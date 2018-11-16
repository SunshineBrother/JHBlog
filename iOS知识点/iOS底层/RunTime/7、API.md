## API

介绍之前先来看看`RunTime`都有哪些`API`吧

### 类方法

- 1、`Class objc_allocateClassPair(Class superclass, const char *name, size_t extraBytes)` 动态创建一个类（参数：父类，类名，额外的内存空间）
- 2、`void objc_registerClassPair(Class cls)` 注册一个类（要在类注册之前添加成员变量）
- 3、`void objc_disposeClassPair(Class cls)` 销毁一个类
- 4、`Class object_getClass(id obj)` 获取isa指向的Class
- 5、`Class object_setClass(id obj, Class cls)` 设置isa指向的Class
- 6、`BOOL object_isClass(id obj)` 判断一个OC对象是否为Class
- 7、`BOOL class_isMetaClass(Class cls)` 判断一个Class是否为元类
- 8、`Class class_getSuperclass(Class cls)`获取父类



我在[方法缓存](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/2、方法缓存.md)讲过，在创建一个实例对象以后，里面的成员变量就固定了，不能在修改了。因此我们在用`objc_registerClassPair`注册类的时候，我们必须把成员变量写在注册之前。
简单使用，因为这里面的都是runtime底层方法写的，所有点语法和set方法都不可以使用，如果想要遍历里面的属性和方法还是需要使用`runtime`提供的方法

**创建类**

```
// 创建类
Class newClass = objc_allocateClassPair([NSObject class], "MJDog", 0);
class_addIvar(newClass, "_age", 4, 1, @encode(int));
class_addIvar(newClass, "_weight", 4, 1, @encode(int));
//注册类
objc_registerClassPair(newClass);

// 成员变量的数量
unsigned int count;
Ivar *ivars = class_copyIvarList(newClass, &count);
for (int i = 0; i < count; i++) {
// 取出i位置的成员变量
Ivar ivar = ivars[i];
NSLog(@"%s %s", ivar_getName(ivar), ivar_getTypeEncoding(ivar));
}
free(ivars);

// 在不需要这个类时释放
  objc_disposeClassPair(newClass);
```

**设置isa指向的Class**

```
Person *p = [[Person alloc]init];
object_setClass(p, [Cat class]);
NSLog(@"%@",p);
```

![RunTime](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/RunTime.png)


### 成员变量 

- 1、`Ivar class_getInstanceVariable(Class cls, const char *name)` 获取一个实例变量信息
- 2、`Ivar *class_copyIvarList(Class cls, unsigned int *outCount)` 拷贝实例变量列表（最后需要调用free释放）
- 3、`void object_setIvar(id obj, Ivar ivar, id value)` 设置成员变量的值
- 4、`id object_getIvar(id obj, Ivar ivar)` 获取成员变量的值
- 5、`BOOL class_addIvar(Class cls, const char * name, size_t size, uint8_t alignment, const char * types)` 动态添加成员变量（已经注册的类是不能动态添加成员变量的）
- 6、`const char *ivar_getName(Ivar v), const char *ivar_getTypeEncoding(Ivar v)`获取成员变量的相关信息
 

最常用的方法就是获取类的成员变量

```
unsigned int count;
Ivar *ivars = class_copyIvarList([Person class], &count);
for (int i = 0; i < count; i++) {
// 取出i位置的成员变量
Ivar ivar = ivars[i];
NSLog(@"%s %s", ivar_getName(ivar), ivar_getTypeEncoding(ivar));
}
free(ivars);

```

常用的方案
- 1、JSON转Model
- 2、常看写控件都有哪些元素，然后进行修改


![RunTime1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/RunTime1.png)



 ### 属性
 - 1、`objc_property_t class_getProperty(Class cls, const char *name)` 获取一个属性

- 2、`objc_property_t *class_copyPropertyList(Class cls, unsigned int *outCount)`拷贝属性列表（最后需要调用free释放）

- 3、`BOOL class_addProperty(Class cls, const char *name, const objc_property_attribute_t *attributes,
unsigned int attributeCount)` 动态添加属性

- 4、`void class_replaceProperty(Class cls, const char *name, const objc_property_attribute_t *attributes,
unsigned int attributeCount)` 动态替换属性
- 5、`const char *property_getName(objc_property_t property)` 获取属性的一些信息
- 6、`const char *property_getAttributes(objc_property_t property)` 获取属性的一些信息
 
  ### 方法
  
- 1、获得一个实例方法、类方法
        - `Method class_getInstanceMethod(Class cls, SEL name)`
        - `Method class_getClassMethod(Class cls, SEL name)`
- 2、方法实现相关操作
        - `IMP class_getMethodImplementation(Class cls, SEL name)`
        - `IMP method_setImplementation(Method m, IMP imp)`
        - `void method_exchangeImplementations(Method m1, Method m2)`
- 3、拷贝方法列表（最后需要调用free释放）
    - `Method *class_copyMethodList(Class cls, unsigned int *outCount)`
- 4、动态添加方法
    - `BOOL class_addMethod(Class cls, SEL name, IMP imp, const char *types)`
- 5、动态替换方法
    - `IMP class_replaceMethod(Class cls, SEL name, IMP imp, const char *types)`
- 6、选择器相关
    - `const char *sel_getName(SEL sel)`
     - `SEL sel_registerName(const char *str)`
- 7、用block作为方法实现
    - `IMP imp_implementationWithBlock(id block)`
    - `id imp_getBlock(IMP anImp)`
    - `BOOL imp_removeBlock(IMP anImp)`


最常见的就是动态方法交换
```
Method runMethod = class_getInstanceMethod([Person class], @selector(run));
Method testMethod = class_getInstanceMethod([Person class], @selector(test));
method_exchangeImplementations(runMethod, testMethod)
```
还有一个方法替换
```
MJPerson *person = [[Person alloc] init];

//        class_replaceMethod([Person class], @selector(run), (IMP)myrun, "v");


class_replaceMethod([Person class], @selector(run), imp_implementationWithBlock(^{
NSLog(@"123123");
}), "v");

[person run];
```















