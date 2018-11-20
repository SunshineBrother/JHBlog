## AutoreleasePool自动释放池

`Autorelease机制`是iOS开发者管理对象内存的好伙伴，MRC中，调用`[obj autorelease]`来延迟内存的释放是一件简单自然的事，ARC下，我们甚至可以完全不知道Autorelease就能管理好内存。而在这背后，objc和编译器都帮我们做了哪些事呢，它们是如何协作来正确管理内存的呢。


### Autorelease对象什么时候释放

新建一个 Xcode 项目，将项目调整成 MRC，`Target -> Build Sttings -> All -> 搜索‘automatic’ -> 把 Objective-C Automatic Reference Counting 设置为 NO`

在 MRC 中，需要使用 retain/release/autorelease 手动管理内存,如下代码
```
int main(int argc, const char * argv[]) {
@autoreleasepool {
NSLog(@"****A***");
Person *p = [[Person alloc]init];
[p release];
NSLog(@"***B***");
}
NSLog(@"***C***");
return 0;
}
```
打印结果
![AutoreleasePool](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/AutoreleasePool.png)

如果使用 autorelease，就需要用到自动缓存池了，代码如下：
```
int main(int argc, const char * argv[]) {
@autoreleasepool {
NSLog(@"****A***");
Person *p = [[[Person alloc]init] autorelease];
NSLog(@"***B***");
}
NSLog(@"***C***");
return 0;
}
```
打印结果
![AutoreleasePool1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/AutoreleasePool1.png)

**AutoreleasePool具体做了什么呢**
想要查看`AutoreleasePool`具体做了什么，我们首先要看`AutoreleasePool`的实现原理

`通过 xcrun -sdk iphoneos clang -arch arm64 -rewrite-objc main.m 命令将 main.m 转成 C++ 代码`

我们找到`main.cpp`文件，拉到最后面，我们可以找到`AutoreleasePool`的实现
```
int main(int argc, const char * argv[]) {
/* @autoreleasepool */ { __AtAutoreleasePool __autoreleasepool; 

Person *p = ((Person *(*)(id, SEL))(void *)objc_msgSend)((id)((Person *(*)(id, SEL))(void *)objc_msgSend)((id)((Person *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("Person"), sel_registerName("alloc")), sel_registerName("init")), sel_registerName("autorelease"));

}
return 0;
}
```

会发现 @autoreleasepool 被转成
```
__AtAutoreleasePool __autoreleasepool;
```
而__AtAutoreleasePool我们全局查找发现他是一个结构体
```
struct __AtAutoreleasePool {
__AtAutoreleasePool() {atautoreleasepoolobj = objc_autoreleasePoolPush();}
~__AtAutoreleasePool() {objc_autoreleasePoolPop(atautoreleasepoolobj);}
void * atautoreleasepoolobj;
};
```

下面这段代码构造函数，在创建结构体的时候调用
```
__AtAutoreleasePool() { // 构造函数，在创建结构体的时候调用
atautoreleasepoolobj = objc_autoreleasePoolPush();
}
```
下面这段代码析构函数，在结构体销毁的时候调用
```
~__AtAutoreleasePool() { // 析构函数，在结构体销毁的时候调用
objc_autoreleasePoolPop(atautoreleasepoolobj);
}
```


```
@autoreleasepool {
Person *p = [[[Person alloc]init] autorelease];
}
```
上面这段代码其实就是这个样子
```
atautoreleasepoolobj = objc_autoreleasePoolPush();
Person *person = [[[Person alloc] init] autorelease];
objc_autoreleasePoolPop(atautoreleasepoolobj);
```

**AutoreleasePoolPage**

对于`objc_autoreleasePoolPush`和`objc_autoreleasePoolPop`
的实现我们可以在[runtime源码](https://opensource.apple.com/source/objc4/)中查找相关实现

```
objc_autoreleasePoolPush(void)
{
return AutoreleasePoolPage::push();
}

void
objc_autoreleasePoolPop(void *ctxt)
{
AutoreleasePoolPage::pop(ctxt);
}
```
我们研究可以发现，`push()`函数和`pop(ctxt)`函数都是有`AutoreleasePoolPage`类来调用的。

对于`AutoreleasePoolPage`类，我们查看成员变量，对于一些静态常亮我们就不过多的探究，我们就来查看一下成员变量。
```
class AutoreleasePoolPage 
{
magic_t const magic;
id *next;
pthread_t const thread;
AutoreleasePoolPage * const parent;
AutoreleasePoolPage *child;
uint32_t const depth;
uint32_t hiwat;
// ...
}
```

- 1、每个`AutoreleasePoolPage对象`占用`4096`字节内存，除了用来存放它内部的成员变量，剩下的空间用来存放autorelease对象的地址
- 2、所有的`AutoreleasePoolPage`对象通过`双向链表`的形式连接在一起
- 3、调用push方法会将一个`POOL_BOUNDARY`入栈，并且返回其存放的内存地址
- 4、调用pop方法时传入一个`POOL_BOUNDARY`的内存地址，会从最后一个入栈的对象开始发送release消息，直到遇到这个`POOL_BOUNDARY`
- 5、`id *next`指向了下一个能存放`autorelease对象地址`的区域  

![AutoreleasePool2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/内存管理/AutoreleasePool2.png)







