## LLDB

LLDB 是一个有着 REPL 的特性和 C++ ,Python 插件的开源调试器。LLDB 绑定在 Xcode 内部，存在于主窗口底部的控制台中。调试器允许你在程序运行的特定时暂停它，你可以查看变量的值，执行自定的指令，并且按照你所认为合适的步骤来操作程序的进展



### expression
可简写为e，作用为执行一个表达式
- 1、查询当前堆栈变量的值
- 2、动态修改当前线程堆栈变量的值

![LLDB1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB1.png)

我们在调试数据的时候，有的时候需要动态修改变量值，使用`expression`那是十分方便的调试

#### `po` & `p`

`po`的作用为打印对象，事实上，我们可以通过`help po`得知，`po`是`expression -O --`的简写，我们可以通过它打印出对象，而不是打印对象的指针。而值得一提的是，在 `help expression` 返回的帮助信息中，我们可以知道，`po`命令会尝试调用对象的 `description` 方法来取得对象信息，因此我们也可以重载某个对象的`description方法`，使我们调试的时候能获得可读性更强，更全面的信息
![LLDB2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB2.png)
 
`p`即是`print`，也是`expression --`的缩写，与`po`不同，它不会打出对象的详细信息，只会打印出一个$符号，数字，再加上一段地址信息。打印对象的时候我们也可以指定特定格式
- `x` ：十六进制打印
- `d`:十进制打印
- `u`:无符号十进制打印
- `o`:八进制打印
- `t`:二进制形式打印
- `f`:浮点数

![LLDB3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB3.png)


### 堆栈

`bt`即是`thread backtrace`，作用是打印出当前线程的堆栈信息。
![LLDB4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB4.png)

我们在打印断点的时候，我们可以在左侧看到一些堆栈信息，但是看不完全，这个时候使用`bt`指令可以打印出完整的堆栈信息


输入`frame select`指令我们可以任意的去选择一个作用域去查看
```
(lldb)frame select 2
```

`thread`另一个比较常用的用法是 `thread return`，调试的时候，我们希望在当前执行的程序堆栈直接返回一个自己想要的值，可以执行该命令直接返回。
`thread return <expr>`
在这个断点中，我们可以执行 `thread return NO`让该函数调用直接返回`NO `，在调试中轻松覆盖任何函数的返回路径。

 ![LLDB5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB5.png)

`frame`即是帧，其实就是当前的程序堆栈，我们输入`bt`命令，打印出来的其实是当前线程的`frame`。
 - 展示当前作用域下的参数和局部变量
 ```
 (lldb)frame variable
 (lldb)fr v
 frame variable --no-summary-depth
 ```
- 展示当前作用域下的局部变量
```
(lldb)frame variable --no-args
(lldb)fr v -a
```
- 展示指定变量var的具体内容
```
(lldb)frame variable var
(lldb)fr v var
(lldb)p var
(lldb)po var
```
- 展示当前对象的全局变量
```
(lldb)target variable
(lldb)ta v
```
- 打印某一方法具体的信息
```
frame select num（1，2，3.）
```
 ![LLDB7](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB7.png)
 
  ![LLDB6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB6.png)



### 设置断点
#### breakpoint

所有调试都是由断点开始的，我们接触的最多，就是以breakpoint命令为基础的断点。
一般我们对breakpoint命令使用得不多，而是在XCode的GUI界面中直接添加断点。除了直接触发程序暂停供调试外，我们可以进行进一步的配置。

![LLDB8](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/LLDB8.png)

- 添加condition，一般用于多次调用的函数或者循坏的代码中，在作用域内达到某个条件，才会触发程序暂停
- 忽略次数，这个很容易理解，在忽略触发几次后再触发暂停
- 添加Action，为这个断点添加子命令、脚本、shell命令、声效（有个毛线用）等Action，我的理解是一个脚本化的功能，我们可以在断点的基础上添加一些方便调试的脚本，提高调试效率。
- 自动继续，配合上面的添加Action，我们就可以不用一次又一次的暂停程序进行调试来查询某些值（大型程序中断一次还是会有卡顿），直接用Action将需要的信息打印在控制台，一次性查看即可。


#### watchpoint

有时候我们会关心类的某个属性什么时候被人修改了，最简单的方法当然就是在setter的方法打断点，或者在`@property`的属性生命行打上断点。这样当对象的setter方法被调用时，就会触发这个断点
当然这么做是有缺点的，对于直接访问内存地址的修改，setter方法的断点并没有办法监控得到，因此我们需要用到`watchpoint`命令。

```
watchpoint set variable str
watchpoint list //列出所有watchpoint
watchpoint delete // 删除所有watchpoint
```


*参考*

[iOS调试-LLDB学习总结](https://www.jianshu.com/p/d6a0a5e39b0e)

[iOS开发调试 - LLDB使用概览](https://www.jianshu.com/p/67f08a4d8cf2)

[LLDB 常用命令](https://blog.csdn.net/u011374318/article/details/79648178)








