# JHBlog
 
iOS开发：我的初级到中级的晋级之路

 
*********************************************************
## iOS高级进发
[OC源码下载地址](https://opensource.apple.com/tarballs/)

[苹果开发文档](https://developer.apple.com/documentation/)

[如何阅读苹果开发文档](https://mp.weixin.qq.com/s/UgwSNSahYzQm14Zwtfk_2w)


GNUstep是GNU计划的项目之一，它将Cocoa的OC库重新开源实现了一遍
源码地址：http://www.gnustep.org/resources/downloads.php
虽然GNUstep不是苹果官方源码，但还是具有一定的参考价值


******************************************************************************************************************

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
  
    
    
******************************************************************************************************************


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
- 9、[UIViewController](https://github.com/SunshineBrother/JHBlog/tree/master/iOS知识点/iOS大杂烩/UIViewController)
    - 1、[UIViewController的生命周期](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/UIViewController的生命周期.md)
    - 2、[UIViewController重构](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/UIViewController重构.md)
- 10、[ios真机调试包路径及配置文件路径](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/ios真机调试包路径及配置文件路径.md)
- 11、[Cocoa框架Foundation和UIKit的区别](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Cocoa框架Foundation和UIKit的区别/Cocoa框架Foundation和UIKit的区别.md)
- 12、[UIView和CALayer的区别](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIView和CALayer的区别？.md)
- 13、[frame和bounds的区别](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/frame和bounds的区别/frame和bounds的区别.md)
- 14、[浅谈性能优化](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/简单性能优化/性能优化.md)
- 15、[UITableView架构总结](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/对UITableView进行性能调优/UITableView架构总结.md)
- 16、[加载大图的优化算法](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/加载大图的优化算法/加载大图的优化算法.md)
- 17、[App启动时间优化](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/APP启动优化/App启动时间优化.md)
- 18、[drawRect为什么导致CPU飙升](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/动画/drawRect/drawRect为什么导致CPU飙升.md)
- 19、[页面间跳转的性能优化](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/页面间跳转的性能优化/页面间跳转的性能优化.md)
- 20、[常见耗电量检测方案调研](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/常见耗电量检测方案调研.md)
- 21、[5种常见的消息传递机制以及他们之间区别](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/5种常见的消息传递机制以及他们之间区别/5种常见的消息传递机制以及他们之间区别.md)
- 22、[写一个好的单例](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/单例模式/单例模式.md)
- 23、[事件响应机制](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/事件响应机制/事件响应机制.md)




******************************************************************************************************************

### iOS高级









  
  ******************************************************************************************************************
  ## 架构
  - [1、浅谈MVC&变异MVC&MVP&MVVM](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/基础架构/1、MVC%26变异MVC%26MVP%26MVVM.md)
  - [2、UIViewController重构](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/UIViewController重构.md)
  
  
  ******************************************************************************************************************
  ## 网络
  
  - [HTTP详解](https://github.com/SunshineBrother/JHBlog/blob/master/网络/HTTP.md)
  - [深度优化iOS网络模块](https://github.com/SunshineBrother/JHBlog/blob/master/网络/深度优化iOS网络模块.md)
  
  
  
  ## 设计模式研究
  
常见的设计模式有23种，根据目的，我们可以把模型分为三类：创建型，结构型，行为型

- 1、创建型设计模式：创建型模式与对象的创建有关
- 2、结构型设计模式：结构型模式处理类和对象的组合
- 3、行为型设计模式：行为型设计模式对类或对象怎样交互和怎么分配职责进行描述
 


  - [1、UML使用简明教程](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/1、StarUML使用简明教程.md)
  - [2、对象设计的六大原则SOLID](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/2、面向对象设计的六大设计原则.md)
  - [3、设计模式总结](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/3、设计模式总结.md)
  
   **创建型**
   - 1、[Abstract Factory 抽象工厂模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/工厂模式/工厂模式.md)
   - 2、[Factory Method 工厂方法模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/工厂模式/工厂模式.md)
   - 3、[Builder 创建者模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/建造者模式/建造者模式.md)
   - 4、[Prototype 原型模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/原型模式/原型模式.md)
   - 5、[Singleton 单例模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/单例模式/单例模式.md)
   
   **结构型**
   - 6、[Adapter 适配器模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/适配器模式/适配器模式.md)
   - 7、[Bridge 桥接模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/桥接模式/桥接模式.md)
   - 8、[Composite 组合模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/组合模式/组合模式.md)
   - 9、[Decorator 装饰者模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/装饰者模式/装饰者模式.md)
   - 10、[Facade 外观模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/外观模式/外观模式.md)
   - 11、[Flyweight 享元模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/享元模式/享元模式.md)
   - 12、[Proxy 代理模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/代理模式/代理模式.md)
   
   **行为型**
   
   - 13、[Chain of responsibility 责任链模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/责任链模式/责任链模式.md)
   - 14、[Command 命令模式](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/命令模式/命令模式.md)
   - 15、[Interpreter 解释器模式]()
   - 16、[Iterator 迭代器模式]()
   - 17、[Mediator 中介模式]()
   - 18、[Memento 备忘录模式]()
   - 19、[Observer 观察者模式]()
   - 20、[State 状态模式]()
   - 21、[Strategy 策略模式]()
   - 22、[Template Method 模板方法模式]()
   - 23、[Visitor 访问者模式]()
  
  
 
  
  
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
  



*********************************************************
 
## 工具
这里记载了一些常用的工具，有许多都是转载的别人的博客，里面我有写转载地址，如果有作者感觉不适，请联系我，我会及时停止转载的


- 1、[如何优雅地使用Sublime Text](https://github.com/SunshineBrother/JHBlog/blob/master/工具/如何优雅地使用Sublime%20Text.md)
- 2、[官方 Swift 风格指南](https://github.com/SunshineBrother/JHBlog/blob/master/工具/官方%20Swift%20风格指南.md)
- 3、[iOS 程序员效率提升利器之 AppleScript](http://mrpeak.cn/blog/ios-applescript/)
- 4、[NPM 使用介绍](http://www.runoob.com/nodejs/nodejs-npm.html)
 - 5、[免费API](https://www.apishop.net/#/)
- 6、[APP Store官方网站](https://help.apple.com/app-store-connect/#/dev4df155cc4)
- 7、[如何在mac上创建txt文档](https://github.com/SunshineBrother/JHBlog/blob/master/工具/如何在mac上创建txt文档/如何在mac上创建txt文档.md)

*********************************************************
## 网站
- 1、[ 牛客网 — 面经和刷面试题](http://link.zhihu.com/?target=https%3A//www.nowcoder.com/)
- 2、[程序员客栈:程序员自由工作平台](https://www.proginn.com)




*********************************************************
## 图片

![iOS技术栈](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS技术栈.png)

![iOS知识体系](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/ios知识体系.png)







