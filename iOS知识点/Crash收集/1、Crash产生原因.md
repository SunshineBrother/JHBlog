 ## Crash产生原因

### Crash分类
一般是由 Mach异常或 Objective-C 异常（NSException）引起的。我们可以针对这两种情况抓取对应的 Crash 事件
 
![crash2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/Crash收集/crash2.png)
 
 - 1、Mach异常是最底层的内核级异常，如EXC_BAD_ACCESS（内存访问异常)
 - 2、Unix Signal是Unix系统中的一种异步通知机制，Mach异常在host层被ux_exception转换为相应的Unix Signal，并通过threadsignal将信号投递到出错的线程
 - 3、 NSException是OC层，由iOS库或者各种第三方库或Runtime验证出错误而抛出的异常。如NSRangeException（数组越界异常）
 - 4、当错误发生时候，先在最底层产生Mach异常；Mach异常在host层被转换为相应的Unix Signal; 在OC层如果有对应的NSException（OC异常），就转换成OC异常，OC异常可以在OC层得到处理；如果OC异常一直得不到处理，程序会强行发送SIGABRT信号中断程序。在OC层如果没有对应的NSException，就只能让Unix标准的signal机制来处理了。
 - 5、在捕获Crash事件时，优选Mach异常。因为Mach异常处理会先于Unix信号处理发生，如果Mach异常的handler让程序exit了，那么Unix信号就永远不会到达这个进程了。而转换Unix信号是为了兼容更为流行的POSIX标准(SUS规范)，这样就不必了解Mach内核也可以通过Unix信号的方式来兼容开发
 

#### Mach异常

Mach操作系统微内核，是许多新操作系统的设计基础。Mach微内核中有几个基础概念：
- Tasks，拥有一组系统资源的对象，允许"thread"在其中执行。
- Threads，执行的基本单位，拥有task的上下文，并共享其资源。
- Ports，task之间通讯的一组受保护的消息队列；task可对任何port发送/接收数据。
- Message，有类型的数据对象集合，只可以发送到port。


Mach 异常是指最底层的内核级异常，被定义在 <mach/exception_types.h>下。`mach`异常由处理器陷阱引发，在异常发生后会被异常处理程序转换成`Mach消息`，接着依次投递到`thread、task和host端口`。如果没有一个端口处理这个异常并返回`KERN_SUCCESS`，那么应用将被终止。每个端口拥有一个异常端口数组，系统暴露了后缀为`_set_exception_ports`的多个`API`让我们注册对应的异常处理到端口中

**Mach异常方式**

![crash1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/Crash收集/crash.png)

Mach提供少量API
```
// 内核中创建一个消息队列，获取对应的port
mach_port_allocate();
// 授予task对port的指定权限
mach_port_insert_right();
// 通过设定参数：MACH_RSV_MSG/MACH_SEND_MSG用于接收/发送mach message
mach_msg();
```

**Mach异常捕获**
`task_set_exception_ports()`，设置内核接收Mach异常消息的`Port`，替换为自定义的Port后，即可捕获程序执行过程中产生的异常消息。

