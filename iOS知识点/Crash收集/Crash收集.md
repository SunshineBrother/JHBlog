 ## Crash分析

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






























[漫谈 iOS Crash 收集框架](https://mp.weixin.qq.com/s?__biz=MjM5NTIyNTUyMQ==&mid=208483273&idx=1&sn=37ee88e06e7426f59f3074c536370317&scene=21)

[全面的理解和分析iOS的崩溃日志](http://www.cocoachina.com/ios/20171026/20921.html)

[iOS实录14：浅谈iOS Crash（一）](https://www.jianshu.com/p/3261493e6d9e)

[质量监控-保护你的crash](https://www.jianshu.com/p/c8f731d18518)

[深入iOS系统底层之crash解决方法介绍](https://www.jianshu.com/p/cf0945f9c1f8)

[Baymax：网易iOS App运行时Crash自动防护实践](https://mp.weixin.qq.com/s?__biz=MzUxMzcxMzE5Ng==&mid=2247488311&amp;idx=1&amp;sn=0db090c8d4a5efafa47f00af4b3f174f&source=41#wechat_redirect)
