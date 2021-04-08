## RunLoop

![RunLoop](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop.png)

RunLoop 运行循环，在程序运行过程中循环做一些事情
**应用范畴**
- 1、定时器（Timer）、PerformSelector
- 2、GCD 
- 3、事件响应、手势识别、界面刷新
- 4、网络请求
- 5、AutoreleasePool

### 概念介绍
在我们命令行项目的`main`函数里面
```
int main(int argc, const char * argv[]) {
@autoreleasepool {
    NSLog(@"Hello, World!");
}
return 0;
}
```
执行完`NSLog(@"Hello, World!");`这个代码以后，程序立即退出，但是在我们的正常项目`main`函数里面
```
int main(int argc, char * argv[]) {
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
```
 如果用一个伪代码来简单的解释一下上面代码的意思，就是
 ```
 int main(int argc, char * argv[]) {
     @autoreleasepool {
     
     int retVal = 0;
     do {
         //休眠等待消息
         int message = sleep_and_wait();
         //处理消息
         retVal = process_message(message)
         } while (0 == retVal);
     }
 }
 ```
 程序不会马上退出，而是保持运行状态，RunLoop的基本作用：
 - 1、保持程序持续的运行
 - 2、处理app中的各种事件（比如触摸事件，定时器事件）
 - 3、节省CPU资源，提高程序性能，该做事的时候做事，改休息的时候休息

**RunLoop对象**
iOS中有2套API来访问和使用RunLoop
- 1、Fundataion：NSRunLoop
- 2、Core Fundataion：CFRunLoop

`NSRunLoop`是基于`CFRunLoop`的一层OC包装，`CFRunLoop`是开源的，地址:https://opensource.apple.com/tarballs/CF/


**RunLoop与线程**
- 1、每一条线程都有唯一的一个与之对应的RunLoop对象
- 2、RunLoop保存在一个全局的Dictionary里，线程作为Key，RunLoop作为Value
- 3、线程刚创建时，并没有RunLoop对象，RunLoop会在第一次获取她时创建
- 4、RunLoop会在线程结束的时候销毁
- 5、主线程的RunLoop已经自动获取（创建），子线程默认没有开启RunLoop

**获取RunLoop对象**
- 1、Fundation
    - 1、获取当前线程的RunLoop对象`[NSRunLoop currentRunLoop]`
    - 2、获取主线程的RunLoop对象`[NSRunLoop mainRunLoop]`
- 2、Core Foundation
    - 1、获取当前线程的RunLoop对象`CFRunLoopGetCurrent()`
    - 2、获取主线程的RunLoop对象`CFRunLoopGetMain()`


**RunLoop相关类**
Core Foundation中关于RunLoop一共有5个类
- 1、CFRunLoopRef
- 2、CFRunLoopModeRef
- 3、CFRunLoopSourceRef
- 4、CFRunLoopTimerRef
- 5、CFRunLoopObserverRef

我们下载`RunLoop`，然后搜索`CFRunLoop`的组成
```
struct __CFRunLoop {
    CFRuntimeBase _base;
    pthread_mutex_t _lock;            /* locked for accessing mode list */
    __CFPort _wakeUpPort;            // used for CFRunLoopWakeUp 
    Boolean _unused;
    volatile _per_run_data *_perRunData;              // reset for runs of the run loop
    pthread_t _pthread;
    uint32_t _winthread;
    CFMutableSetRef _commonModes;
    CFMutableSetRef _commonModeItems;
    CFRunLoopModeRef _currentMode;
    CFMutableSetRef _modes;
    struct _block_item *_blocks_head;
    struct _block_item *_blocks_tail;
    CFAbsoluteTime _runTime;
    CFAbsoluteTime _sleepTime;
    CFTypeRef _counterpart;
};
```

我们打印一下`NSLog(@"%@",[NSRunLoop currentRunLoop]);`

其中主要的有下面几个

![RunLoop1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop1.png)

- 1、`_pthread`记录当前线程
- 2、`_commonModes`
- 3、`_commonModeItems`
- 4、`_currentMode`,当前mode类型
- 5、`_modes` 存放CFRunLoop里面的所有mode

我们在RunLoop源码中搜索`CFRunLoopMode`来查看一下CFRunLoopMode都存放了哪些东西



![RunLoop2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop2.png)

- 1、Source0：
    - 处理触摸事件，
    - performSelector:onThread:
- 2、Source1：
    - 基于Port的线程间通信，
    - 系统事件的捕捉
- 3、Timer ：
    - NSTimer，
    - performSelector:withObject:afterDelay:
- 4、Observers：
    - 用于监听RunLoop的状态
    - UI刷新
    - Autorelease pool（BeforeWaiting）