```
+ (void)createAndSetExceptionPort {
mach_port_t server_port;
kern_return_t kr = mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &server_port);
assert(kr == KERN_SUCCESS);
NSLog(@"create a port: %d", server_port);

kr = mach_port_insert_right(mach_task_self(), server_port, server_port, MACH_MSG_TYPE_MAKE_SEND);
assert(kr == KERN_SUCCESS);

kr = task_set_exception_ports(mach_task_self(), EXC_MASK_BAD_ACCESS | EXC_MASK_CRASH, server_port, EXCEPTION_DEFAULT | MACH_EXCEPTION_CODES, THREAD_STATE_NONE);

[self setMachPortListener:server_port];
}

// 构造BAD MEM ACCESS Crash
- (void)makeCrash {
NSLog(@"********** Make a [BAD MEM ACCESS] now. **********");
*((int *)(0x1234)) = 122;
}
```
以上代码参考[iOS Mach异常和signal信号](https://yq.aliyun.com/articles/499180)
 

`mach异常`即便注册了对应的处理，也不会导致影响原有的投递流程。此外，即便不去注册`mach异常`的处理，最终经过一系列的处理，`mach异常`会被转换成对应的`UNIX信号`，一种`mach异常`对应了一个或者多个信号类型。因此在`捕获crash要提防二次采集的可能`。


![crash3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/Crash收集/crash3.png)



### 处理signal

当错误发生时候，先在最底层产生Mach异常；Mach异常在host层被转换为相应的Unix Signal; 在OC层如果有对应的NSException（OC异常），就转换成OC异常，OC异常可以在OC层得到处理；如果OC异常一直得不到处理，程序会强行发送SIGABRT信号中断程序。在OC层如果没有对应的NSException，就只能让Unix标准的signal机制来处理了

在`signal.h`中声明了`32种`异常信号，常见的有以下几种

- 1、SIGILL    执行了非法指令，一般是可执行文件出现了错误
- 2、SIGTRAP    断点指令或者其他trap指令产生
- 3、SIGABRT    调用abort产生
- 4、SIGBUS    非法地址。比如错误的内存类型访问、内存地址对齐等
- 5、SIGSEGV    非法地址。访问未分配内存、写入没有写权限的内存等
- 6、SIGFPE    致命的算术运算。比如数值溢出、NaN数值等

 **应用**
 1.`AppDelegate.m`中
```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
// Override point for customization after application launch.

InstallSignalHandler();//信号量截断
InstallUncaughtExceptionHandler();//系统异常捕获

return YES;
}
```
2.`SignalHandler.m`的实现

```
void SignalExceptionHandler(int signal)
{
NSMutableString *mstr = [[NSMutableString alloc] init];
[mstr appendString:@"Stack:\n"];
void* callstack[128];
int i, frames = backtrace(callstack, 128);
char** strs = backtrace_symbols(callstack, frames);
for (i = 0; i <frames; ++i) {
[mstr appendFormat:@"%s\n", strs[i]];
}
[SignalHandler saveCreash:mstr];

}

void InstallSignalHandler(void)
{
signal(SIGHUP, SignalExceptionHandler);
signal(SIGINT, SignalExceptionHandler);
signal(SIGQUIT, SignalExceptionHandler);

signal(SIGABRT, SignalExceptionHandler);
signal(SIGILL, SignalExceptionHandler);
signal(SIGSEGV, SignalExceptionHandler);
signal(SIGFPE, SignalExceptionHandler);
signal(SIGBUS, SignalExceptionHandler);
signal(SIGPIPE, SignalExceptionHandler);
}
```
有关错误类型可以看上面的说明，SignalExceptionHandler是信号出错时候的回调。当有信号出错的时候，可以回调到这个方法

3.`UncaughtExceptionHandler.m`的实现

```
void HandleException(NSException *exception)
{
// 异常的堆栈信息
NSArray *stackArray = [exception callStackSymbols];
// 出现异常的原因
NSString *reason = [exception reason];
// 异常名称
NSString *name = [exception name];
NSString *exceptionInfo = [NSString stringWithFormat:@"Exception reason：%@\nException name：%@\nException stack：%@",name, reason, stackArray];
NSLog(@"%@", exceptionInfo);
[UncaughtExceptionHandler saveCreash:exceptionInfo];
}

void InstallUncaughtExceptionHandler(void)
{
NSSetUncaughtExceptionHandler(&HandleException);
}
```
代码参考至[向晨宇的技术博客-iOS异常捕获](http://www.iosxxx.com/blog/2015-08-29-iosyi-chang-bu-huo.html)

**[demo地址](https://github.com/xcysuccess/iOSCrashUncaught)**

### NSException异常
常见的NSException异常有
- 1、unrecognized selector crash
- 2、KVO crash
- 3、NSNotification crash
- 4、NSTimer crash
- 5、Container crash（数组越界，插nil等）
- 6、NSString crash （字符串操作的crash）
- 7、Bad Access crash （野指针）
- 8、UI not on Main Thread Crash (非主线程刷UI(机制待改善))

更加详细的信息请参考[Baymax：网易iOS App运行时Crash自动防护实践](https://mp.weixin.qq.com/s?__biz=MzUxMzcxMzE5Ng==&mid=2247488311&amp;idx=1&amp;sn=0db090c8d4a5efafa47f00af4b3f174f&source=41#wechat_redirect)

#### unrecognized selector类型

unrecognized selector类型的crash在app众多的crash类型中占着比较大的成分，通常是因为一个对象调用了一个不属于它方法的方法导致的。

方法调用流程
runtime中具体的方法调用流程大致如下：
- 1、在相应操作的对象中的缓存方法列表中找调用的方法，如果找到，转向相应实现并执行。
- 2、如果没找到，在相应操作的对象中的方法列表中找调用的方法，如果找到，转向相应实现执行
- 3、如果没找到，去父类指针所指向的对象中执行1，2.
- 4、以此类推，如果一直到根类还没找到，转向拦截调用，走消息转发机制。
- 5、如果没有重写拦截调用的方法，程序报错。


在一个函数找不到时，runtime提供了三种方式去补救：
- 1、调用resolveInstanceMethod给个机会让类添加这个实现这个函数
- 2、调用forwardingTargetForSelector让别的对象去执行这个函数
- 3、调用forwardInvocation（函数执行器）灵活的将目标函数以其他形式执行。

通过重写NSObject的forwardingTargetForSelector方法，我们就可以将无法识别的方法进行拦截并且将消息转发到安全的桩类对象中，从而可以使app继续正常运行


#### KVO crash 产生原因

KVO,即：Key-Value Observing，它提供一种机制，当指定的对象的属性被修改后，则对象就会接受收到通知。简单的说就是每次指定的被观察的对象的属性被修改后，KVO就会自动通知相应的观察者了。


KVO机制在iOS的很多开发场景中都会被使用到。不过如果一不小心使用不当的话，会导致大量的crash问题

通过会导致KVO Crash的两种情形
- 1、KVO的被观察者dealloc时仍然注册着KVO导致的crash
- 2、添加KVO重复添加观察者或重复移除观察者（KVO注册观察者与移除观察者不匹配）导致的crash

解决方法：可以让被观察对象持有一个KVO的delegate，所有和KVO相关的操作均通过delegate来进行管理，delegate通过建立一张map来维护KVO整个关系。具体就是使用runTime的交换方法重写KVO的一些方法


#### NSNotification类型crash防护 

当一个对象添加了notification之后，如果dealloc的时候，仍然持有notification，就会出现NSNotification类型的crash。
NSNotification类型的crash多产生于程序员写代码时候犯疏忽，在NSNotificationCenter添加一个对象为observer之后，忘记了在对象dealloc的时候移除它。
所幸的是，苹果在iOS9之后专门针对于这种情况做了处理，所以在iOS9之后，即使开发者没有移除observer，Notification crash也不会再产生了。
不过针对于iOS9之前的用户，我们还是有必要做一下NSNotification Crash的防护的。


NSNotification Crash的防护原理很简单， 利用method swizzling hook NSObject的dealloc函数，再对象真正dealloc之前先调用一下[[NSNotificationCenter defaultCenter] removeObserver:self]即可。

#### NSTimer类型crash防护

在程序开发过程中，大家会经常使用定时任务，但使用NSTimer的 scheduledTimerWithTimeInterval:target:selector:userInfo:repeats:接口做重复性的定时任务时存在一个问题：NSTimer会强引用target实例，所以需要在合适的时机invalidate定时器，否则就会由于定时器timer强引用target的关系导致target不能被释放，造成内存泄露，甚至在定时任务触发时导致crash。 crash的展现形式和具体的target执行的selector有关。

与此同时，如果NSTimer是无限重复的执行一个任务的话，也有可能导致target的selector一直被重复调用且处于无效状态，对app的CPU，内存等性能方面均是没有必要的浪费。

那么解决NSTimer的问题的关键点在于以下两点：
- 1、NSTimer对其target是否可以不强引用
- 2、是否找到一个合适的时机，在确定NSTimer已经失效的情况下，让NSTimer自动invalidate

#### Container crash 防护方案

Container crash 类型的防护方案也比较简单，针对于NSArray／NSMutableArray／NSDictionary／NSMutableDictionary／NSCache的一些常用的会导致崩溃的API进行method swizzling，然后在swizzle的新方法中加入一些条件限制和判断，从而让这些API变的安全


#### 野指针crash 防护方案

野指针问题的解决思路方向其实很容易确定，XCode提供了Zombie的机制来排查野指针的问题，那么我们这边可以实现一个类似于Zombie的机制，加上对zombie实例的全部方法拦截机制 和 消息转发机制，那么就可以做到在野指针访问时不Crash而只是crash时相关的信息。
同时还需要注意一点：因为zombie的机制需要在对象释放时保留其指针和相关内存占用，随着app的进行，越来越多的对象被创建和释放，这会导致内存占用越来越大，这样显然对于一个正常运行的app的性能有影响。所以需要一个合适的zombie对象释放机制，确定zombie机制对内存的影响是有限度的


####  非主线程刷UI类型crash防护
在非主线程刷UI将会导致app运行crash，有必要对其进行处理。
目前初步的处理方案是swizzle UIView类的以下三个方法：
```
- (void)setNeedsLayout;
- (void)setNeedsDisplay;
- (void)setNeedsDisplayInRect:(CGRect)rect;
```
在这三个方法调用的时候判断一下当前的线程，如果不是主线程的话，直接利用 `dispatch_async(dispatch_get_main_queue(), ^{ //调用原本方法 });`
来将对应的刷UI的操作转移到主线程上，同时统计错误信息。
但是真正实施了之后，发现这三个方法并不能完全覆盖UIView相关的所有刷UI到操作，但是如果要将全部到UIView的刷UI的方法统计起来并且swizzle，感觉略笨拙而且不高效。





[漫谈 iOS Crash 收集框架](https://mp.weixin.qq.com/s?__biz=MjM5NTIyNTUyMQ==&mid=208483273&idx=1&sn=37ee88e06e7426f59f3074c536370317&scene=21)

[全面的理解和分析iOS的崩溃日志](http://www.cocoachina.com/ios/20171026/20921.html)

[iOS实录14：浅谈iOS Crash（一）](https://www.jianshu.com/p/3261493e6d9e)

[质量监控-保护你的crash](https://www.jianshu.com/p/c8f731d18518)

[深入iOS系统底层之crash解决方法介绍](https://www.jianshu.com/p/cf0945f9c1f8)

[Baymax：网易iOS App运行时Crash自动防护实践](https://mp.weixin.qq.com/s?__biz=MzUxMzcxMzE5Ng==&mid=2247488311&amp;idx=1&amp;sn=0db090c8d4a5efafa47f00af4b3f174f&source=41#wechat_redirect)
