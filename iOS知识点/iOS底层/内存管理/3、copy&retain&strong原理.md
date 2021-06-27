 ## Copy&Strong原理 

**问题**
- 1、用@property声明的NSString（或NSArray，NSDictionary）经常使用copy关键字，为什么？如果改用strong关键字，可能造成什么问题？
- 2、怎么用 copy 关键字？
- 3、如何让自己的类用 copy 修饰符？如何重写带 copy 关键字的 setter？
- 4、对非集合类对象的copy操作
- 5、集合类对象的copy与mutableCopy
- 6、这个写法会出什么问题： `@property (copy) NSMutableArray *array;`

### Copy探究

在开始回答`copy`的各种问题之前，我们需要先了解我们为什么要使用`copy`。
- 1、拷贝的目的：产生一个副本对象，跟源对象互不影响
    - 修改了源对象，不会影响副本对象
    - 修改了副本对象，不会影响源对象
- 2、iOS提供了2个拷贝方法
    - 1、copy，不可变拷贝，产生不可变副本
    - 2、mutableCopy，可变拷贝，产生可变副本
- 3、深拷贝和浅拷贝
    - 1、深拷贝：内容拷贝，产生新的对象
    - 2、浅拷贝：指针拷贝，没有产生新的对象


**test1**

对不可变字符串进行`copy&mutableCopy`操作
```
void test1()
{
	NSString *str1 = [NSString stringWithFormat:@"test"];
	NSString *str2 = [str1 copy]; // 返回的是NSString
	NSMutableString *str3 = [str1 mutableCopy]; // 返回的是NSMutableString
	NSLog(@"%p %p %p", str1, str2, str3);
}
```
![copy1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/copy1.png)

我们根据打印的地址可以看出`不可变字符串在copy时是浅拷贝，只拷贝了指针没有拷贝对象；mutableCopy则是深拷贝，产生了新的对象`

**test2**

对可变字符串进行`copy&mutableCopy`操作
```
void test2()
{
	NSMutableString *str1 = [[NSMutableString alloc] initWithFormat:@"test"]; // 1
	NSString *str2 = [str1 copy]; // 深拷贝
	NSMutableString *str3 = [str1 mutableCopy]; // 深拷贝
	NSLog(@"%p %p %p", str1, str2, str3);
}
```

![copy2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/copy2.png)

我们根据打印的地址可以看出`对于可变字符串不论是copy还是mutableCopy都是深拷贝`

**test3**

对不可变数组进行`copy&mutableCopy`操作
```
void test3()
{
	NSArray *array1 = [[NSArray alloc] initWithObjects:@"a", @"b", nil];
	NSArray *array2 = [array1 copy]; // 浅拷贝
	NSMutableArray *array3 = [array1 mutableCopy]; // 深拷贝

	NSLog(@"%p %p %p", array1, array2, array3);
}
```

![copy3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/copy3.png)


我们根据打印的地址可以看出`不可变数组在copy时是浅拷贝，只拷贝了指针没有拷贝对象；mutableCopy则是深拷贝，产生了新的对象`

**test4**

对可变数组进行`copy&mutableCopy`操作
```
void test4()
{
	NSMutableArray *array1 = [[NSMutableArray alloc] initWithObjects:@"a", @"b", nil];
	NSArray *array2 = [array1 copy]; // 深拷贝
	NSMutableArray *array3 = [array1 mutableCopy]; // 深拷贝

	NSLog(@"%p %p %p", array1, array2, array3);
}
```
![copy4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/copy4.png)

我们根据打印的地址可以看出`对于可变数组不论是copy还是mutableCopy都是深拷贝`

**test5**

对不可变字典进行`copy&mutableCopy`操作
```
void test5()
{
	NSDictionary *dict1 = [[NSDictionary alloc] initWithObjectsAndKeys:@"jack", @"name", nil];
	NSDictionary *dict2 = [dict1 copy]; // 浅拷贝
	NSMutableDictionary *dict3 = [dict1 mutableCopy]; // 深拷贝

	NSLog(@"%p %p %p", dict1, dict2, dict3);
}
```

![copy5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/copy5.png)