我们来简单的证明一下`Source0`,我们随便写一个`touchesBegan`触摸事件，然后在里面打一个断点，`bt`指令就是打印线程执行的所有方法

![RunLoop4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop4.png)

我们可以在线程执行方法中可以发现，在调用RunLoop相关方法的时候，第一个是调用的`__CFRunLoopDoSources0`

RunLoop里面会有多个Mode，但是只有一个`_currentMode`

![RunLoop3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop3.png)



**CFRunLoopModeRef**
- 1、CFRunLoopModeRef代表着RunLoop的运行模式
- 2、一个RunLoop包含若干个`Mode`，每个`Mode`又包含若干个`Source0/Source1/Timer/Observer`
- 3、RunLoop启动的时候只能选择其中一个Mode作为currentMode
- 4、如果要切换Mode，只能退出当前Loop，再重新选择一个Mode进入，不同组的`Source0/Source1/Timer/Observer`互不影响
- 5、如果Mode里面没有任何`Source0/Source1/Timer/Observer`，RunLoop会立刻退出

**CFRunLoopModeRef常见的Mode**
- 1、KCFRunLoopDefaultMode（NSDefaultRunLoopMode）：App的默认Mode，通常主线程是在这个Mode下运行的
- 2、UITrackingRunLoopMode：界面跟踪 Mode，用于 ScrollView 追踪触摸滑动，保证界面滑动时不受其他 Mode 影响

获取当前Mode
```
CFRunLoopMode mode = CFRunLoopCopyCurrentMode(CFRunLoopGetCurrent());
```


**CFRunLoopObserverRef**

RunLoop的几种状态

```
/* Run Loop Observer Activities */
typedef CF_OPTIONS(CFOptionFlags, CFRunLoopActivity) {
    kCFRunLoopEntry = (1UL << 0), //即将进入runloop
    kCFRunLoopBeforeTimers = (1UL << 1), //即将处理timer
    kCFRunLoopBeforeSources = (1UL << 2), //即将处理source
    kCFRunLoopBeforeWaiting = (1UL << 5), //即将进入休眠
    kCFRunLoopAfterWaiting = (1UL << 6),  //刚从休眠中唤醒
    kCFRunLoopExit = (1UL << 7),          //即将退出Loop
    kCFRunLoopAllActivities = 0x0FFFFFFFU
};

```
我们可以添加一个Observer监听RunLoop的所有状态，代码如下
```
// 创建Observer
CFRunLoopObserverRef observer = CFRunLoopObserverCreateWithHandler(kCFAllocatorDefault, kCFRunLoopAllActivities, YES, 0, ^(CFRunLoopObserverRef observer, CFRunLoopActivity activity) {
    switch (activity) {
        case kCFRunLoopEntry:
            NSLog(@"kCFRunLoopEntry");
            break;
        case kCFRunLoopBeforeTimers:
            NSLog(@"kCFRunLoopBeforeTimers");
            break;
        case kCFRunLoopBeforeSources:
            NSLog(@"kCFRunLoopBeforeSources");
            break;
        case kCFRunLoopBeforeWaiting:
            NSLog(@"kCFRunLoopBeforeWaiting");
            break;
        case kCFRunLoopAfterWaiting:
            NSLog(@"kCFRunLoopAfterWaiting");
            break;
        case kCFRunLoopExit:
            NSLog(@"kCFRunLoopExit");
            break;
        default:
            break;
    }
});
// 添加Observer到RunLoop中
CFRunLoopAddObserver(CFRunLoopGetMain(), observer, kCFRunLoopCommonModes);
// 释放
CFRelease(observer);
```

我们运行上面代码，然后查看打印结果

![RunLoop6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop6.png)

在没有任何事件处理的情况下，最终RunLoop的活动状态为`kCFRunLoopBeforeWaiting`即将进入休眠




既然我们可以监听到了`RunLoop`的`Mode`变化情况，那么我们就可以打印一下`KCFRunLoopDefaultMode`和`UITrackingRunLoopMode`的切换情况了

我们在view上随便拉一个`UITextView`,然后滚动`UITextView`
监听代码
```
//创建observer
CFRunLoopObserverRef observer = CFRunLoopObserverCreateWithHandler(kCFAllocatorDefault, kCFRunLoopAllActivities, YES, 0, ^(CFRunLoopObserverRef observer, CFRunLoopActivity activity) {
    switch (activity) {
        case kCFRunLoopEntry: {
            CFRunLoopMode mode = CFRunLoopCopyCurrentMode(CFRunLoopGetCurrent());
            NSLog(@"kCFRunLoopEntry - %@", mode);
            CFRelease(mode);
            break;
        }

        case kCFRunLoopExit: {
            CFRunLoopMode mode = CFRunLoopCopyCurrentMode(CFRunLoopGetCurrent());
            NSLog(@"kCFRunLoopExit - %@", mode);
            CFRelease(mode);
            break;
        }

        default:
        break;
    }
});

//添加observer到runloop中
CFRunLoopAddObserver(CFRunLoopGetMain(), observer, kCFRunLoopCommonModes);
// 释放
CFRelease(observer);
```
打印结果为

