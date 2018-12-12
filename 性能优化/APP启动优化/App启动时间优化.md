## App启动时间优化
这篇文章我们研究步骤如下
- 1、APP启动流程
- 2、计算各个流程启动所消耗的时间
- 3、如何进行APP启动优化

### APP启动流程
APP的启动可以分为两大类
- 1、冷启动：从零开始启动APP
- 2、热启动：APP已经存在内存当中，但是后台存活着，再次点击图标启动APP

`而我们对APP启动时间的优化主要是针对冷启动进行优化的`。

想要了解冷启动，我们必须首先要知道APP冷启动的流程

![冷启动1](https://github.com/SunshineBrother/JHBlog/blob/master/性能优化/APP启动优化/冷启动1.png)


APP冷启动可以概括为三个阶段
- 1、dyld：加载动态库
- 2、RunTime方法
- 3、main函数初始化

**1、dyld**

`dyld(dynamic link editor)`，app的动态链接器，可以用来装在Mach-O文件（可执行文件、动态库等）

启动APP时，dyld所做的事情有

![冷启动2](https://github.com/SunshineBrother/JHBlog/blob/master/性能优化/APP启动优化/冷启动2.png)

真正的加载过程从exec()函数开始，exec()是一个系统调用。操作系统首先为进程分配一段内存空间，然后执行如下操作：
- 1、把App对应的可执行文件加载到内存。
- 2、把Dyld加载到内存。
- 3、Dyld进行动态链接。

具体内容
 - 1、加载动态库
    - Dyld从主执行文件的header获取到需要加载的所依赖动态库列表，然后它需要找到每个 dylib，而应用所依赖的 dylib 文件可能会再依赖其他 dylib，所以所需要加载的是动态库列表一个递归依赖的集合
- 2、Rebase和Bind
    - 1、Rebase在Image内部调整指针的指向。在过去，会把动态库加载到指定地址，所有指针和数据对于代码都是对的，而现在地址空间布局是随机化，所以需要在原来的地址根据随机的偏移量做一下修正
    - 2、Bind是把指针正确地指向Image外部的内容。这些指向外部的指针被符号(symbol)名称绑定，dyld需要去符号表里查找，找到symbol对应的实现
    

**2、RunTime方法**

![冷启动3](https://github.com/SunshineBrother/JHBlog/blob/master/性能优化/APP启动优化/冷启动3.png)

在Dyld阶段加载结束以后就进入了RunTime阶段

- 1、Objc setup
    - 1、注册Objc类 (class registration)
    - 2、把category的定义插入方法列表 (category registration)
    - 3、保证每一个selector唯一 (selector uniquing)
- 2、Initializers
    - 1、Objc的+load()函数
    - 2、C++的构造函数属性函数
    - 3、非基本类型的C++静态全局变量的创建(通常是类或结构体)



**3、main函数初始化**

APP的启动由dyld主导，将可执行文件加载到内存，顺便加载所有依赖的动态库
并由runtime负责加载成objc定义的结构
所有初始化工作结束后，dyld就会调用main函数
接下来就是UIApplicationMain函数，AppDelegate的application:didFinishLaunchingWithOptions:方法

这个里面往往是最占用启动时间的地方，同时也是我们最为可控的地方。

![冷启动4](https://github.com/SunshineBrother/JHBlog/blob/master/性能优化/APP启动优化/冷启动4.png)


早期由于业务比较简单，所有启动项都是不加以区分，简单地堆积到didFinishLaunchingWithOptions方法中，但随着业务的增加，越来越多的启动项代码堆积在一起，性能越来越差，启动也越来越占用时间。



### 计算各个流程启动所消耗的时间

一般而言，大家把iOS冷启动的过程定义为：从用户点击App图标开始到appDelegate didFinishLaunching方法执行完成为止。这个过程主要分为两个阶段：

- T1：main()函数之前，即操作系统加载App可执行文件到内存，然后执行一系列的加载&链接等工作，最后执行至App的main()函数。
- T2：main()函数之后，即从main()开始，到appDelegate的didFinishLaunchingWithOptions方法执行完毕。

 ![冷启动6](https://github.com/SunshineBrother/JHBlog/blob/master/性能优化/APP启动优化/冷启动6.png)
 
 **main()函数之前**

对于如何测试启动时间，Xcode 提供了一个很赞的方法，只需要在 Edit scheme -> Run -> Arguments 中将环境变量 DYLD_PRINT_STATISTICS 设为 1，就可以看到 main 之前各个阶段的时间消耗。

![冷启动5](https://github.com/SunshineBrother/JHBlog/blob/master/性能优化/APP启动优化/冷启动5.png)

**main()函数之前**

总共使用了1.1s
加载动态库：242.77ms
指针重定位：671.81ms
objc类初始化：52.86ms
各种其他初始化：171.33ms


**main()函数之后**

main 到 didFinishLaunching 结束或者第一个 ViewController 的viewDidAppear 都是作为 main 之后启动时间的一个度量指标。这个时间统计直接打点计算就可以，不过当遇到时间较长需要排查问题时，只统计两个点的时间其实不方便排查，目前见到比较好用的方式就是为把启动任务规范化、粒子化，针对每个任务都有打点统计，这样方便后期问题的定位和优化。

 

我们也可以借助一些图形化工具来动态分析

- Time Profiler
Time Profiler是Xcode自带的时间性能分析工具，它按照固定的时间间隔来跟踪每一个线程的堆栈信息，通过统计比较时间间隔之间的堆栈状态，来推算某个方法执行了多久，并获得一个近似值


- 火焰图
除了Time Profiler，火焰图也是一个分析CPU耗时的利器，相比于Time Profiler，火焰图更加清晰。火焰图分析的产物是一张调用栈耗时图片，之所以称为火焰图，是因为整个图形看起来就像一团跳动的火焰，火焰尖部是调用栈的栈顶，底部是栈底，纵向表示调用栈的深度，横向表示消耗的时间。一个格子的宽度越大，越说明其可能是瓶颈。分析火焰图主要就是看那些比较宽大的火苗。具体可以参考[如何读懂火焰图？](http://www.ruanyifeng.com/blog/2017/09/flame-graph.html)

 
 ### 优化启动时间
 
 
 









参考:

[[iOS]一次立竿见影的启动时间优化](https://www.jianshu.com/p/c1734cbdf39b)

[如何精确度量 iOS App 的启动时间](https://www.jianshu.com/p/c14987eee107)

[优化 App 的启动时间实践 iOS](http://www.cocoachina.com/ios/20180508/23315.html)

[iOS App冷启动治理：来自美团外卖的实践](https://juejin.im/post/5c0a17d6e51d4570cf60d102)



































