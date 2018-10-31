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



我在[方法缓存](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/2、方法缓存.md)讲过，在创建一个实例对象以后，里面的成员变量就固定了，不能在修改了。因此我们在用`objc_registerClassPair`注册类的时候，我们必须把成员变量写在注册之前。
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

![RunTime](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/RunTime/RunTime.png)










 
 
 
 
 
 
 
 
 
 
 
 
