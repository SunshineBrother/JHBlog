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
- [2、OC对象的分类](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/5、OC对象的分类.md)
- [3、KVO实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/3、KVO.md)
- [4、KVC实现原理](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/4、KVC.md)



## 工具
这里记载了一些常用的工具，有许多都是转载的别人的博客，里面我有写转载地址，如果有作者感觉不适，请联系我，我会及时停止转载的
[如何优雅地使用Sublime Text](https://github.com/SunshineBrother/JHBlog/blob/master/工具/如何优雅地使用Sublime%20Text.md)








