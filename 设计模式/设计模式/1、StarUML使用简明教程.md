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


### UML关系

**介绍类与类之间的关系**

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
- 1. 用来标识Class的可见性（默认为public） 
- 2. 用来添加note的，比如：类的说明 
- 3. 增加类的属性 
- 4. 增加类的操作方法。 
- 5. 增加Reception 
- 6. 增加子类 
- 7. 增加父类 
- 8. 添加已有的接口 
- 9. 添加需要的接口 
- 10. 添加关联 
- 11. 添加聚合 
- 12. 添加组合 
- 13. 添加端口 
- 14. 添加部件
 


#### 2、实现关系

实现关系（realization）：在Java中类似于接口，在iOS中类似于协议

例子：AppDelete实现applicationDidFinishLaunching()协议

![实现关系](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/设计模式/image/实现关系.png)

在模型视图区域右键 --》 add --》 insterface（添加协议） --》 add --》operation（添加方法）












