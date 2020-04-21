## objc_msgSend执行流程 

OC中的方法调用，其实都是转化为`objc_msgSend`函数的调用，`objc_msgSend`的执行流程可以分为3大阶段
- 1、消息发送
- 2、动态方法解析
- 3、消息转发


### 消息发送

![消息发送1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送1.png)

消息发送流程是我们平时最经常使用的流程，其他的像`动态方法解析`和`消息转发`其实是补救措施。具体流程如下
- 1、首先判断消息接受者`receiver`是否为nil，如果为nil直接退出消息发送
- 2、如果存在消息接受者`receiverClass`，首先在消息接受者`receiverClass`的`cache`中查找方法，如果找到方法，直接调用。如果找不到，往下进行
- 3、没有在消息接受者`receiverClass`的`cache`中找到方法，则从`receiverClass`的`class_rw_t`中查找方法，如果找到方法，执行方法，并把该方法缓存到`receiverClass`的`cache`中；如果没有找到，往下进行
- 4、没有在`receiverClass`中找到方法，则通过`superClass指针`找到`superClass`，也是现在缓存中查找，如果找到，执行方法，并把该方法缓存到`receiverClass`的`cache`中；如果没有找到，往下进行
- 5、没有在消息接受者`superClass`的`cache`中找到方法，则从`superClass`的`class_rw_t`中查找方法，如果找到方法，执行方法，并把该方法缓存到`receiverClass`的`cache`中；如果没有找到，重复4、5步骤。如果找不到了`superClass`了，往下进行
- 6、如果在最底层的`superClass`也找不到该方法，则要转到`动态方法解析`


### 动态方法解析

![消息发送2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送2.png)

- 开发者可以实现以下方法，来动态添加方法实现
    - +resolveInstanceMethod:
    - +resolveClassMethod:
    
- 动态解析过后，会重新走“消息发送”的流程，从receiverClass的cache中查找方法这一步开始执行

我们创建一个`Person`类，然后在`.h`文件中写一个`- (void)test`，但是不写具体实现，然后调用。会打印出最常见的`unrecognized selector sent to instance 0x100559b60`。

**动态方法解析1**

动态方法解析需要调用`resolveInstanceMethod`或者`resolveClassMethod`一个对应实例方法，一个对应类方法。我们这里是实例方法使用`resolveInstanceMethod`

我们看一下`resolveInstanceMethod`的解释，在我们需要执行`动态方法解析`的时候我们最好返回`YES`。

![消息发送3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送3.png)

```
- (void)other{
	NSLog(@"%s",__func__);
	}
	+ (BOOL)resolveInstanceMethod:(SEL)sel{
		if (sel == @selector(test)) {
		//获取其他方法
		Method method = class_getInstanceMethod(self, @selector(other));
		//动态添加test的方法
		class_addMethod(self, sel, method_getImplementation(method), method_getTypeEncoding(method));
	}

	return [super resolveInstanceMethod:sel];
}

@end
```

 在`class_addMethod`方法中我们需要`imp`，`types`，但是OC并没有提供相关属性，所有我们可以调用相关方法来获取相关参数
 
 ![消息发送4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送4.png)


**动态方法解析2**

这里我们在随便验证一下`method`的结构是不是这种
```
struct method_t {
	SEL sel;
	char *types;
	IMP imp;
};
```
我们代码改成这样
```
struct method_t {
	SEL sel;
	char *types;
	IMP imp;
};
+ (BOOL)resolveInstanceMethod:(SEL)sel{

	if (sel == @selector(test)) {
		//获取其他方法
		struct method_t *method = (struct method_t *)class_getInstanceMethod(self, @selector(other));
		//动态添加test的方法
		class_addMethod(self, sel, method->imp, method->types);

		return  YES;
	}

	return [super resolveInstanceMethod:sel];
}
```

 ![消息发送5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送5.png)


**动态方法解析3**

其实我们还可以用C语言验证一下，`提示：C语言中函数方法就是函数的地址`

```
void c_other(id self, SEL _cmd)
{
	NSLog(@"c_other - %@ - %@", self, NSStringFromSelector(_cmd));
}
+ (BOOL)resolveInstanceMethod:(SEL)sel{

	if (sel == @selector(test)) {

		class_addMethod(self, sel, (IMP)c_other, "v16@0:8");
		return YES;
	}

	return [super resolveInstanceMethod:sel];
}

```


### 消息转发

如果方法一个方法在`消息发送阶段`没有找到相关方法，也没有进行`动态方法解析`，这个时候就会走到消息转发阶段了。

 ![消息发送6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送6.png)


- 调用`forwardingTargetForSelector`，返回值不为nil时，会调用`objc_msgSend(返回值, SEL)`
- 调用`methodSignatureForSelector`,返回值不为nil，调用`forwardInvocation:`方法；返回值为nil时，调用`doesNotRecognizeSelector:`方法
- 开发者可以在forwardInvocation:方法中自定义任何逻辑
- 以上方法都有对象方法、类方法2个版本（前面可以是加号+，也可以是减号-）

**forwardingTargetForSelector**

我们创建一个命令行项目，创建两个类，`person`和`Student`,在`person.h`里面写一个实例方法，但是不去实现相关方法。

```
@interface Person : NSObject
- (void)test;
@end


@interface Student : NSObject
- (void)test;
@end
#import "Student.h"

@implementation Student
- (void)test{
	NSLog(@"%s",__func__);
}
@end
```
调用的时候回报出我们最常见的错误`unrecognized selector sent to instance 0x100747a50`

如果我们在`person`里面实现这个方法
```
- (id)forwardingTargetForSelector:(SEL)aSelector{
	if (aSelector == @selector(test)) {
	return [[Student alloc]init];
	}
	return nil;
}
```
 
 ![消息发送7](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送7.png)

调用`forwardingTargetForSelector`，返回值不为nil时，会调用`objc_msgSend(返回值, SEL)`，结果就是调用了`objc_msgSend(Student,test)`



**methodSignatureForSelector（方法签名）**

当`forwardingTargetForSelector`返回值为nil，或者都没有调用该方法的时候，系统会调用`methodSignatureForSelector`方法。调用`methodSignatureForSelector`,返回值不为nil，调用`forwardInvocation:`方法；返回值为nil时，调用`doesNotRecognizeSelector:`方法

对于方法签名的生成方式
- 1、`[NSMethodSignature signatureWithObjCTypes:"i@:i"]`
- 2、`[[[Student alloc]init] methodSignatureForSelector:aSelector];`

 实现方法签名以后我们还要实现`forwardInvocation`方法，当调用`person`的`test`的方法的时候，就会走到这个方法中
 
  ![消息发送8](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送8.png)
 
 NSInvocation封装了一个方法调用，包括：方法调用者、方法名、方法参数
 - anInvocation.target 方法调用者
 - anInvocation.selector 方法名
 - [anInvocation getArgument:NULL atIndex:0]

 我们也可以先执行`NSLog(@"========");`在执行Student的test方法
 ```
 - (void)forwardInvocation:(NSInvocation *)anInvocation
 {
	 NSLog(@"========");
	 anInvocation.target = [[Student alloc]init];
	 [anInvocation invoke];
	 
	 //    [anInvocation invokeWithTarget:[[Student alloc] init]];
 }
 ```
  ![消息发送9](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/消息发送9.png)
 
其中这两个方法是一样的
`[anInvocation invokeWithTarget:[[Student alloc] init]];`

```
anInvocation.target = [[Student alloc]init];
[anInvocation invoke];
```


其实这个方法还是比较有用的，像网上一些对bug处理都会用到这个方法






















