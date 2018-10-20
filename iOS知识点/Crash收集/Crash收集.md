 ## Crash分析

### Crash分类
`crash`可以分为三种类型，每一种类型表示不同分层上的crash，也拥有各自的捕获方式。
- `mach exception`异常
- `signal`异常
- `NSException`异常，Objective-C 异常

#### Mach异常

Mach操作系统微内核，是许多新操作系统的设计基础。Mach微内核中有几个基础概念：
- Tasks，拥有一组系统资源的对象，允许"thread"在其中执行。
- Threads，执行的基本单位，拥有task的上下文，并共享其资源。
- Ports，task之间通讯的一组受保护的消息队列；task可对任何port发送/接收数据。
- Message，有类型的数据对象集合，只可以发送到port。


Mach 异常是指最底层的内核级异常，被定义在 <mach/exception_types.h>下。`mach`异常由处理器陷阱引发，在异常发生后会被异常处理程序转换成`Mach消息`，接着依次投递到`thread、task和host端口`。如果没有一个端口处理这个异常并返回`KERN_SUCCESS`，那么应用将被终止。每个端口拥有一个异常端口数组，系统暴露了后缀为`_set_exception_ports`的多个`API`让我们注册对应的异常处理到端口中

**Mach异常方式**






 





### Crash捕获









### Crash分析






























[漫谈 iOS Crash 收集框架](https://mp.weixin.qq.com/s?__biz=MjM5NTIyNTUyMQ==&mid=208483273&idx=1&sn=37ee88e06e7426f59f3074c536370317&scene=21)

[全面的理解和分析iOS的崩溃日志](http://www.cocoachina.com/ios/20171026/20921.html)

[iOS实录14：浅谈iOS Crash（一）](https://www.jianshu.com/p/3261493e6d9e)

[质量监控-保护你的crash](https://www.jianshu.com/p/c8f731d18518)

[深入iOS系统底层之crash解决方法介绍](https://www.jianshu.com/p/cf0945f9c1f8)

[Baymax：网易iOS App运行时Crash自动防护实践](https://mp.weixin.qq.com/s?__biz=MzUxMzcxMzE5Ng==&mid=2247488311&amp;idx=1&amp;sn=0db090c8d4a5efafa47f00af4b3f174f&source=41#wechat_redirect)