![RunLoop5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop5.png)

- 1、在刚开始滚动`UITextView`的时候，先退出`kCFRunLoopDefaultMode`，所以默认应该就是`kCFRunLoopDefaultMode`
- 2、在滚动中，进入`UITrackingRunLoopMode`
- 3、在滚动结束，先退出`UITrackingRunLoopMode`，然后在进入`kCFRunLoopDefaultMode`



### RunLoop的运行逻辑

![RunLoop7](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop7.png)


每次运行RunLoop，线程的RunLoop会自动处理之前未处理的消息，并通知相关的观察者。具体顺序
- 1、通知观察者（observers）RunLoop即将启动
- 2、通知观察者（observers）任何即将要开始的定时器
- 3、通知观察者（observers）即将处理source0事件
- 4、处理source0
- 5、如果有source1，跳到第9步
- 6、通知观察者（observers）线程即将进入休眠
- 7、将线程置于休眠知道任一下面的事件发生
    - 1、source0事件触发
    - 2、定时器启动
    - 3、外部手动唤醒
- 8、通知观察者（observers）线程即将唤醒
- 9、处理唤醒时收到的时间，之后跳回2
    - 1、如果用户定义的定时器启动，处理定时器事件
    - 2、如果source0启动，传递相应的消息
- 10、通知观察者RunLoop结束



**RunLoop休眠原理**

![RunLoop8](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop8.png)

在RunLoop即将休眠的时候，通过`mach_msg()`方法来让软件和硬件交互
- 1、即将休眠的时候，程序调用`mach_msg()`传递给CPU，告诉CPU停止运行
- 2、即将启动RunLoop的时候，程序调用`mach_msg()`传递给CPU，告诉CPU开始工作





### RunLoop简单应用

#### 滚动视图上面NSTimer不失效

我们写一个简单的定时器,然后视图上面创建一个TextView,然后滚动TextView
```
static int count = 0;
[NSTimer scheduledTimerWithTimeInterval:1 repeats:YES block:^(NSTimer * _Nonnull timer) {
    NSLog(@"%d",count++);
}];
```


![RunLoop9](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop9.png)

我们观察可以发现在打印的第二秒和第三秒之间其实相差了`5s`，因为一个线程只会有一个RunLoop，默认情况下是`kCFRunLoopDefaultMode`，在滚动`UITextView`的时候，RunLoop切换到了`UITrackingRunLoopMode`,这个时候定时器就会停止，在滚动`UITextView`结束的时候，RunLoop切换到了`kCFRunLoopDefaultMode`，定时器继续开始启动了。

解决这个问题的方法就是把这个`NSTimer`添加到两种RunLoop中
- 1、
```
[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
[[NSRunLoop currentRunLoop] addTimer:timer forMode:UITrackingRunLoopMode];
```
- 2、还有一个NSRunLoopCommonModes，我们用`NSRunLoopCommonModes`标记的时候，就可以实现上面效果
```
[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
```
NSRunLoopCommonModes并不是一个真的模式，它只是一个标记,timer能在_commonModes数组中存放的模式下工作

#### 线程保活(常驻线程)
开始之前先介绍几个概念
- 1、线程刚创建时，并没有RunLoop对象，RunLoop会在第一次获取她时创建
    - 1、获取线程：[NSRunLoop currentRunLoop]
    - 2、获取线程：CFRunLoopGetCurrent()
- 2、启动RunLoop的三种方法
    - 1、`- (void)run; `,
        这种方法runloop会一直运行下去，在此期间会处理来自输入源的数据，并且会在NSDefaultRunLoopMode模式下重复调用runMode:beforeDate:方法；
    - 2、`- (void)runUntilDate:(NSDate *)limitDate；`
        可以设置超时时间，在超时时间到达之前，runloop会一直运行，在此期间runloop会处理来自输入源的数据，并且也会在NSDefaultRunLoopMode模式下重复调用runMode:beforeDate:方法；
    - 3、`- (void)runMode:(NSString *)mode beforeDate:(NSDate *)limitDate;`
        runloop会运行一次，超时时间到达或者第一个input source被处理，则runloop就会退出
