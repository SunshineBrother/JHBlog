## NSException抛出异常&NSError简单介绍


### NSException的简单介绍

![NSException1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/NSException1.png)

上面这张图想必大家都不陌生吧
其实控制台输出的日志信息就是NSException产生的，一旦程序抛出异常，程序就会崩溃，控制台就会有这些崩溃日志。

 这个类是专门表示异常的，Cocoa框架要求所有的异常都是它或者是它子类的实例，当实例调用raise或者throw方法时就会出现我们如上图之类的崩溃，并给出它的一些相关信息。下面介绍NSException对象的几个重要的属性。

- name :  用于唯一地识别异常的短字符串。名称是必需的
- reason:一个更长的包含造成异常原因的“人类可读的”字符串。原因是必需的。
- userInfo：主要当异常被抛出时，返回原因等信息的一个字典。

**异常处理**

![NSException](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/NSException.png)

上面这幅图是官网给出的一个图

- @try - 定义一个代码块，它是一个异常处理域：可能引发异常的代码。
- @catch()- 定义一个包含代码的块，用于处理块中抛出的异常@try。参数@catch是本地抛出的异常对象; 这通常是一个NSException对象，但也可以是其他类型的对象，例如NSString对象。
- @finally - 定义一个相关代码块，无论是否抛出异常，随后都会执行该代码块。
- @throw - 抛出异常; 这个指令的行为几乎与raise方法相同NSException。您通常会抛出NSException对象


最简单的使用
```
//异常的名称
NSString *exceptionName = @"异常的名称";
//异常的原因
NSString *exceptionReason = @"我异常的原因";
//异常的信息
NSDictionary *exceptionUserInfo = nil;

NSException *exception = [NSException exceptionWithName:exceptionName reason:exceptionReason userInfo:exceptionUserInfo];

NSString *test = @"test";

if ([test isEqualToString:@"test"]) {
//抛异常
@throw exception;
}
```
![NSException2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/NSException2.png)


系统也给我们提供了很多种异常可以直接使用
```
//系统提供了很多异常可以直接使用
FOUNDATION_EXPORT NSString * const NSGenericException;
FOUNDATION_EXPORT NSString * const NSRangeException;
FOUNDATION_EXPORT NSString * const NSInvalidArgumentException;
FOUNDATION_EXPORT NSString * const NSInternalInconsistencyException;

FOUNDATION_EXPORT NSString * const NSMallocException;

FOUNDATION_EXPORT NSString * const NSObjectInaccessibleException;
FOUNDATION_EXPORT NSString * const NSObjectNotAvailableException;
FOUNDATION_EXPORT NSString * const NSDestinationInvalidException;

FOUNDATION_EXPORT NSString * const NSPortTimeoutException;
FOUNDATION_EXPORT NSString * const NSInvalidSendPortException;
FOUNDATION_EXPORT NSString * const NSInvalidReceivePortException;
FOUNDATION_EXPORT NSString * const NSPortSendException;
FOUNDATION_EXPORT NSString * const NSPortReceiveException;

FOUNDATION_EXPORT NSString * const NSOldStyleException;


```

**用途**

- 1、可以用来捕获异常，防止程序的崩溃。当你意识到某段代码可能存在崩溃的危险，那么你就可以通过捕获异常来防止程序的崩溃
- 2、分类(category) + runtime + 异常的捕获 来防止Foundation一些常用方法使用不当而导致的崩溃。其原理就是利用category、runtime来交换两个方法，并且在方法中捕获异常进行相应的处理


数组越界这是一个十分常见的问题，这里我们就来简单的解决一下数组越界问题
```
NSMutableArray *arr = [NSMutableArray arrayWithObject:@[@"1"]];
NSLog(@"%@",arr[2]);

NSLog(@"%s",__func__);
```
上面的代码肯定会出现下面这个错误
![NSException3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/NSException3.png)

但是我们可以在数组越界的时候进行一个`NSException`处理，那么我们的程序就不会闪退


```
#import "NSMutableArray+Extension.h"
#import <objc/runtime.h>
@implementation NSMutableArray (Extension)

+ (void)load {

Class arrayMClass = NSClassFromString(@"__NSArrayM");
//获取系统的添加元素的方法
Method addObject = class_getInstanceMethod(arrayMClass, @selector(objectAtIndexedSubscript:));

//获取我们自定义添加元素的方法
Method avoidCrash = class_getInstanceMethod(arrayMClass, @selector(avoidCrashobjectAtIndexedSubscript:));

method_exchangeImplementations(addObject, avoidCrash);


}

- (id)avoidCrashobjectAtIndexedSubscript:(NSUInteger)idx {

@try {
return [self avoidCrashobjectAtIndexedSubscript:idx];
}
@catch (NSException *exception) {
//你可以在这里进行相应的操作处理
NSLog(@"这里数组越界");
NSLog(@"异常名称:%@   异常原因:%@",exception.name, exception.reason);
}
@finally {

}
}
 

@end
```

![NSException4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/NSException4.png)

我们可以根据`NSException`的特性写一些简单的防止崩溃的框架。





### NSError

每个程序都必须处理运行时发生的错误。例如，程序可能无法打开文件，或者可能无法解析XML文档。通常这些错误需要程序通知用户它们。 在程序中我们可以通过`NSError`把导致错误的原因回调给调用者

NSError对象里封装了三条信息：
- 1、**Error domain**：错误范围，其类型为字符串
 错误发生的范围，也就是产生错误的根源，通常用一个特有的全局变量来定义。比方说，“处理URL的子系统”在从URL中解析或者取得数据时如果出错了，那么就会使用NSURLErrorDomain来表示错误范围。
- 2、**Error code**：错误码，其类型为整数
独有的错误代码，用以指明在某个范围内具体发生了何种错误。某个特定的范围内可能会发生一系列相关错误，这些错误情况通常采用enum来定义。例如当http请求出错时，可能会把http状态码设为错误码。

- 3、**User info**：用户信息，其类型为字典
有关此错误的额外信息，其中或许包含一段“本地化的描述”，获取还含有导致该错误发生的另外一个错误，经由此种信息，可将相关错误串成一条“错误链”。

```
NSError *error = [NSError errorWithDomain:NSURLErrorDomain code:121 userInfo:@{NSLocalizedDescriptionKey:@"本地化的错误描述"}];
NSLog(@"error.userInfo:%@\nerror.code:%ld", error.userInfo,error.code);
```





[Error官网](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/ErrorHandling/ErrorHandling.html#//apple_ref/doc/uid/TP40001806)

[NSException官网](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Exceptions/Tasks/RaisingExceptions.html#//apple_ref/doc/uid/20000058-BBCCFIBF)

[NSException:错误处理机制---调试中以及上架后的产品如何收集错误日志](https://blog.csdn.net/lcl130/article/details/41891273)

[iOS被开发者遗忘在角落的NSException-其实它很强大](https://www.jianshu.com/p/05aad21e319e)