我们根据打印的地址可以看出`不可变字典在copy时是浅拷贝，只拷贝了指针没有拷贝对象；mutableCopy则是深拷贝，产生了新的对象`


**test6**

对可变字典进行`copy&mutableCopy`
```
void test6()
{
	NSMutableDictionary *dict1 = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"jack", @"name", nil];
	NSDictionary *dict2 = [dict1 copy]; // 深拷贝
	NSMutableDictionary *dict3 = [dict1 mutableCopy]; // 深拷贝

	NSLog(@"%p %p %p", dict1, dict2, dict3);

}
```
![copy6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/copy6.png)


根据上面结果我们可以总结出

![copy7](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/copy7.png)


**让自己的类用 copy 修饰符**

我们`copy`属性一般只对`NSString NSArray NSDictionary NSSet`等这些可用，假如我们要对我们的类对象进行copy实现，我们应该怎么做呢

`若想令自己所写的对象具有拷贝功能，则需实现 NSCopying 协议。如果自定义的对象分为可变版本与不可变版本，那么就要同时实现 NSCopying 与 NSMutableCopying 协议。`

- 1、需声明该类遵从 NSCopying 协议
- 2、实现 NSCopying 协议`- (id)copyWithZone:(NSZone *)zone;`
- 3、在`- (id)copyWithZone:(NSZone *)zone;`方法中对类对象进行重新赋值


```
@interface Dog : NSObject<NSCopying>
@property (nonatomic,assign) int age;
@property (nonatomic,copy) NSString *name;
@end

- (id)copyWithZone:(NSZone *)zone{
	Dog *d = [[self class]allocWithZone:zone];
	d.age = _age;
	d.name = _name;
	return d;
}
```


**如何重写带 copy 关键字的 setter**

```
- (void)setName:(NSString *)name {
	if (_name != name) {
		//[_name release];//MRC
		_name = [name copy];
	}
}
```
 
### Strong

我们添加属性
```
@property (strong, nonatomic) NSString *strStrong;
@property (copy, nonatomic) NSString *strCopy;
```
**不可变字符串**
```
NSString *str = @"abc";
self.strCopy = str;
self.strStrong = str;

NSLog(@"\nstr     = %@   内存地址 = %p 指针地址 = %p \nstrong  = %@   内存地址 = %p 指针地址 = %p \ncopy    = %@   内存地址 = %p 指针地址 = %p",
str,str,&str,
self.strStrong,self.strStrong,&_strStrong,
self.strCopy,self.strCopy,&_strCopy);
```

我们打印内存地址和指针地址

![strong](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/strong.png)

我们修改`str`
```
NSString *str = @"abc";
self.strCopy = str;
self.strStrong = str;

NSLog(@"\nstr     = %@   内存地址 = %p 指针地址 = %p \nstrong  = %@   内存地址 = %p 指针地址 = %p \ncopy    = %@   内存地址 = %p 指针地址 = %p",
str,str,&str,
self.strStrong,self.strStrong,&_strStrong,
self.strCopy,self.strCopy,&_strCopy);



str = @"123";
NSLog(@"\nstr     = %@   内存地址 = %p 指针地址 = %p \nstrong  = %@   内存地址 = %p 指针地址 = %p \ncopy    = %@   内存地址 = %p 指针地址 = %p",
str,str,&str,
self.strStrong,self.strStrong,&_strStrong,
self.strCopy,self.strCopy,&_strCopy);
```

![strong1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/strong1.png)


`结论：源对象为不可变字符串而言，不论使用copy还是strong属性，所对应的值是不发生变化，strong和copy并没有开辟新的内存，即并不是深拷贝。此时，使用copy或是strong，并没有对数据产生影响`


**可变字符串**
```
NSMutableString *str = [[NSMutableString alloc] initWithString:@"abc"];
self.strCopy = str;
self.strStrong = str;

NSLog(@"\nstr     = %@   内存地址 = %p 指针地址 = %p \nstrong  = %@   内存地址 = %p 指针地址 = %p \ncopy    = %@   内存地址 = %p 指针地址 = %p",
str,str,&str,
self.strStrong,self.strStrong,&_strStrong,
self.strCopy,self.strCopy,&_strCopy);

[str appendString:@"123"];
NSLog(@"\nstr     = %@   内存地址 = %p 指针地址 = %p \nstrong  = %@   内存地址 = %p 指针地址 = %p \ncopy    = %@   内存地址 = %p 指针地址 = %p",
str,str,&str,
self.strStrong,self.strStrong,&_strStrong,
self.strCopy,self.strCopy,&_strCopy);
```

