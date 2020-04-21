## Swift5.0的Runtime机制浅析


Objective-C语言是一门以C语言为基础的面向对象编程语言，`其提供的运行时(Runtime)机制使得它也可以被认为是一种动态语言`。运行时的特征之一就是对象方法的调用是在程序运行时才被确定和执行的。系统提供的开放接口使得我们可以在程序运行的时候执行方法替换以便实现一些诸如系统监控、对象行为改变、Hook等等的操作处理。然而这种开放性也存在着安全的隐患，我们可以借助Runtime在AOP层面上做一些额外的操作，而这些额外的操作因为无法进行管控， 所以有可能会输出未知的结果。

 

可能是苹果意识到了这个问题，所以在推出的Swift语言中Runtime的能力得到了限制，甚至可以说是取消了这个能力，这就使得`Swift成为了一门静态语言`。Swift语言中对象的方法调用机制和OC语言完全不同，`Swift语言的对象方法调用基本上是在编译链接时刻就被确定的，可以看做是一种硬编码形式的调用实现。`

Swfit中的对象方法调用机制加快了程序的运行速度，同时减少了程序包体积的大小。但是从另外一个层面来看当编译链接优化功能开启时反而又会出现包体积增大的情况。Swift在编译链接期间采用的是空间换时间的优化策略，是以提高运行速度为主要优化考虑点。具体这些我会在后面详细谈到。

通过程序运行时汇编代码分析Swift中的对象方法调用，发现其在Debug模式下和Release模式下的实现差异巨大。其原因是在Release模式下还同时会把编译链接优化选项打开。因此更加确切的说是在编译链接优化选项开启与否的情况下二者的实现差异巨大。

在这之前先介绍一下OC和Swift两种语言对象方法调用的一般实现。

 


## OC类的对象方法调用


对于OC语言来说对象方法调用的实现机制有很多文章都进行了深入的介绍。所有OC类中定义的方法函数的实现都隐藏了两个参数：`一个是对象本身，一个是对象方法的名称`。每次对象方法调用都会至少传递对象和对象方法名称作为开始的两个参数，方法的调用过程都会通过一个被称为消息发送的C函数objc_msgSend来完成。objc_msgSend函数是OC对象方法调用的总引擎，这个函数内部会根据第一个参数中对象所保存的类结构信息以及第二个参数中的方法名来找到最终要调用的方法函数的地址并执行函数调用。这也是OC语言Runtime的实现机制，同时也是OC语言对多态的支持实现。整个流程就如下表述
 
![OC方法调用流程](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS进阶/Swift5.0的Runtime机制浅析/OC方法调用流程.png)



### Swift类的对象创建和销毁


在Swift中可以定义两种类：
- 1、是从NSObject或者派生类派生的类
- 2、从系统Swift基类SwiftObject派生的类

对于后者来说如果在定义类时没有指定基类则默认会从基类`SwiftObject`派生。SwiftObject是一个隐藏的基类，不会在源代码中体现。
`
Swift类对象的内存布局和OC类对象的内存布局相似。二者对象的最开始部分都有一个`isa`成员变量指向类的描述信息。Swift类的描述信息结构继承自OC类的描述信息，但是并没有完全使用里面定义的属性，对于方法的调用则主要是使用其中扩展了一个所谓的虚函数表的区域`，关于这部分会在后续中详细介绍。

Swift类的对象实例都是在·堆内存中创建·，这和OC语言的对象实例创建方式相似。系统会为类提供一个默认的init构造函数，如果想自定义构造函数则需要重写和重载init函数。

一个Swift类的对象实例的构建分为两部分：
- 1、首先是进行堆内存的分配
- 2、然后才是调用init构造函数。

在源代码编写中不会像OC语言那样明确的分为alloc和init两个分离的调用步骤，而是直接采用:类名(初始化参数)这种方式来完成对象实例的创建。在编译时系统会为每个类的初始化方法生成一个:`模块名.类名.__allocating_init(类名,初始化参数)的函数`，这个函数的伪代码实现如下

```
/假设定义了一个CA类。
class CA {
   init(_ a:Int){}
}
```

```
//编译生成的对象内存分配创建和初始化函数代码
CA * XXX.CA.__allocating_init(swift_class  classCA,  int a)
{
    CA *obj = swift_allocObject(classCA);  //分配内存。
    obj->init(a);  //调用初始化函数。
}

//编译时还会生成对象的析构和内存销毁函数代码
XXX.CA.__deallocating_deinit(CA *obj)
{
   obj->deinit()  //调用析构函数
   swift_deallocClassInstance(obj);  //销毁对象分配的内存。
}
```

