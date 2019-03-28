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

![冷启动1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动1.png)


APP冷启动可以概括为三个阶段
- 1、dyld：加载镜像，动态库
- 2、RunTime方法
- 3、main函数初始化

**1、dyld**

`dyld(dynamic link editor)`，app的动态链接器，可以用来装在Mach-O文件（可执行文件、动态库等）

启动APP时，dyld所做的事情有

![冷启动2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动2.png)

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

![冷启动3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动3.png)

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

![冷启动4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动4.png)


早期由于业务比较简单，所有启动项都是不加以区分，简单地堆积到didFinishLaunchingWithOptions方法中，但随着业务的增加，越来越多的启动项代码堆积在一起，性能越来越差，启动也越来越占用时间。



### 计算各个流程启动所消耗的时间

一般而言，大家把iOS冷启动的过程定义为：从用户点击App图标开始到appDelegate didFinishLaunching方法执行完成为止。这个过程主要分为两个阶段：

- T1：main()函数之前，即操作系统加载App可执行文件到内存，然后执行一系列的加载&链接等工作，最后执行至App的main()函数。
- T2：main()函数之后，即从main()开始，到appDelegate的didFinishLaunchingWithOptions方法执行完毕。

 ![冷启动6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动6.png)
 
 **main()函数之前**

对于如何测试启动时间，Xcode 提供了一个很赞的方法，只需要在 Edit scheme -> Run -> Arguments 中将环境变量 DYLD_PRINT_STATISTICS 设为 1，就可以看到 main 之前各个阶段的时间消耗。

![冷启动5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动5.png)

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
 
 
启动时间优化分成两部分
 - T1：main()函数之前，即操作系统加载App可执行文件到内存，然后执行一系列的加载&链接等工作，最后执行至App的main()函数。
 - T2：main()函数之后，即从main()开始，到appDelegate的didFinishLaunchingWithOptions方法执行完毕。
 
 ![冷启动6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动6.png)
 
 
 #### main()函数之前 
 
 ![冷启动1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动1.png)
 

App开始启动后，系统首先加载可执行文件（自身App的所有.o文件的集合），然后加载动态链接库dyld，dyld是一个专门用来加载动态链接库的库。 执行从dyld开始，dyld从可执行文件的依赖开始, 递归加载所有的依赖动态链接库。 
动态链接库包括：iOS 中用到的所有系统 framework，加载OC runtime方法的libobjc，系统级别的libSystem，例如libdispatch(GCD)和libsystem_blocks (Block)。
 
 其实无论对于系统的动态链接库还是对于App本身的可执行文件而言，他们都算是image（镜像），而每个App都是以image(镜像)为单位进行加载的
 
**什么是image**
 
- 1.executable可执行文件 比如.o文件。 
- 2.dylib 动态链接库 framework就是动态链接库和相应资源包含在一起的一个文件夹结构。 
- 3.bundle 资源文件 只能用dlopen加载，不推荐使用这种方式加载。
 
 除了我们App本身的可行性文件，系统中所有的framework比如UIKit、Foundation等都是以动态链接库的方式集成进App中的。
 
 **系统使用动态链接有几点好处**
 
 - 1、代码共用：很多程序都动态链接了这些 lib，但它们在内存和磁盘中中只有一份
 - 2、易于维护：由于被依赖的 lib 是程序执行时才链接的，所以这些 lib 很容易做更新，比如libSystem.dylib 是 libSystem.B.dylib 的替身，哪天想升级直接换成libSystem.C.dylib 然后再替换替身就行了
 - 3、减少可执行文件体积：相比静态链接，动态链接在编译时不需要打进去，所以可执行文件的体积要小很多。
 
 **什么是ImageLoader**
 
 image 表示一个二进制文件(可执行文件或 so 文件)，里面是被编译过的符号、代码等，所以 ImageLoader 作用是将这些文件加载进内存，且每一个文件对应一个ImageLoader实例来负责加载
 
 分两步
 
 - 1、在程序运行时它先将动态链接的 image 递归加载 (也就是上面测试栈中一串的递归调用的时刻)
 - 2、再从可执行文件 image 递归加载所有符号。
 
 **动态链接库加载的具体流程**
 
 动态链接库的加载步骤具体分为5步：
 
- 1、load dylibs image 读取库镜像文件
- 2、Rebase image
- 3、Bind image
- 4、Objc setup
- 5、 initializers

**load dylibs image**

在每个动态库的加载过程中， dyld需要：

- 1、分析所依赖的动态库
- 2、找到动态库的mach-o文件
- 3、打开文件
- 4、验证文件
- 5、在系统核心注册文件签名
- 6、对动态库的每一个segment调用mmap()

