## UML使用简明教程

UML（Unified Modeling Language，统一建模语言）是一个支持模型化和软件系统开发的图形化语言，为软件开发的所有阶段提供模型化和可视化支持，包括由需求分析到规格，到构造和配置。我们今天就来学习一下`UML`建模。

### StarUML

开始之前我们肯定需要先下载`StarUML`工具，可以下载破解版。我们打开下载好的`StarUML`，我们先来介绍一下怎么使用`StarUML`


安装之后的主界面简介如图所示： 

![UML](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/UML.jpg)

 


**1、选择模块**

在右边的`Model Explorer`框中选定`Untitled`模块。通过`Model`主菜单，或右击选定的模型，可以`Add/Design Model`

![UML2](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/UML2.png)

我们点击`model`可以设置这个模块的名称

![UML3](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/UML3.png)



**2、toolbox**

在StarUML中默认打开的“toolbox”工具中就是类相关的一下基础功能组件，以及组件的功能简介基础组件中有类实例，以及描述类的各个功能组件。如图所示。

![UML1](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/UML1.png)


### 类与类之间的关系



类图: 类图是面向对象系统建模中最常用和最重要的图，是定义其它图的基础。类图主要是用来显示系统中的类、接口以及它们之间的静态结构和关系的一种静态模型。 
类图的3个基本组件：类名、属性、方法。 
类的几个主要关系：实现，关联，泛化，聚合，组合，依赖 



#### 1、泛化关系

泛化（generalization）：说白了就是继承关系

例子：子类（men）继承父类


![泛化](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/泛化.png)

**`StarUML`使用步骤1：**

- 1、创建一个文件夹：在模型视图区域右键 --> add --> Package 创建文件夹
- 2、在文件夹下面添加类：右键 --> add --> class 添加类
- 3、添加属性：右键 --> add --> attribute 添加属性
- 4、把class拉到空白版上面，然后  右下方 --> Editors --> name（类名） --> stereotype（解释）
- 5、拉线：在左侧toolBox找到`generalization`，点击，上面会出现一个小锁（🔐）,这时候就可以拉线了

**`StarUML`使用步骤2：**

双击`Class类`会出现操作按钮

![泛化1](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/泛化1.png)

功能介绍： 
- 1、 用来标识Class的可见性（默认为public） 
- 2、用来添加note的，比如：类的说明 
- 3、增加类的属性 
- 4、增加类的操作方法。 
- 5、增加Reception 
- 6、增加子类 
- 7、 增加父类 
- 8、 添加已有的接口 
- 9、 添加需要的接口 
- 10、 添加关联 
- 11、 添加聚合 
- 12、 添加组合 
- 13、 添加端口 
- 14、 添加部件
 


#### 2、实现关系

实现关系（realization）：在Java中类似于接口，在iOS中类似于协议

例子：AppDelete实现applicationDidFinishLaunching()协议

![实现关系](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/实现关系.png)

在模型视图区域右键 --》 add --》 insterface（添加协议） --》 add --》operation（添加方法）


#### 3、依赖关系

依赖关系（dependency）:已知A类和B类，在A类中引用了B类，这种关系是`偶然性、临时性`，同时B类中发生了变化，影响到A类，这种关系就称之为依赖关系。


例子：我到超市买东西，我买了东西，超市收入增加，超市收入的增加跟我买东西有一定的依赖关系


![依赖关系](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/依赖关系.png)


#### 4、关联关系

关联关系可以分为两大类
- 1、单向关联（Directed Association）
- 2、双向关联（Association）

关联关系是一种比较强的依赖

例如：人喝水，这是单向关联
用户和订单（用户保存订单号，订单对应用户） ，这是双向关联

![关联关系](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/关联关系.png)

#### 5、聚合关系

聚合关系（Aggregration）：聚合关系是关联关系的特例，强调整体和部分，整体和部分可以分离，各自有各自的生命周期，互不干扰，部分强调共享

例如：电脑和电池、手机和电池

![聚合关系](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/聚合关系.png)

