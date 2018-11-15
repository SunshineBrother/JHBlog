## NSException抛出异常&NSError简单介绍


### NSException的简单介绍

 这个类是专门表示异常的，Cocoa框架要求所有的异常都是它或者是它子类的实例，当实例调用raise或者throw方法时就会出现我们如上图之类的崩溃，并给出它的一些相关信息。下面介绍NSException对象的几个重要的属性。

- name :  用于唯一地识别异常的短字符串。名称是必需的
- reason:一个更长的包含造成异常原因的“人类可读的”字符串。原因是必需的。
- userInfo：主要当异常被抛出时，返回原因等信息的一个字典。

**异常处理**



















[Error官网](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/ErrorHandling/ErrorHandling.html#//apple_ref/doc/uid/TP40001806)
[NSException官网](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Exceptions/Tasks/RaisingExceptions.html#//apple_ref/doc/uid/20000058-BBCCFIBF)
[NSException:错误处理机制---调试中以及上架后的产品如何收集错误日志](https://blog.csdn.net/lcl130/article/details/41891273)
[iOS被开发者遗忘在角落的NSException-其实它很强大](https://www.jianshu.com/p/05aad21e319e)
