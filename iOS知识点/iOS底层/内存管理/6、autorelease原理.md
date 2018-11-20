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


如果使用 autorelease，就需要用到自动缓存池了，代码如下：




