![strong2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/strong2.png)

`结论：数据源为可变字符串而言，使用copy申明属性，会开辟一块新的内存空间存放值，源数据不论怎么变化，都不会影响copy属性中的值，属于深拷贝；使用strong申明属性，不会开辟新的内存空间，只会引用到源数据内存地址，因此源数据改变，则strong属性也会改变，属于浅拷贝`



**在实际开发中，我们不希望源数据改变影响到属性中的值，故而使用copy来申明。**

为了理解这种做法，首先要知道，两种情况：

对非集合类对象的 copy 与 mutableCopy 操作；
对集合类对象的 copy 与 mutableCopy 操作。
1. 对非集合类对象的copy操作：
在非集合类对象中：对 immutable 对象进行 copy 操作，是指针复制，mutableCopy 操作时内容复制；对 mutable 对象进行 copy 和 mutableCopy 都是内容复制。用代码简单表示如下：

[immutableObject copy] // 浅复制
[immutableObject mutableCopy] //深复制
[mutableObject copy] //深复制
[mutableObject mutableCopy] //深复制
比如以下代码：

NSMutableString *string = [NSMutableString stringWithString:@"origin"];//copy
NSString *stringCopy = [string copy];
查看内存，会发现 string、stringCopy 内存地址都不一样，说明此时都是做内容拷贝、深拷贝。即使你进行如下操作：

[string appendString:@"origion!"]
stringCopy 的值也不会因此改变，但是如果不使用 copy，stringCopy 的值就会被改变。 集合类对象以此类推。 所以，

用 @property 声明 NSString、NSArray、NSDictionary 经常使用 copy 关键字，是因为他们有对应的可变类型：NSMutableString、NSMutableArray、NSMutableDictionary，他们之间可能进行赋值操作，为确保对象中的字符串值不会无意间变动，应该在设置新属性值时拷贝一份。

2、集合类对象的copy与mutableCopy
集合类对象是指 NSArray、NSDictionary、NSSet ... 之类的对象。下面先看集合类immutable对象使用 copy 和 mutableCopy 的一个例子：

NSArray *array = @[@[@"a", @"b"], @[@"c", @"d"]];
NSArray *copyArray = [array copy];
NSMutableArray *mCopyArray = [array mutableCopy];
查看内容，可以看到 copyArray 和 array 的地址是一样的，而 mCopyArray 和 array 的地址是不同的。说明 copy 操作进行了指针拷贝，mutableCopy 进行了内容拷贝。但需要强调的是：此处的内容拷贝，仅仅是拷贝 array 这个对象，array 集合内部的元素仍然是指针拷贝。这和上面的非集合 immutable 对象的拷贝还是挺相似的，那么mutable对象的拷贝会不会类似呢？我们继续往下，看 mutable 对象拷贝的例子：

NSMutableArray *array = [NSMutableArray arrayWithObjects:[NSMutableString stringWithString:@"a"],@"b",@"c",nil];
NSArray *copyArray = [array copy];
NSMutableArray *mCopyArray = [array mutableCopy];
查看内存，如我们所料，copyArray、mCopyArray和 array 的内存地址都不一样，说明 copyArray、mCopyArray 都对 array 进行了内容拷贝。同样，我们可以得出结论：

在集合类对象中，对 immutable 对象进行 copy，是指针复制， mutableCopy 是内容复制；对 mutable 对象进行 copy 和 mutableCopy 都是内容复制。但是：集合对象的内容复制仅限于对象本身，对象元素仍然是指针复制。用代码简单表示如下：

[immutableObject copy] // 浅复制
[immutableObject mutableCopy] //单层深复制
[mutableObject copy] //单层深复制
[mutableObject mutableCopy] //单层深复制
这个代码结论和非集合类的非常相似。









