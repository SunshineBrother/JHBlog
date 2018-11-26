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







































