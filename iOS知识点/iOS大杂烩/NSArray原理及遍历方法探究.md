# NSArray原理及遍历方法探究


[转载：BoyangBlog](https://github.com/BiBoyang/BoyangBlog/blob/master/File/004.md)

前段日子我为了学习英语，阅读《Effective Objective-C 2.0》的原版的时候，我发现了之前没怎么注意到的一段话：

> In the case of NSArray, when an instance is allocated, it’s an instance of another class that’s allocated (during a call to alloc), known as a placeholder array. This placeholder array is then converted to an instance of another class, which is a concrete subclass of NSArray.      
在使用了NSArray的alloc方法来获取实例时，该方法首先会分类一个属于某类的实例，此实例充当“占位数组”。该数组稍后会转为另一个类的实例，而那个类则是NSArray的实体子类。

话不多说，代码写两行：
```C++
NSArray *placeholder = [NSArray alloc];
NSArray *arr1 = [[NSArray alloc] init];
NSArray *arr2 = [[NSArray alloc] initWithObjects:@0, nil];
NSArray *arr3 = [[NSArray alloc] initWithObjects:@0, @1, nil];
NSArray *arr4 = [[NSArray alloc] initWithObjects:@0, @1, @2, nil];
    
NSLog(@"placeholder: %s", object_getClassName(placeholder));
NSLog(@"arr1: %s", object_getClassName(arr1));
NSLog(@"arr2: %s", object_getClassName(arr2));
NSLog(@"arr3: %s", object_getClassName(arr3));
NSLog(@"arr4: %s", object_getClassName(arr4));
    
NSMutableArray *mPlaceholder = [NSMutableArray alloc];
NSMutableArray *mArr1 = [[NSMutableArray alloc] init];
NSMutableArray *mArr2 = [[NSMutableArray alloc] initWithObjects:@0, nil];
NSMutableArray *mArr3 = [[NSMutableArray alloc] initWithObjects:@0, @1, nil];
    
NSLog(@"mPlaceholder: %s", object_getClassName(mPlaceholder));    
NSLog(@"mArr1: %s", object_getClassName(mArr1));
NSLog(@"mArr2: %s", object_getClassName(mArr2));
NSLog(@"mArr3: %s", object_getClassName(mArr3));
```

打印出来的结果是这样的:

```C++
2018-02-25 09:09:15.628381+0800 NSArrayTest[44716:5228210] placeholder: __NSPlaceholderArray
2018-02-25 09:09:15.628749+0800 NSArrayTest[44716:5228210] arr1: __NSArray0
2018-02-25 09:09:15.629535+0800 NSArrayTest[44716:5228210] arr2: __NSSingleObjectArrayI
2018-02-25 09:09:15.630635+0800 NSArrayTest[44716:5228210] arr3: __NSArrayI
2018-02-25 09:09:15.630789+0800 NSArrayTest[44716:5228210] arr4: __NSArrayI
2018-02-25 09:09:15.630993+0800 NSArrayTest[44716:5228210] mPlaceholder: __NSPlaceholderArray
2018-02-25 09:09:15.631095+0800 NSArrayTest[44716:5228210] mArr1: __NSArrayM
2018-02-25 09:09:15.631954+0800 NSArrayTest[44716:5228210] mArr2: __NSArrayM
2018-02-25 09:09:15.632702+0800 NSArrayTest[44716:5228210] mArr3: __NSArrayM
```

清晰易懂，我们可以看到，不管创建的事可变还是不可变的数组，在alloc之后得到的类都是**__NSPlaceholderArray**。而当我们`init`一个不可变的空数组之后，得到的是**__NSArray0**；如果有且只有一个元素，那就是**__NSSingleObjectArrayI**；有多个元素的，叫做 **__NSArrayI**；`init`一个可变数组的话，就都是 **__NSArrayM**。


![](https://upload-images.jianshu.io/upload_images/1342490-270c017a4b4a3579.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
我们看到`__NSPlaceholderArray`的名字就知道它是用来占位的。
那它是个什么呢？
我们继续写几行代码：

```C++
NSArray *placeholder1 = [NSArray alloc];
NSArray *placeholder2 = [NSArray alloc];
NSLog(@"placeholder1: %p", placeholder1);
NSLog(@"placeholder2: %p", placeholder2);
```
打印出来的结果很有意思

```C++
2018-02-25 09:41:45.097431+0800 NSArrayTest[45228:5277101] placeholder1: 0x604000005d90
2018-02-25 09:41:45.097713+0800 NSArrayTest[45228:5277101] placeholder2: 0x604000005d90
```
这两个数组的内存地址是一样的，可以猜测，这里是生成了一个单例，在执行`init`之后就被新的实例给更换掉了。**该类内部只有一个isa指针**，除此之外没有别的东西。
由于苹果没有公开此处的源码，我查阅了别的类似的开源以及资料，得到如下的结论：

> 1. 当元素为空时，返回的是__NSArray0的单例；
> 2. 当元素仅有一个时，返回的是__NSSingleObjectArrayI的实例；
> 3. 当元素大于一个的时候，返回的是__NSArrayI的实例。
> 4. 网上的资料，大多未提及__NSSingleObjectArrayI，可能是后面新增的，理由大概还是为了效率，在此不深究。

为了区别可变和不可变的情况，在init的时候，会根据是NSArray还是NSMutableArray来创建`immutablePlaceholder`和`mutablePlaceholder`，它们都是`__NSPlaceholderArray`类型的。

#### 创建数组
在上面的多种创建数组的方法里，都是最后调用了initWithObjects:count:函数。
```C++
@interface NSArray<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (ObjectType)objectAtIndex:(NSUInteger)index;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end
```
这就是类族的优点，在创建某个类族的子类的时候，我们不需要实现所有的功能。在CoreFoundation的类蔟的抽象工厂基类（如NSArray、NSString、NSNumber等）中，`Primitive methods`指的就是这些核心的方法，也就是那些在创建子类时必须要重写的方法，通常在类的interface中声明，在文档中一般也会说明。其他可选实现的方法在Category中声明。同时还需要注意其整个继承树的祖先的Primitive methods也都需要实现。

#### CFArray和NSMutableArray

CFArray是CoreFoundation中的，和Foundation中的NSArray相对应，他们是**Toll-Free Bridged**的。通过阅读 [ibireme](https://blog.ibireme.com/2014/02/17/cfarray/)的这篇博客，我们可以知道，CFArray最开始是使用双端队列实现的，但是因为性能问题，后来发生了改变，因为没有开源代码，ibireme只能通过测试来猜测它可能换成[圆形缓冲区](https://en.wikipedia.org/wiki/Circular_buffer)来实现了。

任何典型的程序员都知道 C 数组的原理。可以归结为一段能被方便读写的连续内存空间。数组和指针并不相同 (详见 [Expert C Programming](https://link.jianshu.com?t=http%3A%2F%2Fwww.amazon.com%2FExpert-Programming-Peter-van-Linden%2Fdp%2F0131774298) 或 [这篇文章](https://link.jianshu.com?t=http%3A%2F%2Feli.thegreenplace.net%2F2009%2F10%2F21%2Fare-pointers-and-arrays-equivalent-in-c%2F))，不能说：一块被 **malloc** 过的内存空间等同于一个数组 (一种被滥用了的说法)。

使用一段线性内存空间的一个最明显的缺点是，在下标 0 处插入一个元素时，需要移动其它所有的元素，即 **memmove** 的原理：

![](https://upload-images.jianshu.io/upload_images/6260113-3a498cb87008f05c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

同样地，假如想要保持相同的内存指针作为首个元素的地址，移除第一个元素需要进行相同的动作：
[](https://link.jianshu.com/?t=http%3A%2F%2Fblog.joyingx.me%2Fimages%2F20150503%2F2.jpg)
![](http://upload-images.jianshu.io/upload_images/1342490-5f4bd5189d2515f9?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
当数组非常大时，这样很快会成为问题。显而易见，直接对指针存取，在数组的世界里必定不是最好的办法。C语言风格的数组通常很有用，但OC程序员每天的主要工作使得我们需要 NSMutableArray 这样一个可变的、可索引的容器。
这里，我们需要阅读[这篇博客](http://ciechanowski.me/blog/2014/03/05/exposing-nsmutablearray/)。在这里我们可以确定使用了环形缓冲区。
正如你会猜测的，**__NSArrayM** 用了[环形缓冲区 (circular buffer)](https://link.jianshu.com?t=http%3A%2F%2Fen.wikipedia.org%2Fwiki%2FCircular_buffer)。这个数据结构相当简单，只是比常规数组或缓冲区复杂点。环形缓冲区的内容能在到达任意一端时绕向另一端。

环形缓冲区有一些非常酷的属性。尤其是，除非缓冲区满了，否则在任意一端插入或删除均不会要求移动任何内存。我们来分析这个类如何充分利用环形缓冲区来使得自身比 C 数组强大得多。
我们在这里知道了几个有趣的东西：
 **在删除的时候不会清除指针。**
 最有意思的一点，如果我们在中间进行插入或者删除，只会移动最少的一边的元素。

![](https://upload-images.jianshu.io/upload_images/1342490-fd825000c47dd36a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![](http://upload-images.jianshu.io/upload_images/1342490-1a27f1fd852e2c30?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 内部结构
我们来看一下内部结构：
**1\. __NSArrayI**
__NSArrayI的结构定义为:

```
@interface __NSArrayI : NSArray
{
    NSUInteger _used;
    id _list[0];
}
@end

```

`_used`是数组的元素个数,调用`[array count]`时，返回的就是`_used`的值。
这里我们可以把`id _list[0]`当作`id *_list`来用，即一个存储`id`对象的`buff`.
由于`__NSArrayI`的不可变,所以`_list`一旦分配，释放之前都不会再有移动删除操作了，只有获取对象一种操作.因此`__NSArrayI`的实现并不复杂.
**2\. __NSSingleObjectArrayI**
__NSSingleObjectArrayI的结构定义为:

```
@interface __NSSingleObjectArrayI : NSArray
{
    id object;
}
@end

```

因为只有在"创建只包含一个对象的不可变数组"时,才会得到`__NSSingleObjectArrayI`对象，所以其内部结构更加简单，一个`object`足矣.
**3\. __NSArrayM**
__NSArrayM的结构定义为:

```
@interface __NSArrayM : NSMutableArray
{
    NSUInteger _used;
    NSUInteger _offset;
    int _size:28;
    int _unused:4;
    uint32_t _mutations;
    id *_list;
}
@end

```

`__NSArrayM`稍微复杂一些，但是同样的，它的内部对象数组也是一块连续内存`id* _list`，正如`__NSArrayI`的`id _list[0]`一样
`_used`:当前对象数目
`_offset`:实际对象数组的起始偏移,这个字段的用处稍后会讨论
`_size`:已分配的`_list`大小(能存储的对象个数，不是字节数)
`_mutations`：修改标记，每次对`__NSArrayM`的修改操作都会使`_mutations`加1
`id *_list`是个循环数组.并且在增删操作时会动态地重新分配以符合当前的存储需求.

我们在上面说过，**__NSArrayM** 用了[环形缓冲区 (circular buffer)](https://link.jianshu.com/?t=http%3A%2F%2Fen.wikipedia.org%2Fwiki%2FCircular_buffer)。
并且在增删操作时会动态地重新分配以符合当前的存储需求.以一个初始包含5个对象,总大小`_size`为6的`_list`为例:
`_offset = 0`,`_used = 5`,`_size=6`

![image](http://upload-images.jianshu.io/upload_images/1342490-b858da3a89a12afd?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在末端追加3个对象后:
`_offset = 0`,`_used = 8`,`_size=8`
`_list`已重新分配

![image](http://upload-images.jianshu.io/upload_images/1342490-a55870d6fe2e7985?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

删除对象A:
`_offset = 1`,`_used = 7`,`_size=8`

![image](http://upload-images.jianshu.io/upload_images/1342490-bbf9d5188c694b41?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

删除对象E:
`_offset = 2`,`_used = 6`,`_size=8`
B,C往后移动了，E的空缺被填补

![image](http://upload-images.jianshu.io/upload_images/1342490-8e2feca17cda493e?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在末端追加两个对象:
`_offset = 2`,`_used = 8`,`_size=8`
`_list`足够存储新加入的两个对象，因此没有重新分配，而是将两个新对象存储到了`_list`起始端

![image](http://upload-images.jianshu.io/upload_images/1342490-80e5b222a0214da1?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)








#### NSMutableArray的方法
正如 [NSMutableArray Class Reference](https://link.jianshu.com?t=https%3A%2F%2Fdeveloper.apple.com%2Flibrary%2Fios%2Fdocumentation%2FCocoa%2FReference%2FFoundation%2FClasses%2FNSMutableArray_Class%2FReference%2FReference.html) 的讨论，每个 **NSMutableArray** 子类必须实现下面 7 个方法：

*   **- count**
*   **- objectAtIndex:**
*   **- insertObject:atIndex:**
*   **- removeObjectAtIndex:**
*   **- addObject:**
*   **- removeLastObject**
*   **- replaceObjectAtIndex:withObject:**

毫不意外的是，**__NSArrayM** 履行了这个规定。然而，**__NSArrayM** 的所有实现方法列表相当短且不包含 21 个额外的在 **NSMutableArray** 头文件列出来的方法。谁负责执行这些方法呢？

这证明它们只是 **NSMutableArray** 类自身的一部分。这会相当的方便：任何 **NSMutableArray** 的子类只须实现 7 个最基本的方法。所有其它高等级的抽象建立在它们的基础之上。例如 **- removeAllObjects** 方法简单地往回迭代，一个个地调用 **- removeObjectAtIndex:**。
## 遍历数组的n个方法
#### 1.for 循环
```
for (int i = 0;  i < array.count; ++i) {
       id object = array[i];
  }
```

#### 2.NSEnumerator
```
NSArray *anArray = /*...*/;
NSEnumerator *enumerator = [anArray objectEnumerator];
id object;
while((object = [enumerator nextObject])!= nil){

}
```
#### 3.forin
快速遍历
```
NSArray *anArray = /*...*/;
for (id object in anArray) {

  }
```
#### 4.enumerateObjectsWithOptions:usingBlock:
通过block回调，在子线程中遍历，对象的回调次序是乱序的,而且调用线程会等待该遍历过程完成:
```
[array enumerateObjectsWithOptions:NSEnumerationConcurrent usingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        xxx
  }];
```
性能比较如图
![](http://upload-images.jianshu.io/upload_images/1342490-f6cd704688cccb1d?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
横轴为遍历的对象数目,纵轴为耗时,单位us.
从图中看出，在对象数目很小的时候，各种方式的性能差别微乎其微。随着对象数目的增大， 性能差异才体现出来.
其中for in的耗时一直都是最低的，当对象数高达100万的时候，for in耗时也没有超过5ms.
其次是for循环耗时较低.
反而，直觉上应该非常快速的多线程遍历方式却是性能最差的。








## 遍历的速度特点探究
#### 1.for 循环&for in
这两个速度是最快的，我们就以forin为例。forin遵从了`NSFastEnumeration`协议，它只有一个方法：
```
- (NSUInteger)countByEnumeratingWithState:
                        (NSFastEnumerationState *)state
                             objects:(id *)stackbuffer 
                                  count:(NSUInteger)len;
```
它直接从C数组中取对象。对于可变数组来说，它最多只需要两次就可以获取全部全速。如果数组还没有构成循环，那么第一次就获得了全部元素，跟不可变数组一样。但是如果数组构成了循环，那么就需要两次，第一次获取对象数组的起始偏移到循环数组末端的元素,第二次获取存放在循环数组起始处的剩余元素。
而for循环之所以慢一点，是因为for循环的时候每次都要调用`objectAtIndex:`
假如我们遍历的时候不需要获取当前遍历操作所针对的下标，我们就可以选择forin。
#### 2.block循环
这种循环虽然是最慢的，但是我们在遍历的时候可以直接从block中获取更多的信息，并且可以修改块的方法签名，以免进行类型转换操作。
```
for(NSString *key in aDictionary){
    NSString *object = (NSString *)aDictionary[key];
}
NSDictionary *aDictionary = /*...*/;
[aDictionary enumerateKeysAndObjectsUsingBlock:
  ^(NSString *key,NSString *obj,BOOL *stop){
  
  }];

```
并且如果需要需要并发的时候，也可以方便的使用dispatch_group/dispatch_apply。

另外还有一点：如果数组的数量过多，除了block遍历，其他的遍历方法都需要添加autoreleasePool方法来优化。block遍历就不需要，因为系统在实现它的时候就已经实现了相关处理。

## 参考文献

[Effective Objective-C 2.0:编写高质量iOS与OS X代码的52个有效方法](https://detail.tmall.com/item.htm?spm=a230r.1.14.6.6f3c5210AspBot&id=560781916540&cm_id=140105335569ed55e27b&abbucket=14)

 [NSMutableArray Class Reference](https://link.jianshu.com?t=https%3A%2F%2Fdeveloper.apple.com%2Flibrary%2Fios%2Fdocumentation%2FCocoa%2FReference%2FFoundation%2FClasses%2FNSMutableArray_Class%2FReference%2FReference.html)

[CFArray 的历史渊源及实现原理](https://www.desgard.com/CFArray/)

[Objective-C 数组遍历的性能及原理](https://www.jianshu.com/p/66f8410c6bbc)
