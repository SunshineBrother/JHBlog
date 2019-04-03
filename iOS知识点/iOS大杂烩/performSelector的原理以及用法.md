## performSelector的原理以及用法 

```
@protocol NSObject

- (id)performSelector:(SEL)aSelector;
- (id)performSelector:(SEL)aSelector withObject:(id)object;
- (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;

@end

@interface NSObject (NSDelayedPerforming)

- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay inModes:(NSArray<NSRunLoopMode> *)modes;
- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget selector:(SEL)aSelector object:(nullable id)anArgument;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget;

@end

@interface NSRunLoop (NSOrderedPerform)

- (void)performSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg order:(NSUInteger)order modes:(NSArray<NSRunLoopMode> *)modes;
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg;
- (void)cancelPerformSelectorsWithTarget:(id)target;

@end


@interface NSObject (NSThreadPerformAdditions)

- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array;
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait;
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array  
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait  
- (void)performSelectorInBackground:(SEL)aSelector withObject:(nullable id)arg  

@end
```

### 1、基础用法

performSelecor响应了OC语言的动态性:延迟到运行时才绑定方法。当我们在使用以下方法时:

```
[self performSelector:@selector(play)];
[self performSelector:@selector(play:) withObject:@{@"A":@"a"}];
[self performSelector:@selector(play:with:) withObject:@{@"A":@"a"} withObject:@{@"B":@"b"}];
```
编译阶段并不会去检查方法是否有效存在，只会给出警告:
```
Undeclared selector 'play'
Undeclared selector 'play:'
Undeclared selector 'play:with:'
```

### 2、延迟执行

延迟执行的方法主要来源自`NSObject`的分类`NSDelayedPerforming`

关于延迟执行的方法
```
- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay;
- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay inModes:(NSArray<NSRunLoopMode> *)modes;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget selector:(SEL)aSelector object:(nullable id)anArgument;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget;
```

最简单的使用就是这样
```
[obj performSelector:@selector(play) withObject:@"李周" afterDelay:4.f];
```

该方法在当前线程的运行循环(`runloop`)中设置一个计时器(`timer`)来执行`aSelector`消息。该计时器`Mode`为`NSDefaultRunLoopMode`。当触发计时器时，线程会尝试从`runloop`中出列`dequeue`该消息并执行该`selector`。如果`runloop`正在运行并且处于`default mode`,则成功。否则，该计时器将等待，直到`runloop`处于`default mode`

 
```
dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
NSLog(@"1");
[self performSelector : @selector(play)
withObject : nil
afterDelay : 0];
NSLog(@"3");
});

- (void)play{
NSLog(@"2");
}
```

上面这一段代码打印什么呢？ 

我们把代码运行一下，发现打印为
```
2019-04-03 14:18:13.918873+0800 performSelector[7605:267316] 1
2019-04-03 14:18:13.919144+0800 performSelector[7605:267316] 3
```

**为什么？**

我们知道线程刚创建时并没有`runloop`，如果不主动获取，那它一直不会有。从上面我们知道该方法内部会创建一个`Timer`，而只有主线程中的`runloop`是默认开启的，其他线程没有，所以在上面的代码中，`performSelector:withObject:afterDelay:`方法在一个子线程中执行，由于该线程中并`runloop`并没有开启，所以`performSelector:withObject:afterDelay:`方法会失效，也就不会执行`aSelector`了。
 
想要打印`2`需要这样修改
```
dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
NSLog(@"1");
[self performSelector : @selector(play)
withObject : nil
afterDelay : 1];
[[NSRunLoop currentRunLoop] run];
NSLog(@"3");
});
```
打印结果
```
2019-04-03 14:20:44.972441+0800 performSelector[7669:270248] 1
2019-04-03 14:20:45.976442+0800 performSelector[7669:270248] 2
2019-04-03 14:20:45.976923+0800 performSelector[7669:270248] 3
```


如果希望在`runloop`处于`default mode`以外的模式中将该消息出列。可以使用`performSelector:withObject:afterDelay:inModes:`方法。如果不确定当前线程是否是主线程，则可以使用`performSelectorOnMainThread：withObject：waitUntilDone：`或`performSelectorOnMainThread：withObject：waitUntilDone：modes：`方法来保证选择器在主线程上执行。 要取消已经在排队的消息，请使用`cancelPreviousPerformRequestsWithTarget：`或`cancelPreviousPerformRequestsWithTarget：selector：object：`方法

 

### 3、关于`performSelector`的一些命令执行

```
@interface NSRunLoop (NSOrderedPerform)

- (void)performSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg order:(NSUInteger)order modes:(NSArray<NSRunLoopMode> *)modes;
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg;
- (void)cancelPerformSelectorsWithTarget:(id)target;

@end
```
我们执行下面一段代码
```
- (void)test3{

[[NSRunLoop currentRunLoop]performSelector:@selector(play1) target:self argument:nil order:1 modes:@[(NSRunLoopMode)kCFRunLoopDefaultMode]];
[[NSRunLoop currentRunLoop]performSelector:@selector(play5) target:self argument:nil order:5 modes:@[(NSRunLoopMode)kCFRunLoopDefaultMode]];
[[NSRunLoop currentRunLoop]performSelector:@selector(play2) target:self argument:nil order:2 modes:@[(NSRunLoopMode)kCFRunLoopDefaultMode]];
[[NSRunLoop currentRunLoop]performSelector:@selector(play3) target:self argument:nil order:3 modes:@[(NSRunLoopMode)kCFRunLoopDefaultMode]];
[[NSRunLoop currentRunLoop]performSelector:@selector(play4) target:self argument:nil order:4 modes:@[(NSRunLoopMode)kCFRunLoopDefaultMode]];
}

- (void)play1{
NSLog(@"%s",__func__);
}
- (void)play2{
NSLog(@"%s",__func__);
}
- (void)play3{
NSLog(@"%s",__func__);
}
- (void)play4{
NSLog(@"%s",__func__);
}
- (void)play5{
NSLog(@"%s",__func__);
}
```

按照我们正常代码执行的顺序应该是
```
[ViewController play1]
[ViewController play5]
[ViewController play2]
[ViewController play3]
[ViewController play4]
```

但是我们运行以后发现，执行的顺序为
```
[ViewController play1]
[ViewController play2]
[ViewController play3]
[ViewController play4]
[ViewController play5]
```

`我们仔细观察代码的书写顺序和运行结果就会发现，参数order越小，执行越早，也就是说，最早执行的代码是order最小的那个，然后按顺序进行下去`



### 4、线程问题`NSThreadPerformAdditions`

```
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array;
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait;
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array  
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait  
- (void)performSelectorInBackground:(SEL)aSelector withObject:(nullable id)arg  

```

- 1、**performSelectorOnMainThread在主线程中执行**
- 2、**performSelectorInBackground 后台执行**
```
[self performSelectorInBackground:@selector(test) withObject:nil];
```
- 3、**performSelector:onThread在指定线程执行**
```
[self performSelector:@selector(test) onThread:[NSThread currentThread] withObject:nil waitUntilDone:YES];
```




















