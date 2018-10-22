## Crash日志分析 

### 日志内容
整个日志内容中，直接和Crash信息相关，最能帮助开发者定位问题部分是： 异常信息 和 线程回溯部分的内容。日志主要分为六个部分：
- 进程信息：发生Crash闪退进程的相关信息
    - `Hardware Model` : 标识设备类型。 如果很多崩溃日志都是来自相同的设备类型，说明应用只在某特定类型的设备上有问题
    - `Process` 是应用名称。中括号里面的数字是闪退时应用的进程ID。
- 基本信息:给出了一些基本信息，包括闪退发生的日期和时间，设备的iOS版本。
- 异常信息:闪退发生时抛出的异常类型。还能看到异常编码和抛出异常的线程。
    - Exception Type异常类型：通常包含1.7中的Signal信号和EXC_BAD_ACCESS，NSRangeException等。
    - Exception Codes：异常编码：
    - Crashed Thread：发生Crash的线程id
- 
```
Exception Type:  EXC_BAD_ACCESS (SIGBUS)
Exception Codes: 0x00000000 at 0x00000005710bbeb8
Crashed Thread:  2
```

- 线程回溯：回溯是闪退发生时所有活动帧清单。它包含闪退发生时调用函数的清单。
- 线程状态：闪退时寄存器中的值。一般不需要这部分的信息，因为回溯部分的信息已经足够让你找出问题所在
- 二进制映像：闪退时已经加载的二进制文件。
```
Incident Identifier: 85BE3461-D7FD-4043-A4B9-1C0D9A33F63D
CrashReporter Key:   9ec5a1d3b8d5190024476c7068faa58d8db0371f
//1、进程信息
Hardware Model:      iPhone7,2
Code Type:       ARM-64
Parent Process:  ? [1]
//2、基本信息
Date/Time:       2018-08-06 16:36:58.000 +0800
OS Version:      iOS 10.3.3 (14G60)
Report Version:  104
//3、异常信息
Exception Type:  EXC_BAD_ACCESS (SIGBUS)
Exception Codes: 0x00000000 at 0x00000005710bbeb8
Crashed Thread:  2
//4、线程回溯 （展示发生Crash线程的回溯信息，其他略）
Thread 2 name:  WebThread
Thread 2 Crashed:
0   libobjc.A.dylib                 objc_msgSend + 16
1   UIKit                           -[UIWebDocumentView _updateSubviewCaches] + 40
2   UIKit                           -[UIWebDocumentView subviews] + 92
3   UIKit                           -[UIView(CALayerDelegate) _wantsReapplicationOfAutoLayoutWithLayoutDirtyOnEntry:] + 72
4   UIKit                           -[UIView(CALayerDelegate) layoutSublayersOfLayer:] + 1256
5   QuartzCore                      -[CALayer layoutSublayers] + 148
6   QuartzCore                      CA::Layer::layout_if_needed(CA::Transaction*) + 292
7   QuartzCore                      CA::Layer::layout_and_display_if_needed(CA::Transaction*) + 32
8   QuartzCore                      CA::Context::commit_transaction(CA::Transaction*) + 252
9   QuartzCore                      CA::Transaction::commit() + 504
10  QuartzCore                      CA::Transaction::observer_callback(__CFRunLoopObserver*, unsigned long, void*) + 120
11  CoreFoundation                  __CFRUNLOOP_IS_CALLING_OUT_TO_AN_OBSERVER_CALLBACK_FUNCTION__ + 32
12  CoreFoundation                  __CFRunLoopDoObservers + 372
13  CoreFoundation                  CFRunLoopRunSpecific + 456
14  WebCore                         RunWebThread(void*) + 456
15  libsystem_pthread.dylib         _pthread_body + 240
16  libsystem_pthread.dylib         _pthread_body + 0

//5、进程状态（展示部分）
Thread 2 crashed with ARM-64 Thread State:
cpsr: 0x0000000020000000     fp: 0x000000016e18d7c0     lr: 0x000000018e2765fc     pc: 0x0000000186990150 
sp: 0x000000016e18d7b0     x0: 0x0000000174859740     x1: 0x000000018eb89b7b    x10: 0x0000000102ffc000 
x11: 0x00000198000003ff    x12: 0x0000000102ffc290    x13: 0xbadd8a65710bbead    x14: 0x0000000000000000 
x15: 0x000000018caeb48c    x16: 0x00000005710bbea8    x17: 0x000000018e2765d4    x18: 0x0000000000000000 
x19: 0x0000000103a52800     x2: 0x0000000000000000    x20: 0x00000000000002a0    x21: 0x0000000000000000 
x22: 0x0000000000000000    x23: 0x0000000000000000    x24: 0x0000000000000098    x25: 0x0000000000000000 
x26: 0x000000018ebade52    x27: 0x00000001ad018624    x28: 0x0000000000000000    x29: 0x000000016e18d7c0 
x3: 0x000000017463db60     x4: 0x0000000000000000     x5: 0x0000000000000000     x6: 0x0000000000000000 
x7: 0x0000000000000000     x8: 0x00000001acfb9000     x9: 0x000000018ebf8829

//6、二进制映像 （展示部分）
Binary Images:
0x100030000 -        0x1022cbfff +xxxx arm64  <6b98f446542b3de5818256a8f2dc9ebf> /var/containers/Bundle/Application/441619EF-BD56-4738-B6CF-854492CDFAC9/xxxx.app/xxxx
0x1063f8000 -        0x106507fff  MacinTalk arm64  <0890ce05452130bb9af06c0a04633cbb> /System/Library/TTSPlugins/MacinTalk.speechbundle/MacinTalk
0x107000000 -        0x1072e3fff  TTSSpeechBundle arm64  <d583808dd4b9361b99a911b40688ffd0> /System/Library/TTSPlugins/TTSSpeechBundle.speechbundle/TTSSpeechBundle
...
0x18e03d000 -        0x18ede3fff  UIKit arm64  <314063bdf85f321d88d6e24a0de464a2> /System/Library/Frameworks/UIKit.framework/UIKit
0x18ede4000 -        0x18ee0cfff  CoreBluetooth arm64  <ced176702d7c37e6a9027eeb3fbf7f66> /System/Library/Frameworks/CoreBluetooth.framework/CoreBluetooth

```

