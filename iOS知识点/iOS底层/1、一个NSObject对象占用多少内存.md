 ## 一个NSObject对象占用多少内存

我们平时所编写的Object-C代码，底层实现都是C/C++代码，

![Object-C代码底层实现](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/Object-C代码底层实现.png)

所以OC的面向对象都是基于C/C++的数据结构实现的

`思考:OC对象主要是基于C/C++的什么数据结构实现的呢？？？`


想要了解OC对象主要是基于C/C++的什么数据结构实现的，我们首先要做的就是将Object-C代码转化为C/C++代码，这样我们才能清楚的看清是怎么实现的


然后我们打开终端，在命令行找到cd到文件目录，然后中输入：
```
clang -rewrite-objc main.m 

```

命令可以将main.m编译成C++的代码，改成不同的文件名，就会生成不同的c++代码 
这是就生成了main.cpp这个c++文件，打开文件代码 
查看该main.cpp最底下的main函数， 

但是不同平台支持的代码肯定是不一样的，像平台有`Windows`、`mac`、`iOS`，架构有`模拟器(i386)、32bit(armv7)、64bit（arm64）`，我们使用`iOS`，他的架构现在基本上都是`64bit（arm64）`

```
xcrun  -sdk  iphoneos  clang  -arch  arm64  -rewrite-objc OC源文件  -o  输出的CPP文件
如果需要链接其他框架，使用-framework参数。比如-framework UIKit
```
在终端输入命令以后，我们会生成一个`main.cpp`文件，打开`main.cpp`文件文件，我们把`main.cpp`文件拉到最下面，我们会看到这样一段代码
```
int main(int argc, const char * argv[]) {
/* @autoreleasepool */ { __AtAutoreleasePool __autoreleasepool; 


	}
	return 0;
}
```
这一段代码就是我们OC代码中的`mian`函数的实现
```
int main(int argc, const char * argv[]) {
	@autoreleasepool {

	}
	return 0;
}

```

这时我们在`mian`函数写入这一段代码，然后我们点击进入，查看代码实现
```
NSObject *obj = [[NSObject alloc] init];
```
点击`NSObject`进入内部，可以看到NSObject底层实现
```
struct NSObject {
	Class isa;  
};
```
我们用`NSObject_IMPL`查找在c++文件中具体的实现

```
struct NSObject_IMPL {
	Class isa;
};
```


我们再一次执行命令
```
xcrun  -sdk  iphoneos  clang  -arch  arm64  -rewrite-objc mian.m
```
生成的C++代码为
```
int main(int argc, const char * argv[]) {
	/* @autoreleasepool */ { __AtAutoreleasePool __autoreleasepool; 
	NSObject *obj = ((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)((NSObject *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("NSObject"), sel_registerName("alloc")), sel_registerName("init"));

	}
	return 0;
}
```
有两个方法可以打印内存大小
```
// 获得NSObject实例对象的成员变量所占用的大小  
NSLog(@"%zd", class_getInstanceSize([NSObject class]));

// 获得obj指针所指向内存的大小  
NSLog(@"%zd", malloc_size((__bridge const void *)obj));
```
打印结果


![NSObject对象内存](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/NSObject对象内存.png)

### 一个OC对象在内存中是怎么样布局的呢

我们在C++文件中找到NSObject的实现
OC代码
```
struct NSObject {
	Class isa;  
};
```
c++代码
```
struct NSObject_IMPL {
	Class isa;
};
```
我们知道一个指针是`8个字节`，但是NSObject对象打印`16个字节`,他们是怎么样布局的呢

![NSObject对象内存地址](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/NSObject对象内存地址.png)

我们可以根据内存地址实时查看内存分配情况`Debug -> Debug Workfllow -> View Memory （Shift + Command + M）`

![查看内存数据](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/查看内存数据.png)

![查看内存数据1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/查看内存数据1.png)


![查看内存数据2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/查看内存数据2.png)


我们也可以直接使用 `LLDB命令`来查看内存地址
**常用LLDB命令**
- print、p：打印
- po：打印对象
- 读取内存
    - memory read/数量格式字节数  内存地址
    - x/数量格式字节数  内存地址（格式：x是16进制，f是浮点，d是10进制；字节大小
    ：b：byte 1字节，h：half word 2字节，w：word 4字节，g：giant word 8字节）
    
- 修改内存中的值（memory  write  内存地址  数值   memory  write  0x0000010  10）


**问题1**：假设我创建一个`Studeng`类，里面有`age`,`number`两个属性，那么他的内存是多大呢？

```
Student *stu = [[Student alloc]init];
stu->_number = 4;
stu->_age = 5;
```

我们先执行命令，查看一下c++源码
```
struct Student_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	int _number;
	int _age;
};
```
我们在知道结果之前大概猜猜内存是多大呢？16，24，32...


猜16字节的猜对了，我们先看看结果


![Student内存打印](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/Student内存打印.png)

我们用`LLDB命令`打印一下
```
a9 11 00 00 01 80 1d 00 04 00 00 00 05 00 00 00
```

 为什么会是`04 00 00 00`和`05 00 00 00`呢，而不是`00 00 00 04`和`00 00 00 o5`,这个就要考虑[大端小端](https://baike.baidu.com/item/大小端模式/6750542?fromtitle=大端小端&fromid=15925891&fr=aladdin)，具体概念自己可以去查。


但是为什么会是16个字节呢，因为int类型占用4个字节，两个int类型8个字节，一个`isa`8个字节，因为刚刚占满16个字节，对象就没有在开辟新的空间了


如果在多一个`height`会占用几个字节呢

![Student内存打印2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/Student内存打印2.png)


`占用32个字节，大家是不是很惊讶，没有猜到`

其实这又要提到一个新的知识点了`内存对齐`,我们知道OC对象就是C++结构体，`而结构体的大小必须是最大成员大小的倍数`，当在多了一个`height`以后，内存不够用了，然后就需要扩展了。

**如果是这样呢，占用内存是多少**
```
@interface Person : NSObject{
	@public
	int _number;
	int _age;
}
@end

@implementation Person

@end

@interface Student : Person{
	@public
		int _height;
	}
@end

@implementation Student

@end
```
`Student`继承自`Person`

![Student内存打印](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/Student内存打印2.png)

我们生成C++代码
```
struct Student_IMPL {
	struct Person_IMPL Person_IVARS;
	int _height;
};

struct Person_IMPL {
	struct NSObject_IMPL NSObject_IVARS;
	int _number;
	int _age;
};

struct NSObject_IMPL {
	Class isa;
};

```
整理一下就是这样
```
struct Student_IMPL {
	Class isa;
	int _number;
	int _age;
	int _height;
};

```
[参考demo](https://github.com/SunshineBrother/iOSDemo)