通常的，一个App需要加载100到400个dylibs， 但是其中的系统库被优化，可以很快的加载。 针对这一步骤的优化有：

- 1、减少非系统库的依赖
- 2、合并非系统库
- 3、使用静态资源，比如把代码加入主程序



**rebase/bind**


由于ASLR(address space layout randomization)的存在，可执行文件和动态链接库在虚拟内存中的加载地址每次启动都不固定，所以需要这2步来修复镜像中的资源指针，来指向正确的地址。 rebase修复的是指向当前镜像内部的资源指针； 而bind指向的是镜像外部的资源指针。 
rebase步骤先进行，需要把镜像读入内存，并以page为单位进行加密验证，保证不会被篡改，所以这一步的瓶颈在IO。bind在其后进行，由于要查询符号表，来指向跨镜像的资源，加上在rebase阶段，镜像已被读入和加密验证，所以这一步的瓶颈在于CPU计算。 
通过命令行可以查看相关的资源指针:

>xcrun dyldinfo -rebase -bind -lazy_bind myApp.App/myApp


优化该阶段的关键在于减少__DATA segment中的指针数量。我们可以优化的点有：

- 1、减少Objc类数量， 减少selector数量
- 2、减少C++虚函数数量
- 3、转而使用swift stuct（其实本质上就是为了减少符号的数量）


**Objc setup**

这一步主要工作是:

- 1、注册Objc类 (class registration)
- 2、把category的定义插入方法列表 (category registration)
- 3、保证每一个selector唯一 (selctor uniquing)


**initializers**

以上三步属于静态调整(fix-up)，都是在修改__DATA segment中的内容，而这里则开始动态调整，开始在堆和堆栈中写入内容。 在这里的工作有：

- 1、Objc的+load()函数
- 2、C++的构造函数属性函数 形如attribute((constructor)) void DoSomeInitializationWork()
- 3、非基本类型的C++静态全局变量的创建(通常是类或结构体)(non-trivial initializer) 比如一个全局静态结构体的构建，如果在构造函数中有繁重的工作，那么会拖慢启动速度




***对于main()调用之前的耗时我们可以优化的点有***

- 1、减少不必要的framework，因为动态链接比较耗时
- 2、check framework应当设为optional和required，如果该framework在当前App支持的所有iOS系统版本都存在，那么就设为required，否则就设为optional，因为optional会有些额外的检查
- 3、合并或者删减一些OC类，关于清理项目中没用到的类 
- 4、删减没有被调用到或者已经废弃的方法
- 5、将不必须在+load方法中做的事情延迟到+initialize中
- 6、尽量不要用C++虚函数(创建虚函数表有开销)

这个介绍一些工具
- 1、去除没有用到的资源： https://github.com/tinymind/LSUnusedResources
- 2、利用AppCode：https://www.jetbrains.com/objc/  检测未使用的代码：菜单栏 -> Code -> Inspect Code
- 3、可借助第三方工具解析LinkMap文件： https://github.com/huanxsd/LinkMap

生成LinkMap文件，可以查看可执行文件的具体组成

 ![冷启动7](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动7.png)


#### main()函数之后

其实在main()函数之前我们能够进行优化的部分并没有多少，而且操作性也不大，更多的优化其实还是我们对我们代码的优化，很多启动时间的占用更多的是因为我们代码布局的问题。

 
![冷启动4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动4.png)

相当一部分的项目都是所有的启动项不加分类一股脑的堆积在了`didFinishLaunch`中，其实这是相当不合理的。