### 异常信息解读

**Exception Type（异常类型）**

Exception Type：通常包含Signal信号 和 EXC_BAD_ACCESS，NSRangeException等
- 1、EXC_CRASH：unrecognized selector
- 2、 SIGHUP
本信号在用户终端连接(正常或非正常)结束时发出, 通常是在终端的控制进程结束时, 通知同一session内的各个作业, 这时它们与控制终端不再关联。

- 3、SIGINT
程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl-C)时发出，用于通知前台进程组终止进程。
 - 4、SIGQUIT
和SIGINT类似, 但由QUIT字符(通常是Ctrl-)来控制. 进程在因收到SIGQUIT退出时会产生core文件, 在这个意义上类似于一个程序错误信号。
- 5、 SIGILL
执行了非法指令. 通常是因为可执行文件本身出现错误, 或者试图执行数据段. 堆栈溢出时也有可能产生这个信号。
- 6、SIGTRAP
由断点指令或其它trap指令产生. 由debugger使用。
- 7、SIGABRT
调用abort函数生成的信号。
- 8、 SIGBUS
非法地址, 包括内存地址对齐(alignment)出错。比如访问一个四个字长的整数, 但其地址不是4的倍数。它与SIGSEGV的区别在于后者是由于对合法存储地址的非法访问触发的(如访问不属于自己存储空间或只读存储空间)。
- 9、 SIGFPE
在发生致命的算术运算错误时发出. 不仅包括浮点运算错误, 还包括溢出及除数为0等其它所有的算术的错误。
- 10、 SIGKILL
用来立即结束程序的运行. 本信号不能被阻塞、处理和忽略。如果管理员发现某个进程终止不了，可尝试发送这个信号。
- 11、 SIGUSR1
留给用户使用
- 12、 SIGSEGV
试图访问未分配给自己的内存, 或试图往没有写权限的内存地址写数据.
- 13、 SIGUSR2
留给用户使用
- 14、 SIGPIPE
管道破裂。这个信号通常在进程间通信产生，比如采用FIFO(管道)通信的两个进程，读管道没打开或者意外终止就往管道写，写进程会收到SIGPIPE信号。此外用Socket通信的两个进程，写进程在写Socket的时候，读进程已经终止。
- 15、 SIGALRM
时钟定时信号, 计算的是实际的时间或时钟时间. alarm函数使用该信号.
- 16、 SIGTERM
程序结束(terminate)信号, 与SIGKILL不同的是该信号可以被阻塞和处理。通常用来要求程序自己正常退出，shell命令kill缺省产生这个信号。如果进程终止不了，我们才会尝试SIGKILL。
- 17、 SIGCHLD
子进程结束时, 父进程会收到这个信号。
如果父进程没有处理这个信号，也没有等待(wait)子进程，子进程虽然终止，但是还会在内核进程表中占有表项，这时的子进程称为僵尸进程。这种情 况我们应该避免(父进程或者忽略SIGCHILD信号，或者捕捉它，或者wait它派生的子进程，或者父进程先终止，这时子进程的终止自动由init进程 来接管)。
- 18、 SIGCONT
让一个停止(stopped)的进程继续执行. 本信号不能被阻塞. 可以用一个handler来让程序在由stopped状态变为继续执行时完成特定的工作. 例如, 重新显示提示符
- 19、SIGSTOP
停止(stopped)进程的执行. 注意它和terminate以及interrupt的区别:该进程还未结束, 只是暂停执行. 本信号不能被阻塞, 处理或忽略.
- 20、 SIGTSTP
停止进程的运行, 但该信号可以被处理和忽略. 用户键入SUSP字符时(通常是Ctrl-Z)发出这个信号
- 21、SIGTTIN
当后台作业要从用户终端读数据时, 该作业中的所有进程会收到SIGTTIN信号. 缺省时这些进程会停止执行.
- 22、 SIGTTOU
类似于SIGTTIN, 但在写终端(或修改终端模式)时收到.
- 23、 SIGURG
有”紧急”数据或out-of-band数据到达socket时产生.
- 24、 SIGXCPU
超过CPU时间资源限制. 这个限制可以由getrlimit/setrlimit来读取/改变。
- 25、 SIGXFSZ
当进程企图扩大文件以至于超过文件大小资源限制。
- 26、 SIGVTALRM
虚拟时钟信号. 类似于SIGALRM, 但是计算的是该进程占用的CPU时间.
- 27、SIGPROF
类似于SIGALRM/SIGVTALRM, 但包括该进程用的CPU时间以及系统调用的时间.
- 28、SIGWINCH
窗口大小改变时发出.
- 29、SIGIO
文件描述符准备就绪, 可以开始进行输入/输出操作.
- 30、SIGPWR
Power failure
- 31、 SIGSYS
非法的系统调用


