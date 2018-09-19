## Block底层解密 
block想必做过一段iOS开发的同学都用过吧，但是大部分人都是仅仅会用，不怎么理解他是怎么实现的，今天就让我们来一步一步的分析一下底层是怎么实现的吧。

### 查看源码

```
void (^block)(void) =  ^(){
NSLog(@"this is a block!");
};
```

这样一个简单的`block`块大家都应该知道吧，但是这个`block`块是怎么实现的呢？

想要了解OC对象主要是基于C/C++的什么数据结构实现的，我们首先要做的就是将Object-C代码转化为C/C++代码，这样我们才能清楚的看清是怎么实现的

然后我们打开终端，在命令行找到cd到文件目录，然后中输入：
```
xcrun  -sdk  iphoneos  clang  -arch  arm64  -rewrite-objc main.m
```
执行结束以后，会生成`main.cpp`文件，我们打开`main.cpp`文件，拉到最下边就是我们的`main`函数实现的。

我们得到c++代码的block实现
```
void (*block)(void) = ((void (*)())&__main_block_impl_0((void *)__main_block_func_0, &__main_block_desc_0_DATA));
```

我们知道`(void *)`这种类型的都是类型的强制转换，为了更好的识别我们的这个Block代码，我们把类型转化去掉
```
void (*block)(void) = &__main_block_impl_0(__main_block_func_0,
&__main_block_desc_0_DATA));
```

我们在分别查询`__main_block_impl_0`,`__main_block_func_0`,`__main_block_desc_0_DATA`代表什么意思

**__main_block_impl_0**

```
struct __main_block_impl_0 {
struct __block_impl impl;
struct __main_block_desc_0* Desc;
// 构造函数（类似于OC的init方法），返回结构体对象
__main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, int flags=0) {
impl.isa = &_NSConcreteStackBlock;
impl.Flags = flags;
impl.FuncPtr = fp;
Desc = desc;
}
};
```

我们查看一下`__block_impl`里面是什么
```
struct __block_impl {
void *isa;
int Flags;
int Reserved;
void *FuncPtr;
};
```

**__main_block_func_0**

```
// 封装了block执行逻辑的函数
static void __main_block_func_0(struct __main_block_impl_0 *__cself) {

NSLog((NSString *)&__NSConstantStringImpl__var_folders_2r__m13fp2x2n9dvlr8d68yry500000gn_T_main_c60393_mi_0);
}
```
**__main_block_desc_0_DATA**
```
static struct __main_block_desc_0 {
size_t reserved;
size_t Block_size;//内存大小描述
} __main_block_desc_0_DATA
```


所以我们可以总结
- 1、`__main_block_impl_0`中`__block_impl`存放的是一些变量信息，其中存在`isa`，所以可以判断block的本质其实就是OC对象
- 2、初始化
```
__main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, int flags=0) {
impl.isa = &_NSConcreteStackBlock;
impl.Flags = flags;
impl.FuncPtr = fp;
Desc = desc;
}
```
我们在来查看Block方法
```
void (*block)(void) = &__main_block_impl_0(__main_block_func_0,
&__main_block_desc_0_DATA));
```
对应上面的初始化我们可以看出第一个参数传递的是`执行方法`，第二个参数为`描述信息`


**Block底层结构图**

![Block1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/Block1.png)


### 成员变量的捕获
为了保证block内部能够正常的访问外部变量，block有个变量捕获机制,这里我们先说结果，然后在进行证明


![Block2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/Block2.png)


我们在`main`函数写下这些代码，然后在把`main`函数生成c++代码
```
#import <Foundation/Foundation.h>
int height = 180;
int main(int argc, const char * argv[]) {
@autoreleasepool {


int age = 10;
static int weight = 65;
void (^block)(void) =  ^(){
NSLog(@"age---------%d",age);
NSLog(@"weight---------%d",weight);
NSLog(@"height---------%d",height);
};
block();
}
return 0;
}
```
我们直接找到c++代码里面存放变量的结构体`__main_block_impl_0`
```
struct __main_block_impl_0 {
struct __block_impl impl;
struct __main_block_desc_0* Desc;
int age;
int *weight;
__main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, int _age, int *_weight, int flags=0) : age(_age), weight(_weight) {
impl.isa = &_NSConcreteStackBlock;
impl.Flags = flags;
impl.FuncPtr = fp;
Desc = desc;
}
};
```

我们可以看到变量捕获为`age`,`*weight`,但是没有捕获到全局变量`height`。为了方便的理解，我们先来了解一些内存空间的分配。
- 1、栈区(stack) 由编译器自动分配并释放，存放函数的参数值，局部变量等。栈空间分静态分配 和动态分配两种。静态分配是编译器完成的，比如自动变量(auto)的分配。动态分配由alloca函数完成。
- 2、堆区(heap) 由程序员分配和释放，如果程序员不释放，程序结束时，可能会由操作系统回收 ，比如在ios 中 alloc 都是存放在堆中。
- 3、全局区(静态区) (static) 全局变量和静态变量的存储是放在一起的，初始化的全局变量和静态变量存放在一块区域，未初始化的全局变量和静态变量在相邻的另一块区域，程序结束后有系统释放。
- 4、程序代码区 存放函数的二进制代码

总结：
- 1、因为自动变量(auto)分配的内存空间在`栈区(stack)`，编译器会自动帮我们释放，如果我们把block写在另外一个方法中调用，自动变量`age`就会被释放，block在使用的时候就已经被释放了，所以需要重新copy一下
- 2、静态变量在程序结束后有系统释放，所以不需要担心被释放，block只需要知道他的内存地址就行
- 3、对于全局变量，任何时候都可以直接访问，所以根本就不需要捕获

 
### Block类型

block有3种类型，可以通过调用class方法或者isa指针查看具体的类型，但是最终都是继承者NSBlock类型
- 1、__NSGlobalBlock__，没有访问auto变量
- 2、__NSStackBlock__，访问了auto变量
- 3、__NSMallocBlock__，__NSStackBlock__调用了copy方法

她们的内存分配

![Block3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/Block3.png)


每一种类型的Block调用copy后的结果
- 1、__NSStackBlock__原来在栈区，copy以后从栈复制到堆
- 2、__NSGlobalBlock__原来在程序的数据段，copy以后什么也不做
- 3、__NSMallocBlock__原来在堆区，复制以后引用计数加1
我们来写一小段代码证明一下
```
void (^block1)(void) =  ^(){
NSLog(@"block1");
};
int age = 10;
void (^block2)(void) =  ^(){
NSLog(@"block2");
NSLog(@"age---------%d",age);
};
void (^block3)(void) = [ ^(){
NSLog(@"block3");
NSLog(@"age---------%d",age);
} copy];

NSLog(@"block1:%@---->block2:%@----->block3:%@",[block1 class],[block2 class],[block3 class]);
```

打印结果为

![Block4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/Block4.png)

为什么`block2`打印类型为`__NSMallocBlock__`,而不是`__NSStackBlock__`，因为ARC环境导致了，ARC会自动帮我们copy了一下`__NSStackBlock__`










