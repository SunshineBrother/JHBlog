## Cocoa框架Foundation和UIKit的区别

### Cocoa


Cocoa不是一种编程语言（它可以运行多种编程语言），它也不是一个开发工具（通过命令行我们仍然可以开发Cocoa程序），它是创建Mac OS X和IOS程序的原生面向对象API，为这两者应用提供了编程环境。 
我们通常称为“Cocoa框架”，事实上Cocoa本身是一个框架的集合，它包含了众多子框架，其中最重要的要数“Foundation”和“UIKit”。前者是框架的基础，和界面无关，其中包含了大量常用的API；后者是基础的UI类库，以后我们在IOS开发中会经常用到。这两个框架在系统中的位置如下图


### Foundation框架简介


Foundation框架是包含常用一些结构体、枚举、类的一个框架，目的是使开发更快捷，

Foundation框架定义了一下功能：

基本的对象：NSNumber 、NSString 、NSDate 、

常用结构体和枚举：

基本集合：NSArray 、NSDictionary 、NSSet

内存管理：

操作系统服务：文件操作、URL、进程

归档和解档：

**Foundation框架的特点：**

- 1.都是以NS为前缀。
- 2.类都是继承自超类Object
