#### 6、组合关系
组合关系（Composition）：强调整体和部分，整体和部分不可以分离，共享生命周期，整体生命周期结束意味着部分生命周期结束    

例如：公司和部门

![组合关系](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/组合关系.png)



### UML建模模型图

常见的模型图有
- 1、用例图（Use Case Diagram）
- 2、类图(Class Diagram)
- 3、顺序图（时序图）(Sequence Diagram)
- 4、协作图(Collaboration Diagram)
- 5、状态图(State Chart Diagram)
- 6、活动图(Activity Diagram)
- 7、构件图(Component Diagram)
- 8、部署图(Deployment Diagram)



#### 1、用例图（Use Case Diagram）

用例图是从用户角度描述系统功能， 是用户所能观察到的系统功能的模型图，用例是系统中的一个功能单元；

用例图列出系统中的用例和系统外的参与者，并显示哪个参与者参与了哪个用例的执行
(或称为发起了哪个用例)。

用例图多用于静态建模阶段(主要是业务建模和需求建模)。

主要有两个概念

- 1、参与者（Actor）
    - 1、参与者是角色(role)而不是具体的人，它代表了参与者在与系统打交道的过程中所扮演的角色。所以在系统的实际运作中，一个实际用户可能对应系统的多个参与者。不同的用户也可以只对应于一个参与者，从而代表同一参与者的不同实例。
    - 2、参与者作为外部用户(而不是内部)与系统发生交互作用，是它的主要特征

- 2、用例(Use Case)
    - 系统外部可见的一个系统功能单元。系统的功能由系统单元所提供，并通过一系列系统单元与一个或多个参与者之间交换的消息所表达 。创建新用例，确认候选用例和划分用例范围的优秀法则----“WAVE”测试(见附录) 


![用例图](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/用例图.png)


**`StarUML`使用步骤**

- 1、在右侧右键 --> add Diagram --> Use Case Diagram(添加示例图)
- 2、在左下方的Toolbox工具栏里面我们可以找到我们需要的各种关系箭头


![用例图1](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/用例图1.png)





#### 2、类图(Class Diagram)

类图以反映类的结构(属性、操作)以及类之间的关系为主要目的，描述了软件系统的结构，是一种静态建模方法

类图中的“类”与面向对象语言中的“类”的概念是对应的，是对现实世界中的事物的抽象
从上到下分为三部分，分别是类名、属性和操作。类名是必须有的

注意：属性和方法修饰符
`+`表示public修饰符
`-`表示private修饰符
`#`表示protected修饰符


**`StarUML`使用步骤**
- 1、在右侧右键 --> add Diagram --> Class Diagram(添加类图)


![类图](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/类图.png)




#### 3、顺序图（时序图）(Sequence Diagram)

顺序图用来表示用例中的行为顺序。当执行一个用例行为时，顺序图中的每条消息对应了一个类操作或状态机中引起转换的事件。
顺序图展示对象之间的交互，这些交互是指在场景或用例的事件流中发生的。 顺序图属于动态建模。 
顺序图的重点在消息序列上，也就是说，描述消息是如何在对象间发送和接收的。表示了对象之间传送消息的时间顺序。
浏览顺序图的方法是：从上到下查看对象间交换的消息。

时序图主要包含
- 1、参与者：与系统、子系统或类发生交互作用的外部用户(参见用例图定义)。
- 2、对象：顺序图的横轴上是与序列有关的对象。对象的表示方法是：矩形框中写有对象或类名，且名字下面有下划线。
- 3、生命线：坐标轴纵向的虚线表示对象在序列中的执行情况(即发送和接收的消息，对象的活动)这条虚线称为对象的“生命线”。
- 4、消息符号：消息用从一个对象的生命线到另一个对象生命线的箭头表示。箭头以时间顺序在图中从上到下排列。
    - 发送消息，有同步消息，异步消息，重复消息，自己给自己发送消息等等类型


简单发送消息
![时序图1](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/时序图1.png)



下面这个是微信支付的时序图

![时序图](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/时序图.png)


 
 
