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

















































