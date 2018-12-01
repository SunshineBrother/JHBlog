# JHBlog
 
iOS开发：我的初级到中级的晋级之路

******************************************************************************************************************
## 架构
- [1、浅谈MVC&变异MVC&MVP&MVVM](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/基础架构/1、MVC%26变异MVC%26MVP%26MVVM.md)
 
## 设计模式研究
**什么是设计模式**
在软件开发中，经过验证的，用于解决在特定环境下，重复出现的特定的问题的解决方案。
注意上面的提到的限定词，下面来详细说下
- 1、软件开发：其实各行各业都有模式可以套用，这里的设计模式指的是在软件开发领域
- 2、经过验证的：必须是经过大家公认和验证过的解决方案才算得上是设计模式，而不是每个人随便总结的解决方案都能算
- 3、特定环境：必须是在某个特定环境才可以使用该设计模式，因为不同的环境，就算同样的问题，解决方案也不同，所以不能脱离环境去谈使用设计模式
- 4、重复出现：因为只有重复出现的问题才有必要总结经验，形成固定的解决方案，再次遇到这样的问题就不用从头开始寻找解决方案，而是直接套用就可以了。
- 5、特定问题：软件开发领域没有银弹，不要指望一种设计模式就能包治百病。每种模式只是针对特定问题的解决方案，所以不要迷信设计模式，滥用设计模式。

常见的设计模式有23种，根据目的，我们可以把模型分为三类：创建型，结构型，行为型
- [UML了解](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/UML/UML类图几种关系的总结.md)

- Creational 创建型 5
- [Factory Method 工厂方法模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/1、工厂模式/工厂模式.md)
- Abstract Factory 抽象工厂模式
- Builder 建造者模式
- Prototype 原型模式
- Singleton 单例模式

-  Structural 结构型 7
- Adapter 适配器模式
- Bridge 桥接模式
- Composite 组合模式
- Decorator 装饰者模式
- Facade 外观模式
- Flyweight 享元模式
- Proxy 代理模式
- Behavioral 行为型 11
- Chain of responsibility 责任链模式
- Command 命令模式
- Interpreter 解释器模式
- Iterator 迭代器模式
- Mediator 中介模式
- Memento 备忘录模式
- Observer 观察者模式
- State 状态模式
- [Strategy 策略模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/2、策略模式/策略模式.md)
- Template Method 模板方法模式
- Visitor 访问者模式