[复制自：iOS异常捕获](http://www.iosxxx.com/blog/2015-08-29-iosyi-chang-bu-huo.html)
[详细可以参考这里](https://github.com/st3fan/osx-10.9/blob/master/xnu-2422.1.72/osfmk/mach/exception_types.h)


**Exception Code（异常编码）**

`Exception Code`：以一些文字开头，紧接着是一个或多个十六进制值。这些数值说明了Crash发生的本质
从Exception Code中，可以区分出Crash是因为程序错误、非法内存访问还是其他原因。常见的异常编码如下表：

|异常编码|描述|
|---|:---:|
|0x8badf00d|ate bad food ，表示应用是因为发生watchdog超时而被iOS终止的。通常是应用花费太多时间而无法启动、终止或响应用系统事件。|
|0xdeadfa11|dead fall，用户强制退出。|
|0xbaaaaaad|用户按住Home键和音量键，获取当前内存状态，不代表崩溃。|
|0xbad22222|VoIP 应用因为过于频繁重启而被终止|
|0xc00010ff|cool off，因为太烫了被干掉|
|0xdead10cc|dead lock，表明应用因为在后台运行时占用系统资源（如通讯录数据库）|
|0xbbadbeef|bad beef，发生致命错误|
 
详细的异常编码代表的含义请参考：[Hexspeak](https://en.wikipedia.org/wiki/Hexspeak)

在后台任务列表中关闭已挂起的应用不会产生崩溃日志。 因为应用一旦被挂起，它何时被终止都是合理的。所以不会产生崩溃日志



### Crash分析

应用程序出现的crash崩溃异常有一些能够简单的被分析和解决，往往这些crash崩溃异常都会带有明确的上下文信息和函数调用层级堆栈。向下面这样，我们能够很清楚的看到是`数组越界问题`
```
Terminating app due to uncaught exception 'NSRangeException', reason: '*** -[__NSArrayI objectAtIndexedSubscript:]: index 3 beyond bounds [0 .. 1]'
*** First throw call stack:

```

但并不是所有的crash崩溃异常都能被简单的解决，尤其是那些没有明确上下文信息的函数调用堆栈或者那些调用堆栈中没有一个函数或者方法能够被直接定位到源代码的场景.。就像我们第一个崩溃日志那个场景。

从崩溃的函数调用栈中可以看出异常是出现在最顶层的函数调用`objc_msgSend+16`处，也就是在`objc_msgSend`函数的`第5条指令`处(通常情况下arm体系结构中每条指令占用4个字节，上述的信息表明是崩溃在函数的第16个字节的偏移地址处，也就是函数的第5条指令处)。崩溃异常类型显示为`EXC_BAD_ACCESS`表明是产生了无效的地址的读写访问，整个崩溃函数调用栈中没应用程序中的任何上下文信息

 可以来看看这个函数实现的汇编代码指令开头片段：
 ```
 ;iOS10以后的objc_msgSend的部分实现代码。
 _objc_msgSend:
 00000001800bc140<+0>    cmp     x0, #0x0     ;判断对象receiver和0进行比较
 00000001800bc144<+4>    b.le    0x1800bc1ac    ;如果对象指针为0或者高位为1则执行特殊处理跳转。
 00000001800bc148<+8>    ldr     x13, [x0]           ;取出对象的isa指针赋值给x13
 00000001800bc14c<+12>   and x16, x13, #0xffffffff8   ;得到对象的Class对象指针赋值给x16
 00000001800bc150<+16>   ldp x10, x11, [x16, #0x10]    ;取出Class对象的cache成员分别保存到x10,x11寄存器中 
 -----------------------------------------------------------上面的指令就是代码崩溃处。
 00000001800bc154<+20>   and     w12, w1, w11

 ```


### 常见的崩溃异常分析定位方法

当出现了没有上下文的崩溃异常调用栈时，并不是对它束手无策。除了可以根据异常类型(signal的类型)分析外，还可以借助搜索引擎以及一些常见的问题解答站点来寻找答案，当然还可以借助下面列出几种定位和分析的方法


- 1、开源代码法

这个方法其实很简单，苹果其实开源了非常多的基础库的源代码，因此当程序崩溃在这些开源的基础库上时就可以去下载对应的基础库的源代码进行阅读。然后从源代码上进行问题的分析，从而找到产生异常崩溃的原因。你可以从[这里](https://opensource.apple.com)处去下载开源的最新的源代码。这种方法的缺点是并不是所有的代码都是开源的，而且开源的代码并不一定是你真机设备上运行的iOS版本。因此这种方法只能是一种辅助方法。

 - 2、方法符号断点法
采用这种方法时，确保你手头上要有一台和产生崩溃异常问题的操作系统版本相同的真机设备，以方便联机调试和运行

设置符号断点的方法或者函数名时可以有如下的选择

    - 1、如果产生崩溃的栈顶是一个OC对象的方法则可以直接用这个类名和方法名来设置符号断点。

    - 2、如果产生崩溃的栈顶是一个通用的C函数比如objc_msgSend、free、objc_release则考虑用函数调用栈的第二层函数和方法名来设置符号断点。比如文本例子中的-[UIWebDocumentView _updateSubviewCaches]方法。
    
    - 3、如果产生崩溃的函数调用栈顶是一个没有对外暴露的C函数，因为这种函数设置符号断点的难度比交大，所以往往考虑采用函数调用栈的第二层函数或者方法名来做为符号断点

- 3、手动重现法

有时候即使你设置了符号断点，场景依然无法重现，这时候就需要采用一些特殊的手段，那就是手动的执行方法调用。实现方式很简单就是在某个演示代码中人为的进行崩溃栈顶函数的调用。就比如上面的例子当[UIWebDocumentView _updateSubviewCaches]方法一直不被执行时，就可以自己手动的去创建一个UIWebDocumentView对象，并手动的调用对应的方法_updateSubviewCaches即可。这里存在的两个问题是有可能这个类并没有对外进行声明，或者我们并不知道方法的参数类型或者需要传递的值。对于第一个问题解决的方法可以采用NSClassFromString来得到类信息并进行对象创建。而第二个问题则可以借助一些工具比如class-dump或者一些其他的手段来确认方法的参数个数和参数类型。总之，目的就是为了能够进入函数的断点，甚至都可以在不知道如何传递参数时将所有的参数都传值为0或者nil来临时解决问题。下面就是模拟崩溃函数的调用实现代码：
```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
// Override point for customization after application launch.

//因为类名和方法名都未对外公开，我们可以借助一些技术手段来让某个特定的方法执行，目的是为了能够进入到方法的内部实现。
Class cls = NSClassFromString(@"UIWebDocumentView");
id obj = [[cls alloc] init];
SEL sel = sel_registerName("_updateSubviewCaches");
[obj performSelector:sel];

//...
}
```
测试代码可以写在任何一个地方，这里为了方便就在程序启动处加上测试代码。等代码编写完毕后，就可以为方法设置符号断点。这样当程序一运行时就一定能够进入到这个函数的内部去。一旦函数被执行后出现了断点，就可以按照第2种方法中的介绍进行崩溃分析了。

 

文章参考自

[深入iOS系统底层之crash解决方法介绍](https://www.jianshu.com/p/cf0945f9c1f8)

[iOS实录14：浅谈iOS Crash（一）](https://www.jianshu.com/p/3261493e6d9e)

[iOS异常捕获](http://www.iosxxx.com/blog/2015-08-29-iosyi-chang-bu-huo.html)





