通过对SDK的梳理和分析，我们发现启动项也需要根据所完成的任务被分类，有些启动项是需要刚启动就执行的操作，如Crash监控、统计上报等，否则会导致信息收集的缺失；有些启动项需要在较早的时间节点完成，例如一些提供用户信息的SDK、定位功能的初始化、网络初始化等；有些启动项则可以被延迟执行，如一些自定义配置，一些业务服务的调用、支付SDK、地图SDK等。我们所做的分阶段启动，首先就是把启动流程合理地划分为若干个启动阶段，然后依据每个启动项所做的事情的优先级把它们分配到相应的启动阶段，优先级高的放在靠前的阶段，优先级低的放在靠后的阶段。

 
 ![冷启动8](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动8.png)
 
 
 我们虽然把各个功能的优先级给整理了出来，但是我们启动还是需要很长时间，我们并没有减少启动时间。这个时候我们需要充分利用串行队列
 - 1、启动页的利用
 - 2、广告页的利用
 - 3、`rootViewController`的`viewController`中`viewDidAppear`的利用
 - 4、缓存&首页预请求
 
 **闪屏页的使用**
 
 现在许多App在启动时并不直接进入首页，而是会向用户展示一个持续一小段时间的闪屏页，如果使用恰当，这个闪屏页就能帮我们节省一些启动时间。因为当一个App比较复杂的时候，启动时首次构建App的UI就是一个比较耗时的过程，假定这个时间是0.2秒，如果我们是先构建首页UI，然后再在Window上加上这个闪屏页，那么冷启动时，App就会实实在在地卡住0.2秒，但是如果我们是先把闪屏页作为App的RootViewController，那么这个构建过程就会很快。因为闪屏页只有一个简单的ImageView，而这个ImageView则会向用户展示一小段时间，这时我们就可以利用这一段时间来构建首页UI了，一举两得
 
 ![冷启动9](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/冷启动9.png)
 
 
 **广告页的利用**
 
 广告页好多也是需要等几秒的，我们也可以在加载广告页的时候，先立马展示一个空壳的 UI 给用户，然后在 viewDidAppear 方法里进行数据加载解析渲染等一系列操作，这样一来，用户已经看到界面了，就不会觉得是启动慢，这个时候的等待就变成等待数据请求了，这样就把这部分时间转嫁出去了。
 
 
 **viewDidAppear的利用**
 
 我们一些比较靠后的SDK的初始化我们可以在首页已经加载出来以后在初始化
 
 
 **缓存&首页预请求**
 
 使用缓存
 
 
 
 ### 总结
 
 为此，我专门建了一个类来负责启动事件，为什么呢？如果不这么做，那么此次优化以后，以后再引入第三方的时候，别的同事可能很直觉的就把第三方的初始化放到了 didFinishLaunchingWithOptions 方法里，这样久而久之， didFinishLaunchingWithOptions 又变得不堪重负，到时候又要专门花时间来做重复的优化。
 
 ```
 /**
 * 注意: 这个类负责所有的 didFinishLaunchingWithOptions 延迟事件的加载.
 * 以后引入第三方需要在 didFinishLaunchingWithOptions 里初始化或者我们自己的类需要在 didFinishLaunchingWithOptions 初始化的时候,
 * 要考虑尽量少的启动时间带来好的用户体验, 所以应该根据需要减少 didFinishLaunchingWithOptions 里耗时的操作.
 * 第一类: 比如日志 / 统计等需要第一时间启动的, 仍然放在 didFinishLaunchingWithOptions 中.
 * 第二类: 比如用户数据需要在广告显示完成以后使用, 所以需要伴随广告页启动, 只需要将启动代码放到 startupEventsOnADTimeWithAppDelegate 方法里.
 * 第三类: 比如直播和分享等业务, 肯定是用户能看到真正的主界面以后才需要启动, 所以推迟到主界面加载完成以后启动, 只需要将代码放到 startupEventsOnDidAppearAppContent 方法里.
 */
 
 #import <Foundation/Foundation.h>
 
 NS_ASSUME_NONNULL_BEGIN
 
 @interface BLDelayStartupTool : NSObject
 
 /**
 * 启动伴随 didFinishLaunchingWithOptions 启动的事件.
 * 启动类型为:日志 / 统计等需要第一时间启动的.
 */
 + (void)startupEventsOnAppDidFinishLaunchingWithOptions;
 
 /**
 * 启动可以在展示广告的时候初始化的事件.
 * 启动类型为: 用户数据需要在广告显示完成以后使用, 所以需要伴随广告页启动.
 */
 + (void)startupEventsOnADTime;
 
 /**
 * 启动在第一个界面显示完(用户已经进入主界面)以后可以加载的事件.
 * 启动类型为: 比如直播和分享等业务, 肯定是用户能看到真正的主界面以后才需要启动, 所以推迟到主界面加载完成以后启动.
 */
 + (void)startupEventsOnDidAppearAppContent;
 
 @end
 
 NS_ASSUME_NONNULL_END
 
 
 ```
 
 
 




参考:

[[iOS]一次立竿见影的启动时间优化](https://www.jianshu.com/p/c1734cbdf39b)

[如何精确度量 iOS App 的启动时间](https://www.jianshu.com/p/c14987eee107)

[优化 App 的启动时间实践 iOS](http://www.cocoachina.com/ios/20180508/23315.html)

[iOS App冷启动治理：来自美团外卖的实践](https://juejin.im/post/5c0a17d6e51d4570cf60d102)

[APP启动优化的一次实践](https://icetime17.github.io/2018/01/01/2018-01/APP启动优化的一次实践/)

[优化 App 的启动时间](http://yulingtianxia.com/blog/2016/10/30/Optimizing-App-Startup-Time/)

[今日头条iOS客户端启动速度优化](https://techblog.toutiao.com/2017/01/17/iosspeed/#more)




