其中的swift_class 就是从objc_class派生出来，用于描述类信息的结构体。


Swift对象的生命周期也和OC对象的生命周期一样是通过引用计数来进行控制的。当对象初次创建时引用计数被设置为1，每次进行对象赋值操作都会调用`swift_retain`函数来增加引用计数，而每次对象不再被访问时都会调用`swift_release`函数来减少引用计数。当引用计数变为0后就会调用编译时为每个类生成的析构和销毁函数：`模块名.类名.__deallocating_deinit(对象)`。这个函数的定义实现在前面有说明。

这就是Swift对象的创建和销毁以及生命周期的管理过程，这些C函数都是在编译链接时插入到代码中并形成机器代码的，整个过程对源代码透明。下面的例子展示了对象创建和销毁的过程。

 ```
 ////////Swift源代码

let obj1:CA = CA(20);
let obj2 = obj1
 ```

```
///////C伪代码

CA *obj1 = XXX.CA. __allocating_init(classCA, 20);
CA *obj2 = obj1;
swift_retain(obj1);
swift_release(obj1);
swift_release(obj2);
```



### Swift类的对象方法调用

Swift语言中对象的方法调用的实现机制和C++语言中对虚函数调用的机制是非常相似的。(需要注意的是我这里所说的调用实现只是在编译链接优化选项开关在关闭的时候是这样的,在优化开关打开时这个结论并不正确)。
 
Swift语言中类定义的方法可以分为三种：
- 1、OC类的派生类并且重写了基类的方法
- 2、extension中定义的方法
- 3、类中定义的常规方法。

针对这三种方法定义和实现，系统采用的处理和调用机制是完全不一样的


#### OC类的派生类并且重写了基类的方法


如果在Swift中的使用了OC类，比如还在使用的UIViewController、UIView等等。并且还重写了基类的方法，比如一定会重写UIViewController的viewDidLoad方法。`对于这些类的重写的方法定义信息还是会保存在类的Class结构体中，而在调用上还是采用OC语言的Runtime机制来实现，即通过objc_msgSend来调用。而如果在OC派生类中定义了一个新的方法的话则实现和调用机制就不会再采用OC的Runtime机制来完成了，比如说在UIView的派生类中定义了一个新方法foo，那么这个新方法的调用和实现将与OC的Runtime机制没有任何关系了！ `它的处理和实现机制会变成我下面要说到的第三种方式。下面的Swift源代码以及C伪代码实现说明了这个情况：

```
////////Swift源代码
//类定义
class MyUIView:UIView {
    open func foo(){}   //常规方法
    override func layoutSubviews() {}  //重写OC方法
}
func main(){
  let obj = MyUIView()
  obj.layoutSubviews()   //调用OC类重写的方法
  obj.foo()   //调用常规的方法。
}
```

```
////////C伪代码
//...........................................运行时定义部分
//OC类的方法结构体
struct method_t {
    SEL name;
    IMP imp;
};
//Swift类描述
struct swift_class {
    ...   //其他的属性，因为这里不关心就不列出了。
    struct method_t  methods[1];
    ...   //其他的属性，因为这里不关心就不列出了。
    //虚函数表刚好在结构体的第0x50的偏移位置。
    IMP vtable[1];
};
//...........................................源代码中类的定义和方法的定义和实现部分
//类定义
struct MyUIView {
      struct swift_class *isa;
}
//类的方法函数的实现
void layoutSubviews(id self, SEL _cmd){}
void foo(){}  //Swift类的常规方法中和源代码的参数保持一致。
//类的描述信息构建，这些都是在编译代码时就明确了并且保存在数据段中。
struct swift_class classMyUIView;
classMyUIView.methods[0] = {"layoutSubviews", &layoutSubviews};
classMyUIView.vtable[0] = {&foo};
//...........................................源代码中程序运行的部分
void main(){
  MyUIView *obj = MyUIView.__allocating_init(classMyUIView);
  obj->isa = &classMyUIView;
  //OC类重写的方法layoutSubviews调用还是用objc_msgSend来实现
  objc_msgSend(obj, @selector(layoutSubviews);
  //Swift方法调用时对象参数被放到x20寄存器中
  asm("mov x20, obj");
  //Swift的方法foo调用采用间接调用实现
  obj->isa->vtable[0]();
}
```



















































































 