*********************************************************
## iOS高级进发
[OC源码下载地址](https://opensource.apple.com/tarballs/)

GNUstep是GNU计划的项目之一，它将Cocoa的OC库重新开源实现了一遍
源码地址：http://www.gnustep.org/resources/downloads.php
虽然GNUstep不是苹果官方源码，但还是具有一定的参考价值

### iOS底层
- [1、一个NSObject对象占用多少内存](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/1、一个NSObject对象占用多少内存.md)
- [2、OC对象的分类](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/2、OC对象的分类.md)
- [3、KVO实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/3、KVO.md)
- [4、KVC实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/4、KVC.md)
- [5、分类](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/分类/1、分类的实现原理.md)
    - [5.1、分类的实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/分类/1、分类的实现原理.md)
    - [5.2、Load和Initialize实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/分类/2、Load和Initialize实现原理.md)
- [6、Block底层解密](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/7、Block底层解密.md)
 - [7、RunLoop实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/8、RunLoop.md)
 - [8、RunTime实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/0、运行时.md)
    - [8.1、isa解析](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/1、isa.md)
    - [8.2、方法缓存](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/2、方法缓存.md)
    - [8.3、objc_msgSend执行流程](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/3、objc_msgSend执行流程.md)
    - [8.4、@dynamic关键字](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/4、@dynamic关键字.md)
    - [8.5、Class和SuperClass区别](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/5、Class%26SuperClass.md)
    - [8.6、isKindOfClass和isMemberOfClass区别 ](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/6、isMemberOfClass%26.isKindOfClassmd.md)
    - [8.7、RunTime的相关API](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/7、API.md)
- [9、多线程](1、多线程面试题)
    - [9.1、多线程面试题](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/1、多线程面试题.md)
    - [9.2、多线程之NSThread](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/2、NSThread介绍.md)
    - [9.3、多线程之GCD](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/3、GCD介绍.md)
    - [9.4、多线程之NSOperation](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/4、NSOperation介绍.md)
    - [9.5、多线程之线程安全](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/5、线程安全.md)
    - [9.6、死锁](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/6、死锁.md)
    - [9.7、线程之间的通讯](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/8、线程之间的通讯.md)
    - [9.8、GCD高级用法](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/7、GCD高级用法.md)
    - [9.9、深入浅出 iOS 并发编程](https://www.jianshu.com/p/39d6edb54d24)
- [10、内存管理]()  
    - [10.1、定时器target的内存泄漏](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/1、定时器.md)
    - [10.2、Tagged Pointer](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/2、tagged%20pointer.md)
    - [10.3、copy&retain&strong原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/3、copy%26retain%26strong原理.md)
    - [10.4、weak&assign原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/4、weak%26assign原理.md)
    - [10.5、@property 的本质是什么](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/5、%40property%20的本质是什么.md)
    - [10.6、autorelease原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/6、autorelease原理.md)
    - [10.7、atomic 一定是线程安全的吗](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/7、atomic%20一定是线程安全的吗.md)
    - [10.8、dealloc原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/8、dealoc原理.md)
    - [10.9、引用计数的存储](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/9、引用计数的存储.md)
  
    


### iOS大杂烩

- 1、[LLDB使用](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB.md)
- 2、[基本数据类型](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/打印各种数据类型.md)
- 3、[App信息监控](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/App需要监控信息.md)
- 4、[Crash系列]()
    - [1、Crash产生原因](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/1、Crash产生原因.md)
    - [2、Crash日志收集](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/2、Crash日志收集.md)
    - [3、Crash日志分析](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/3、Crash日志分析.md)
    - [4、NSException抛出异常](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/4、NSException抛出异常.md)
    - [5、符号表&dSYM](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/5、符号表.md)
- 5、[armv7,armv7s,arm64,i386,x86_64 简单了解](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/armv7%2Carmv7s%2Carm64%2Ci386%2Cx86_64.md)
- 6、[performSelector的原理以及用法](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/performSelector的原理以及用法.md)
- 7、[更新cocoapod](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/更新cocoapod.md)
- 8、[为什么不能在子线程中刷新UI](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/为什么不能在子线程中刷新UI.md)
- 9、[UIViewController的生命周期](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController的生命周期.md)
- 10、[ios真机调试包路径及配置文件路径](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/ios真机调试包路径及配置文件路径.md)
- 11、[UIView的继承链](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIView的继承链.md)
- 12、[frame和bounds的区别](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/frame和bounds的区别.md)
  
  *********************************************************
  ## RxSwift学习历程
  ### 基础概念
  - [1、Observable - 可被监听的序列](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/1、创建序列.md)
  - [2、除了Observable其他的可被监听的序列](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/1.1、可被监听的序列.md)
  - [3、subscribe订阅](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/2、subscribe订阅.md)
  - [4、观察者（Observer）](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/3、observer.md)
  - [5、Subjects介绍](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/4、Subjects介绍.md)
  - [6、Schedulers - 调度器](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/5、Schedulers%20-%20调度器.md)
  - [7、Error Handling 错误处理 ](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/6、ErrorHandling错误处理.md)
  - [8、操作符]()
  - [8.1、变换操作符](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/7.1、变换操作符.md)
  - [8.2、过滤操作符](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/7.2、过滤操作符.md)
  - [8.3、结合操作](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/7.3、结合操作.md)
  - [9、Driver](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/8、Driver.md)
  
  
  ### UI操作
  - [1、UILabel](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/9、UI控件：UILabel.md)
  - [2、UITextField 与 UITextView](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/10、UI控件：UITextField、UITextView.md)
  - [3、UIButton](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/11、UI控件UIButton.md)
  - [4、RxSwift接收事件](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/13、rxswift接收事件.md)
  - [5、MVVM案例：登录](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/14、MVVM.md)
  - [6、UITableView 的基本用法](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/15、UITableView%20的基本用法.md)
  


******************************************************************************************************************
## 第三方

**[第三方](https://github.com/SunshineBrother/JHBlog/blob/master/第三方/第三方.md)**


******************************************************************************************************************
## 实用文章
 **博客**
- 1、[Swift 文章精选](https://github.com/ipader/SwiftGuide/blob/master/Featured-Articles.md)
- 2、[一个国外视频学习网站](https://academy.realm.io/cn/section/apple/)


**UI界面**
- 1、[UITableView]()
    - [如何在 iOS 中实现一个可展开的 Table View](https://swift.gg/2015/12/03/expandable-table-view/)
- 2、[iOS设计指南](https://www.ui.cn/detail/32167.html)
- 3、[iOS开发 将App内部功能块生成桌面快捷方式](https://www.jianshu.com/p/9fb0824f95fe?utm_source=desktop&utm_medium=timeline)

**布局**
- 1、[ios中的UI自适应](https://academy.realm.io/cn/posts/gotocph-sam-davies-adaptive-ui-ios/)

**动画**
- 1、[内存恶鬼drawRect](https://bihongbo.com/2016/01/03/memoryGhostdrawRect/)


**WebView**
- 1、[iOS WebView生成长截图的第三种解决方案](https://juejin.im/post/5b9d145ae51d450e7579d1e5)
- 2、[WKWebView使用指南](https://www.jianshu.com/p/97faf098e673)
- 3、[UITableViewCell含有WebView的自适应高度新解决方案](https://juejin.im/post/5be3960af265da616f6f7468)

**国际化**

- 1、[iOS国际化详解](https://www.jianshu.com/p/7e1c7c210ec2)
- 2、[3分钟实现iOS语言本地化/国际化（图文详解）](https://www.jianshu.com/p/88c1b65e3ddb)


**Crash分析**

- 1、[手把手教你查看和分析iOS的crash崩溃](https://juejin.im/post/5b8f8e726fb9a05d185ec651)
- 2、[漫谈 iOS Crash 收集框架](https://mp.weixin.qq.com/s?__biz=MjM5NTIyNTUyMQ==&mid=208483273&idx=1&sn=37ee88e06e7426f59f3074c536370317&scene=21)
- 3、[全面的理解和分析iOS的崩溃日志](http://www.cocoachina.com/ios/20171026/20921.html)
- 4、[iOS实录14：浅谈iOS Crash（一）](https://www.jianshu.com/p/3261493e6d9e)
- 5、[质量监控-保护你的crash](https://www.jianshu.com/p/c8f731d18518)
- 6、[深入iOS系统底层之crash解决方法介绍](https://www.jianshu.com/p/cf0945f9c1f8)
- 7、[Baymax：网易iOS App运行时Crash自动防护实践](https://mp.weixin.qq.com/s?__biz=MzUxMzcxMzE5Ng==&mid=2247488311&amp;idx=1&amp;sn=0db090c8d4a5efafa47f00af4b3f174f&source=41#wechat_redirect)
- 8、[iOS 启动连续闪退保护方案](https://wereadteam.github.io/2016/05/23/GYBootingProtection/)


**锁**

- 1、[lock](https://github.com/bestswifter/blog/blob/master/articles/ios-lock.md)

**安全性**

- 1、[从爬虫攻击者角度谈客户端 API 安全设计](https://mp.weixin.qq.com/s/yv9Ph_8pzej3Wasbsc-fXQ)
 
 **性能优化**
 
 - 1、[深入剖析Swift性能优化](https://mp.weixin.qq.com/s/U95QmOOjeXkk-yC23cuZCQ)
 - 2、[iOS 性能优化的探索](https://www.jianshu.com/p/b8346c1a4145)
 - 3、[如何将 iOS 项目的编译速度提高5倍](https://link.jianshu.com/?t=https%3A%2F%2Fzhuanlan.zhihu.com%2Fp%2F27584726)
- 4、[使用 ASDK 性能调优 - 提升 iOS 界面的渲染性能](https://link.jianshu.com/?t=http%3A%2F%2Fdraveness.me%2Fasdk-rendering)
- 5、[微信读书 iOS 性能优化总结](https://link.jianshu.com/?t=https%3A%2F%2Fwereadteam.github.io%2F2016%2F05%2F03%2FWeRead-Performance%2F)
- 6、[微信读书 iOS 质量保证及性能监控](https://link.jianshu.com/?t=https%3A%2F%2Fwereadteam.github.io%2F2016%2F12%2F12%2FMonitor%2F)
- 7、[页面间跳转的性能优化(一)](https://www.jianshu.com/p/77847c0027c9)
- 8、[页面间跳转的性能优化(二)](https://www.jianshu.com/p/92532c2b1d55)
- 9、[iOS 瘦包常见方式梳理](https://mp.weixin.qq.com/s?__biz=MzA5NzMwODI0MA==&mid=2647761547&idx=1&sn=2f84d8b9eeb134ed0c5cb7142ef0caa9&chksm=8887d9b4bff050a2cc850ab243282f25894cc5eae5596e1b3ad52a6a69de030bbc571d1f74be#rd)


**性能检测工具**
- 1、[Allocations:分析静态内存分配](https://github.com/LeoMobileDeveloper/Blogs/blob/master/Instruments/Allocations.md)

**导航栏**
 - 1、[iOS系统中导航栏的转场解决方案与最佳实践](https://juejin.im/post/5bd2bf936fb9a05cef177644)
 
 **调试**
 - 1、[iOS调试-LLDB学习总结](https://www.jianshu.com/p/d6a0a5e39b0e)
 - 2、[iOS各种调试技巧豪华套餐](http://www.cnblogs.com/daiweilai/p/4421340.html)
 - 3、[Safari/Chrome调试WebView](https://blog.csdn.net/hello_hwc/article/details/80721246)
 
 **组件化**
- 1、[iOS 从零到一搭建组件化项目框架](https://www.jianshu.com/p/59c2d2c4b737)
- 2、[iOS 响应式架构](https://link.jianshu.com/?t=http%3A%2F%2Fblog.mrriddler.com%2F2017%2F06%2F28%2FiOS%25E5%2593%258D%25E5%25BA%2594%25E5%25BC%258F%25E6%259E%25B6%25E6%259E%2584%2F)
- 3、[iOS 组件化方案探索](https://link.jianshu.com/?t=http%3A%2F%2Fwereadteam.github.io%2F2016%2F03%2F19%2FiOS-Component%2F)
- 4、[iOS 组件化 —— 路由设计思路分析](https://www.jianshu.com/p/76da56b3bd55)
- 5、[iOS组件化方案](https://mp.weixin.qq.com/s?__biz=MzA5NzMwODI0MA==&mid=2647761549&idx=1&sn=90880890bb0de4c03bc94a9105ce78bc&chksm=8887d9b2bff050a4b42dbef4e69635dc53d3360e88ce7f6fef30bb8b257b59321c9a13ef0f34#rd)


**设计模式**
- 1、[深度重构UIViewController](https://zhuanlan.zhihu.com/p/23161172)

 **事件执行**
 - 1、[iOS触摸事件全家桶](https://www.jianshu.com/p/c294d1bd963d)
 
 **数据库**
 - 1、[core Data线程大揭秘](https://academy.realm.io/cn/posts/marcus-zarra-core-data-threading/)
 - 2、[Realm数据库基础教程](http://www.cocoachina.com/ios/20150505/11756.html)
 
 **设计模式**
 - 1、[Category 特性在 iOS 组件化中的应用与管控](https://mp.weixin.qq.com/s/5ucpVa6ku4b9_pfMP9CqlQ)
 - 2、[设计模式:实现了 Gof 的 23 种设计模式](https://github.com/CyC2018/InnterviewNotes/blob/master/notes/设计模式.md)
 - 3、[面向对象思想:三大原则（继承、封装、多态）、类图、设计原则](https://github.com/CyC2018/InnterviewNotes/blob/master/notes/面向对象思想.md)
 
 **算法**
 - 1、[剑指 Offer 题解:目录根据原书第二版进行编排，代码和原书有所不同，尽量比原书更简洁](https://github.com/CyC2018/CS-Notes/blob/master/notes/剑指%20offer%20题解.md)
 - 2、[Leetcode 题解](https://github.com/CyC2018/InnterviewNotes/blob/master/notes/Leetcode%20题解.md)
 - 3、[算法:排序、并查集、栈和队列、红黑树、散列表。](https://github.com/CyC2018/InnterviewNotes/blob/master/notes/算法.md)
 
 
 **网络**
 
 - 1、[计算机网络:物理层、链路层、网络层、运输层、应用层](https://github.com/CyC2018/InnterviewNotes/blob/master/notes/计算机网络.md)
 - 2、[HTTP:方法、状态码、Cookie、缓存、连接管理、HTTPs、HTTP 2.0](https://github.com/CyC2018/InnterviewNotes/blob/master/notes/HTTP.md)
 - 3、[Socket:I/O 模型、I/O 多路复用](https://github.com/CyC2018/InnterviewNotes/blob/master/notes/Socket.md)
 - 4、[移动App 网络优化细节探讨](https://www.jianshu.com/p/0d5c574b8eff)
 
 **Git**
 - 1、[Git：一些 Git 的使用和概念](https://github.com/CyC2018/InnterviewNotes/blob/master/notes/Git.md)
 - 2、[如何利用GitHub进行代码审查](https://academy.realm.io/cn/posts/codereview-howto/)
 
  **其他**
  - 1、[聊聊移动端跨平台开发的各种技术](http://fex.baidu.com/blog/2015/05/cross-mobile/)
 
 
 ## 大公司架构
 
 **支付宝客户端架构解析**
- 1、[开篇 | 模块化与解耦式开发在蚂蚁金服 mPaaS 深度实践探讨](https://juejin.im/post/5bc41d80f265da0aaa053ca5)
- 2、[口碑 App 各 Bundle 之间的依赖分析指南](https://juejin.im/post/5bc5c46be51d450e95105048)
- 3、[源码剖析 | 蚂蚁金服 mPaaS 框架下的 RPC 调用历程](https://juejin.im/post/5bc850caf265da0abf7d195d)
- 4、[支付宝移动端动态化方案实践](https://juejin.im/post/5bd3f516518825279a5f9694)
- 5、[支付宝客户端架构解析：iOS 容器化框架初探](https://juejin.im/post/5bdc19cbf265da614b117217)
- 5、[支付宝客户端架构解析：iOS 客户端启动性能优化初探](https://juejin.im/post/5bee3825e51d456d6b6f9486)

**iOS应用架构**
- 1、[iOS应用架构谈 开篇](https://casatwy.com/iosying-yong-jia-gou-tan-kai-pian.html) 
- 2、[iOS应用架构谈 view层的组织和调用方案](https://casatwy.com/iosying-yong-jia-gou-tan-viewceng-de-zu-zhi-he-diao-yong-fang-an.html) 
- 3、[iOS应用架构谈 网络层设计方案](https://casatwy.com/iosying-yong-jia-gou-tan-wang-luo-ceng-she-ji-fang-an.html) 
- 4、[iOS应用架构谈 本地持久化方案及动态部署](https://casatwy.com/iosying-yong-jia-gou-tan-ben-di-chi-jiu-hua-fang-an-ji-dong-tai-bu-shu.html) 
- 5、[iOS应用架构谈 组件化方案](https://casatwy.com/iOS-Modulization.html)


 
*********************************************************
 
## 工具
这里记载了一些常用的工具，有许多都是转载的别人的博客，里面我有写转载地址，如果有作者感觉不适，请联系我，我会及时停止转载的


- 1、[如何优雅地使用Sublime Text](https://github.com/SunshineBrother/JHBlog/blob/master/工具/如何优雅地使用Sublime%20Text.md)
- 2、[官方 Swift 风格指南](https://github.com/SunshineBrother/JHBlog/blob/master/工具/官方%20Swift%20风格指南.md)
- 3、[iOS 程序员效率提升利器之 AppleScript](http://mrpeak.cn/blog/ios-applescript/)
- 4、[NPM 使用介绍](http://www.runoob.com/nodejs/nodejs-npm.html)
 - 5、[免费API](https://www.apishop.net/#/)

















