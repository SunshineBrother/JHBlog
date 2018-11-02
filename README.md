# JHBlog
这里以后就是自己的博客地址啦，欢迎点赞

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

### iOS底层
- [1、一个NSObject对象占用多少内存](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/1、一个NSObject对象占用多少内存.md)
- [2、OC对象的分类](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/2、OC对象的分类.md)
- [3、KVO实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/3、KVO.md)
- [4、KVC实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/4、KVC.md)
- [5、分类](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/5、分类.md)
- [7、Block底层解密](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/7、Block底层解密.md)
 - [8、RunLoop](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/8、RunLoop.md)
 - [9、RunTime](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/1、isa.md)
    - [9.1、isa解析](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/1、isa.md)
    - [9.2、方法缓存](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/2、方法缓存.md)
    - [9.3、objc_msgSend执行流程](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/3、objc_msgSend执行流程.md)
    - [9.4、@dynamic关键字](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/4、@dynamic关键字.md)
    - [9.5、Class和SuperClass区别](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/5、Class%26SuperClass.md)
    - [9.6、isKindOfClass和isMemberOfClass区别 ](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/6、isMemberOfClass%26.isKindOfClassmd.md)
    - [9.7、RunTime的相关API](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/7、API.md)
    
    
    


### iOS大杂烩

- 1、[LLDB使用](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/LLDB/LLDB.md)
- 2、[基本数据类型](https://github.com/SunshineBrother/JHBlog/blob/master/iOS%E7%9F%A5%E8%AF%86%E7%82%B9/%E6%89%93%E5%8D%B0%E5%90%84%E7%A7%8D%E6%95%B0%E6%8D%AE%E7%B1%BB%E5%9E%8B.md)
- 3、[App信息监控](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/App需要监控信息.md)
- 4、[Crash产生原因](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/Crash收集/Crash产生原因.md)
- 5、[Crash日志收集](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/Crash收集/Crash日志收集.md)
- 6、[Crash日志分析](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/Crash收集/Crash日志分析.md)
- 7、[armv7,armv7s,arm64,i386,x86_64 简单了解](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/armv7%2Carmv7s%2Carm64%2Ci386%2Cx86_64.md)

  

*********************************************************
## 第三方

- 1、[启动页](https://github.com/CoderZhuXH/XHLaunchAd )
-  2、[国际化](https://github.com/igorkulman/iOSLocalizationEditor)
通常 iPhone 上的一些应用需要支持多国语言，这要确保所有内容都已翻译，任何语言都不能丢失任何字符串，这是一件比较痛苦的事情。而 iOSLocalizationEditor 是一款在 macOS 上帮助用户编辑和管理 app localizations 的图形化工具，它会显示每种语言的所有本地化版本，并能方便快捷的找出你缺失的 key 。如果想要试试看的朋友，也可以参考下这篇[文章](https://blog.kulman.sk/checking-for-missing-translations-in-ios/)

 


*********************************************************
## 实用文章
**WebView**
- 1、[iOS WebView生成长截图的第三种解决方案](https://juejin.im/post/5b9d145ae51d450e7579d1e5)
- 2、[WKWebView使用指南](https://www.jianshu.com/p/97faf098e673)

**国家化**

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
 
 **导航栏**
 - 1、[iOS系统中导航栏的转场解决方案与最佳实践](https://juejin.im/post/5bd2bf936fb9a05cef177644)
 
*********************************************************
 
## 工具
这里记载了一些常用的工具，有许多都是转载的别人的博客，里面我有写转载地址，如果有作者感觉不适，请联系我，我会及时停止转载的


- 1、[如何优雅地使用Sublime Text](https://github.com/SunshineBrother/JHBlog/blob/master/工具/如何优雅地使用Sublime%20Text.md)

- 2、[官方 Swift 风格指南](https://github.com/SunshineBrother/JHBlog/blob/master/工具/官方%20Swift%20风格指南.md)

- 3、[iOS 程序员效率提升利器之 AppleScript](http://mrpeak.cn/blog/ios-applescript/)




