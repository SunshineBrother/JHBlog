## @property 的本质是什么 

@property 的本质就是`ivar + getter + setter`


我们创建一个`person`类，里面创建一个属性
```
@property (nonatomic,copy) NSString *name;
```

**打印属性信息**

```
unsigned int count;
objc_property_t *propertyList = class_copyPropertyList([Person class], &count);
for (unsigned int i = 0; i< count; i++)
	{
	const char *name = property_getName(propertyList[i]);
	NSLog(@"__%@",[NSString stringWithUTF8String:name]);
	objc_property_t property = propertyList[i];
	const char *a = property_getAttributes(property);
	NSLog(@"属性信息__%@",[NSString stringWithUTF8String:a]);
}
```

![property](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/property.png)

属性信息中`NSString`我们是知道了，但是`T,C,N,V_name`都是什么意思呢。我们查看[官方介绍](https://link.jianshu.com/?t=https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtPropertyIntrospection.html)


![property1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/property1.png)

```
//T@"NSString",C,N,V_name
//T 类型
//C copy
//N nonatomic
//V 实例变量
```

**方法列表**
```
u_int methodCount;
NSMutableArray *methodList = [NSMutableArray array];
Method *methods = class_copyMethodList([Person class], &methodCount);
for (int i = 0; i < methodCount; i++)
{
	SEL name = method_getName(methods[i]);
	NSString *strName = [NSString stringWithCString:sel_getName(name) encoding:NSUTF8StringEncoding];
	[methodList addObject:strName];
}
free(methods);

NSLog(@"方法列表:%@",methodList);
```

![property2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/property2.png)


我们并没有写`name`&`setName:`方法，所以这个`get`和`set`方法应该就是runtime生成的。

### property的实现

property的实现主要是利用runtime的两个方法
```
class_addProperty(Class _Nullable cls, const char * _Nonnull name,
const objc_property_attribute_t * _Nullable attributes,
unsigned int attributeCount)

void
class_addMethods(Class _Nullable, struct objc_method_list * _Nonnull)
```

**1、class_addProperty 生成属性**

```
/** 
* Adds a property to a class.
* 
* @param cls 修改的类
* @param name 属性名字
* @param attributes 属性数组
* @param attributeCount 属性数组数量
* @return y 成功,n失败
*/
OBJC_EXPORT BOOL class_addProperty(Class cls, const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount)
 
```
生成属性
```
objc_property_attribute_t type = { "T", "@\"NSString\"" };
objc_property_attribute_t ownership = { "C", "" }; // C = copy
objc_property_attribute_t nonatomic = { "N", "" }; //nonatomic
objc_property_attribute_t backingivar  = { "V", "_name" };//V 实例变量
objc_property_attribute_t attrs[] = { type, ownership,nonatomic, backingivar };
class_addProperty([self class], "name", attrs, 4); 
```



**2、class_addMethod 生成方法**


```
NSString *nameGetter(id self, SEL _cmd) {
Ivar ivar = class_getInstanceVariable([self class], "_privateName");
return object_getIvar(self, ivar);
}
void nameSetter(id self, SEL _cmd, NSString *newName) {
Ivar ivar = class_getInstanceVariable([self class], "_privateName");
id oldName = object_getIvar(self, ivar);
if (oldName != newName) object_setIvar(self, ivar, [newName copy]);
}


//其中 “v@:” 表示返回值和参数

if(class_addMethod([self class],  NSSelectorFromString(@"name"), (IMP)nameGetter, "@@:"))
{
	NSLog(@"name get 方法添加成功");
}
else
{
	NSLog(@"name get 方法添加失败");
}

if(class_addMethod([self class], NSSelectorFromString(@"setName:"), (IMP)nameSetter, "v@:@"))
{
	NSLog(@"name set 方法添加成功");
}
else
{
	NSLog(@"name set 方法添加失败");
}

 
```



























