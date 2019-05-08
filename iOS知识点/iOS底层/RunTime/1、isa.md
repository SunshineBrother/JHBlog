## isa指针

我们在研究OC对象的时候已经知道了，实力对象的`isa`指向类对象，类对象的`isa`指向元类对象。其实这样说还是有一点不对的，应该说在`arm64架构`之前，isa就是一个普通的指针，存储着`Class`、 `Meta-Class` 对象的内存地址；但是从`arm64`之后，对`isa`进行了优化，变成了一个`共用体（union）`结构，还使用`位域`来存放跟多的信息。


我们在[这里](https://opensource.apple.com/tarballs/objc4/)下载runtime源码，然后查找`struct objc_object`里面的`isa`,这里我们只研究arm64架构`isa`
```
struct {
uintptr_t nonpointer        : 1;
uintptr_t has_assoc         : 1;
uintptr_t has_cxx_dtor      : 1;
uintptr_t shiftcls          : 33; // MACH_VM_MAX_ADDRESS 0x1000000000
uintptr_t magic             : 6;
uintptr_t weakly_referenced : 1;
uintptr_t deallocating      : 1;
uintptr_t has_sidetable_rc  : 1;
uintptr_t extra_rc          : 19;
#       define RC_ONE   (1ULL<<45)
#       define RC_HALF  (1ULL<<18)
};
```
我们发现`isa`的结构是这种`共用体（union）`结构，其实使用这种共用体是一种优化，`isa`不在单独存放的是一个指针信息了，里面存放了更多的其他信息。

### 概念
想要明白`isa`变成`共用体（union）`结构,是一种优化，我们需要先了解一些概念
- 1、位运算
- 2、字节和位
- 3、位域
- 4、共用体

#### 位运算

位运算的运算符有下面几个
- 1、左移：`<<`
- 2、右移：`>>`
- 3、按位或：`|`
- 4、按位与：`&`
- 5、按位取反：`~`
- 6、按位异或：`^` 其功能是参与运算的两数各对应的二进位相异或，当两对应的二进位相异时，结果为1

**与操作&**
`与操作&`：都是1则为1，一个0就是0。可以用来取出来特定的位。例如一个二进制`0b 0000 0111`,我们分别想取出第一位`1`和第四位`0`。
````
 0000 0111            0000 0111
&0000 0001           &0000 1000
--------------       --------------
 0000 0001            0000 0000
````
我们可以发现我们使用按位与&的时候，我们如果想取出哪一位，把改为设置为1，其他位设置为0就可以了。

介绍到了`&`，我再来介绍一个概念，`掩码：一般用来按位与(&)运算的`，具体有什么作用，我们下面会进行讲解


**或操作|**

`或操作|`：一个是1，则为1，全部是0才为0。
例如一个二进制`0b 0101 1010`。

```
  0101 1010
| 0001 1100           
--------------
  0101 1110
```
`如果我们想要某一位，就该该位或上一个0`

**左移：`<<`**
二进制位全部左移若干位，左边的丢弃，右边补0

 - 1、1<<0   1左移0位，0b0000 0001
 - 2、1<<1   1左移1位，0b0000 0010
 - 3、1<<2   1左移2位，0b0000 0100
 - 4、1<<3   1左移3位，0b0000 1000

**右移：`>>`**

二进制右移若干位，正数左边补0，负数左边补1，右边丢弃。

例如 12>>2
0000 1100 = 12
0000 0011 = 2 (右移后)

特点：每右移一位，就除以一次2。a>>n 就是 a除以2的n次方


#### 字节和位
- Bit意为“位”或“比特”，是计算机运算的基础，属于二进制的范畴；
- Byte意为“字节”，是计算机文件大小的基本计算单位；

通常用bit来作数据传输的单位，因为物理层，数据链路层的传输对于用户是透明的，而这种通信传输是基于二进制的传输。在应用层通常是用byte来作单位，表示文件的大小，在用户看来就是可见的数据大小

**换算**
1 Byte = 8 Bits
1 KB = 1024 Bytes
1 MB = 1024 KB
1 GB = 1024 MB
另外，Byte通常简写为B(大写），而bit通常简写为b（小写）。可以这么记忆，大写的为大单位，实际数值小，小写的为小单位，实际数值较大，1B=8b。

#### 位域

所谓”位域“是把一个字节中的二进位划分为几 个不同的区域， 并说明每个区域的位数。每个域有一个域名，允许在程序中按域名进行操作。它实际上是C语言提供的一种数据结构。

使用位域的好处是：   
- 1.有些信息在存储时，并不需要占用一个完整的字节， 而只需占几个或一个二进制位。例如在存放一个开关量时，只有0和1 两种状态， 用一位二进位即可。这样节省存储空间，而且处理简便。 这样就可以把几个不同的对象用一个字节的二进制位域来表示。
- 2.可以很方便的利用位域把一个变量给按位分解。比如只需要4个大小在0到3的随即数，就可以只rand()一次，然后每个位域取2个二进制位即可，省时省空间


struct 位域结构名 
{ 位域列表 };
其中位域列表的形式为： 类型说明符 位域名：位域长度;
```
struct {
char tall : 1;
char rich : 1;
char handsome : 1;
} _tallRichHandsome;
```

#### 4、共用体

union中可以定义多个成员，`union的大小由最大的成员的大小决定`；

union成员共享同一块大小的内存，一次只能使用其中的一个成员； 
对union某一个成员赋值，会覆盖其他成员的值（但前提是成员所占字节数相同，当成员所占字节数不同时只会覆盖相应字节上的值，比如对char成员赋值就不会把整个int成员覆盖掉，因为char只占一个字节，而int占四个字节）；
union量的存放顺序是所有成员都从低地址开始存放的。


### 案例

例如我们创建一个`Person`类，里面有三个`Bool`属性，`tall`、`rich`、`handsome`。 

```
@property (nonatomic,assign) BOOL tall;
@property (nonatomic,assign) BOOL rich;
@property (nonatomic,assign) BOOL handsome;
```
我们知道这三个属性占用了`3个字节`。其实这个时候我们可以考虑到使用`位域`或者`共用体`的概念,使用`位（Bit）的0和1来代表这三个属性的YES NO`，那个三个属性就只是占用了`2个字节`

**位域代码**
```
@interface Person()
{
// 位域
struct {
char tall : 1;
char rich : 1;
char handsome : 1;
} _tallRichHandsome;
}
@end
@implementation Person

- (void)setTall:(BOOL)tall
{
_tallRichHandsome.tall = tall;
}

- (BOOL)isTall
{
return !!_tallRichHandsome.tall;
}

- (void)setRich:(BOOL)rich
{
_tallRichHandsome.rich = rich;
}

- (BOOL)isRich
{
return !!_tallRichHandsome.rich;
}

- (void)setHandsome:(BOOL)handsome
{
_tallRichHandsome.handsome = handsome;
}

- (BOOL)isHandsome
{
return !!_tallRichHandsome.handsome;
}
```

为什么会出现`!!`，我们知道`!(-1) == NO` ，`!`上一个存在的值是`NO`，`!!`两次那么只会出现YES 和 NO了。

**共用体**

其实我们观察isa的类型，发现isa其实是使用的`共用体`，
```
#define TallMask (1<<0)
#define RichMask (1<<1)
#define HandsomeMask (1<<2)


@interface Person()
{
union {
int bits;
struct {
char tall : 1;
char rich : 1;
char handsome : 1;
};
} _tallRichHandsome;
}
@end

@implementation Person

- (void)setTall:(BOOL)tall
{
if (tall) {
_tallRichHandsome.bits |= TallMask;
} else {
_tallRichHandsome.bits &= ~TallMask;
}
}

- (BOOL)isTall
{
return !!(_tallRichHandsome.bits & TallMask);
}

- (void)setRich:(BOOL)rich
{
if (rich) {
_tallRichHandsome.bits |= RichMask;
} else {
_tallRichHandsome.bits &= ~RichMask;
}
}

- (BOOL)isRich
{
return !!(_tallRichHandsome.bits & RichMask);
}

- (void)setHandsome:(BOOL)handsome
{
if (handsome) {
_tallRichHandsome.bits |= HandsomeMask;
} else {
_tallRichHandsome.bits &= ~HandsomeMask;
}
}

- (BOOL)isHandsome
{
return !!(_tallRichHandsome.bits & HandsomeMask);
}
```

`#define TallMask (1<<0)`这是掩码，为了方便阅读。
```
struct {
char tall : 1;
char rich : 1;
char handsome : 1;
};
```
其实也仅仅是方便阅读的作用，让我们知道`tall`、`rich`、`handsome`是在哪一位上，去掉并不影响代码。

### 扩展：位运算应用

其实我们可以看到苹果官方文档上面有很多地方运用到了位运算
```
typedef NS_ENUM(NSInteger, LXDAuthorizationType)
{
LXDAuthorizationTypeNone = 0,
LXDAuthorizationTypePush = 1 << 0,  ///<    推送授权
LXDAuthorizationTypeLocation = 1 << 1,  ///<    定位授权
LXDAuthorizationTypeCamera = 1 << 2,    ///<    相机授权
LXDAuthorizationTypePhoto = 1 << 3,     ///<    相册授权
LXDAuthorizationTypeAudio = 1 << 4,  ///<    麦克风授权
LXDAuthorizationTypeContacts = 1 << 5,  ///<    通讯录授权
};

```


```
typedef NS_OPTIONS(NSUInteger, UIViewAutoresizing) {
UIViewAutoresizingNone                 = 0,
UIViewAutoresizingFlexibleLeftMargin   = 1 << 0,
UIViewAutoresizingFlexibleWidth        = 1 << 1,
UIViewAutoresizingFlexibleRightMargin  = 1 << 2,
UIViewAutoresizingFlexibleTopMargin    = 1 << 3,
UIViewAutoresizingFlexibleHeight       = 1 << 4,
UIViewAutoresizingFlexibleBottomMargin = 1 << 5
};
```
太多了，我就不一一列举了。其实我们在有些情况下也可以参考这样的设计。
 例如
 ```
 typedef enum {
 OptionsOne = 1<<0,   // 0b0001
 OptionsTwo = 1<<1,   // 0b0010
 OptionsThree = 1<<2, // 0b0100
 OptionsFour = 1<<3   // 0b1000
 } Options
 
 - (void)setOptions:(Options)options
 {
 if (options & OptionsOne) {
 NSLog(@"包含了OptionsOne");
 }
 
 if (options & OptionsTwo) {
 NSLog(@"包含了OptionsTwo");
 }
 
 if (options & OptionsThree) {
 NSLog(@"包含了OptionsThree");
 }
 
 if (options & OptionsFour) {
 NSLog(@"包含了OptionsFour");
 }
 }
 
 
 调用上面方法
 [self setOptions: OptionsOne | OptionsFour];
 
 ```


### 最后

![isa](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/RunTime/isa.png)

最后我们在看一下isa结构吧
- 1、nonpointer：0，代表普通的指针，存储着Class、Meta-Class对象的内存地址；1，代表优化过，使用位域存储更多的信息
- 2、has_assoc：是否有设置过关联对象，如果没有，释放时会更快
- 3、has_cxx_dtor：是否有C++的析构函数（.cxx_destruct），如果没有，释放时会更快
- 4、shiftcls：存储着Class、Meta-Class对象的内存地址信息
- 5、magic：用于在调试时分辨对象是否未完成初始化
- 6、weakly_referenced：是否有被弱引用指向过，如果没有，释放时会更快
- 7、deallocating：对象是否正在释放
- 8、extra_rc：里面存储的值是引用计数器 
- 9、has_sidetable_rc：引用计数器是否过大无法存储在isa中；如果为1，那么引用计数会存储在一个叫SideTable的类的属性中

    




















