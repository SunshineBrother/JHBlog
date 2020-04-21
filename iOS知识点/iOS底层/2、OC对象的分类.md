 ## OC对象的分类
 
 OC对象主要可以分为3种
 - 1、instance对象（实例对象）：instance实例对象就是通过alloc出来的对象，每次调用alloc都会产生新的instance对象
 - 2、class对象（类对象）：每个类的内存中有且只有一个类对象
 - 3、meta-class对象（元类对象）：每个类的内存中有且只有一个元类对象



实例对象的存储信息
- isa指针
- 其他成员变量

类对象的存储信息
- isa指针
- superClass指针
- 类的属性信息（@property），类的对象方法信息（method），类的协议信息（protocol），类的成员变量信息（ivar）

元类的存储信息
- isa指针
- superClass指针
- 类的属性信息（@property），类的对象方法信息（method），类的协议信息（protocol），类的成员变量信息（ivar）

`元类和类的存储结构是一样的，但是用途不一样`

 ![OC对象的分类1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/OC对象的分类1.png)
- instance的isa指向class，当调用`对象方法`时，通过instance的isa找到class，最后找到对象方法的实现进行调用
- class的isa指向meta-class，当调用`类方法`时，通过class的isa找到meta-class，最后找到`类方法`

### 总览图
 ![OC对象的分类2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/OC对象的分类2.png)

- 1、instance的`isa`指向class
- 2、class的`isa`指向meta-class
- 3、meta-class的`isa`指向基类的meta-class
- 4、class的`superclass`指向`父类的class`，如果没有父类，superclass指向nil
- 5、meta-class的`superclass`指向父类的meta-class，基类的meta-class的superclass指向基类的class
- 6、instance的调用轨迹：isa找class，方法不存在，就通过superclass找父类
- 7、class调用类方法的轨迹：isa找到meta-class，方法不存在，就通过superclass找父类







