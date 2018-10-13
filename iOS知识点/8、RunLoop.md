## RunLoop

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
其中主要的有下面几个

![RunLoop1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop1.png)

- 1、`_pthread`记录当前线程
- 2、`_commonModes`
- 3、`_commonModeItems`
- 4、`_currentMode`,当前mode类型
- 5、`_modes` 存放CFRunLoop里面的所有mode

我们在RunLoop源码中搜索`CFRunLoopMode`来查看一下CFRunLoopMode都存放了哪些东西

![RunLoop2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop2.png)


RunLoop里面会有多个Mode，但是只有一个`_currentMode`

![RunLoop3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/RunLoop3.png)