- 3、退出RunLoop的方式
    - 1、启动方式的退出方法，如果runloop没有input sources或者附加的timer，runloop就会退出。
    - 2、启动方式runUntilDate，可以通过设置超时时间来退出runloop。
    - 3、启动方式runMode:beforeDate，通过这种方式启动，runloop会运行一次，当超时时间到达或者第一个输入源被处理，runloop就会退出。
        

如果我们想控制runloop的退出时机，而不是在处理完一个输入源事件之后就退出，那么就要重复调用runMode:beforeDate:，
具体可以参考苹果文档给出的方案，如下：
```
NSRunLoop *myLoop  = [NSRunLoop currentRunLoop];
myPort = (NSMachPort *)[NSMachPort port];
[myLoop addPort:_port forMode:NSDefaultRunLoopMode];

BOOL isLoopRunning = YES; // global

while (isLoopRunning && [myLoop runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]]);
 
```

```
//关闭runloop的地方
- (void)quitLoop
{
    isLoopRunning = NO;
    CFRunLoopStop(CFRunLoopGetCurrent());
}
```

做了一个简单的RunLoop的封装，我们可以更加方便的时候保活线程，并且能够及时的销毁,需要的可以点击[这里](https://github.com/SunshineBrother/JHBlog/tree/master/iOS知识点/RunLoop封装)



### 面试题
1、讲讲RunLoop项目中有用到吗？

- 1、定时器切换的时候，为了保证定时器的准确性，需要添加runLoop
- 2、在聊天界面，我们需要持续的把聊天信息存到数据库中，这个时候需要开启一个保活线程，在这个线程中处理

2、RunLoop内部实现逻辑？

- 1、通知观察者（observers）RunLoop即将启动
- 2、通知观察者（observers）任何即将要开始的定时器
- 3、通知观察者（observers）即将处理source0事件
- 4、处理source0
- 5、如果有source1，跳到第9步
- 6、通知观察者（observers）线程即将进入休眠
- 7、将线程置于休眠知道任一下面的事件发生
- 1、source0事件触发
- 2、定时器启动
- 3、外部手动唤醒
- 8、通知观察者（observers）线程即将唤醒
- 9、处理唤醒时收到的时间，之后跳回2
- 1、如果用户定义的定时器启动，处理定时器事件
- 2、如果source0启动，传递相应的消息
- 10、通知观察者RunLoop结束

3、RunLoop和线程的关系？

- 1、每一条线程都有唯一的一个与之对应的RunLoop对象
- 2、RunLoop保存在一个全局的Dictionary里，线程作为Key，RunLoop作为Value
- 3、线程刚创建时，并没有RunLoop对象，RunLoop会在第一次获取她时创建
- 4、RunLoop会在线程结束的时候销毁
- 5、主线程的RunLoop已经自动获取（创建），子线程默认没有开启RunLoop
 
4、RunLoop有几种状态

kCFRunLoopEntry = (1UL << 0),   //   即将进入RunLoop
kCFRunLoopBeforeTimers = (1UL << 1), // 即将处理Timer
kCFRunLoopBeforeSources = (1UL << 2), // 即将处理Source
kCFRunLoopBeforeWaiting = (1UL << 5), //即将进入休眠
kCFRunLoopAfterWaiting = (1UL << 6),// 刚从休眠中唤醒
kCFRunLoopExit = (1UL << 7),// 即将退出RunLoop

5、RunLoop的mode的作用
系统注册了5中mode
```
kCFRunLoopDefaultMode //App的默认Mode，通常主线程是在这个Mode下运行
UITrackingRunLoopMode //界面跟踪 Mode，用于 ScrollView 追踪触摸滑动，保证界面滑动时不受其他 Mode 影响
UIInitializationRunLoopMode // 在刚启动 App 时第进入的第一个 Mode，启动完成后就不再使用
GSEventReceiveRunLoopMode // 接受系统事件的内部 Mode，通常用不到
kCFRunLoopCommonModes //这是一个占位用的Mode，不是一种真正的Mode

```
但是我们只能使用两种mode
```
kCFRunLoopDefaultMode //App的默认Mode，通常主线程是在这个Mode下运行
UITrackingRunLoopMode //界面跟踪 Mode，用于 ScrollView 追踪触摸滑动，保证界面滑动时不受其他 Mode 影响
```





[iOS 多线程：『RunLoop』详尽总结](https://www.jianshu.com/p/d260d18dd551)

[iOS RunLoop入门小结](http://www.cocoachina.com/ios/20180515/23380.html)

[iOS-Runloop常驻线程／性能优化](https://www.jianshu.com/p/f3079ea36775)



