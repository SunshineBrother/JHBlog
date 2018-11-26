## Copy&Retain&Strong原理 

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


### 手动实现一个Copy

























