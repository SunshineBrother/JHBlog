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


















 
 
 
 
 
 
 
 
 
 
 
 
