## GCD介绍 

- 1、GCD简介
- 2、GCD任务和队列
- 3、GCD 的基本使用
- 4、GCD 线程间的通信
- 5、GCD 的其他方法（栅栏方法：dispatch_barrier_async、延时执行方法：dispatch_after、一次性代码（只执行一次）：dispatch_once、快速迭代方法：dispatch_apply、队列组：dispatch_group、信号量：dispatch_semaphore）
- 6、线程死锁

>对于GCD的基本介绍，[这篇文章](https://www.jianshu.com/p/2d57c72016c6)讲的那是已经十分详细了，我这里复制过来加深一下我的印象；在对前辈总结基础之上我这篇文章有讨论了一下线程死锁的问题。


### 1、GCD简介
 
 > Grand Central Dispatch(GCD) 是 Apple 开发的一个多核编程的较新的解决方法。它主要用于优化应用程序以支持多核处理器以及其他对称多处理系统。它是一个在线程池模式的基础上执行的并发任务。在 Mac OS X 10.6 雪豹中首次推出，也可在 iOS 4 及以上版本使用。
 
GCD 的好处具体如下

- GCD 可用于多核的并行运算
- GCD 会自动利用更多的 CPU 内核（比如双核、四核）
- GCD 会自动管理线程的生命周期（创建线程、调度任务、销毁线程）
- 程序员只需要告诉 GCD 想要执行什么任务，不需要编写任何线程管理代码


### 2、GCD任务和队列

GCD 中两个核心概念：任务和队列

#### 任务
**任务**：就是执行操作的意思，换句话说就是你在线程中执行的那段代码。在 GCD 中是放在 block 中的

- **同步执行（sync）**
    - 同步添加任务到指定的队列中，在添加的任务执行结束之前，会一直等待，直到队列里面的任务完成之后再继续执行。
    - 只能在当前线程中执行任务，`不具备`开启新线程的能力
    
- **异步执行（async）**
    - 异步添加任务到指定的队列中，它不会做任何等待，可以继续执行任务。
    - 可以在新的线程中执行任务，`具备`开启新线程的能力。


```
// 同步执行任务创建方法
dispatch_sync(queue, ^{
// 这里放同步执行任务代码
});
// 异步执行任务创建方法
dispatch_async(queue, ^{
// 这里放异步执行任务代码
});
```

#### 队列

**队列（Dispatch Queue）**：这里的队列指执行任务的等待队列，即用来存放任务的队列。队列是一种特殊的线性表，采用 FIFO（先进先出）的原则，即新任务总是被插入到队列的末尾，而读取任务的时候总是从队列的头部开始读取。每读取一个任务，则从队列中释放一个任务

- **串行队列（Serial Dispatch Queue）**
    - 每次只有一个任务被执行。让任务一个接着一个地执行。（只开启一个线程，一个任务执行完毕后，再执行下一个任务）
    
- **并发队列（Concurrent Dispatch Queue）**
    - 可以让多个任务并发（同时）执行。（可以开启多个线程，并且同时执行任务）


`并发队列的并发功能只有在异步（dispatch_async）函数下才有效`


**队列的创建方法/获取方法**

可以使用`dispatch_queue_create`来创建队列，需要传入两个参数，第一个参数表示队列的唯一标识符，用于 DEBUG，可为空，Dispatch Queue 的名称推荐使用应用程序 ID 这种逆序全程域名；第二个参数用来识别是串行队列还是并发队列。`DISPATCH_QUEUE_SERIAL` 表示串行队列，`DISPATCH_QUEUE_CONCURRENT`表示并发队列。

 ```
 // 串行队列的创建方法
 dispatch_queue_t queue = dispatch_queue_create("net.bujige.testQueue", DISPATCH_QUEUE_SERIAL);
 // 并发队列的创建方法
 dispatch_queue_t queue = dispatch_queue_create("net.bujige.testQueue", DISPATCH_QUEUE_CONCURRENT);
 
 ```

**对于串行队列，GCD 提供了的一种特殊的串行队列：主队列（Main Dispatch Queue）**

- 所有放在主队列中的任务，都会放到主线程中执行
- 可使用dispatch_get_main_queue()获得主队列。

```
// 主队列的获取方法
dispatch_queue_t queue = dispatch_get_main_queue();
```

**对于并发队列，GCD 默认提供了全局并发队列（Global Dispatch Queue）**

可以使用`dispatch_get_global_queue`来获取。需要传入两个参数。第一个参数表示队列优先级，一般用`DISPATCH_QUEUE_PRIORITY_DEFAULT`。第二个参数暂时没用，用0即可。

```
// 全局并发队列的获取方法
dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
```

![GCD](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/多线程/GCD.png)

`使用sync函数往当前串行队列中添加任务，会卡住当前的串行队列（产生死锁`



### 3、GCD 的基本使用

**同步串行队列**

```
dispatch_queue_t queue = dispatch_queue_create("test", DISPATCH_QUEUE_SERIAL);
dispatch_sync(queue, ^{
// 追加任务1
for (int i = 0; i < 2; ++i) {
NSLog(@"1---%@",[NSThread currentThread]);
}
});

dispatch_sync(queue, ^{
// 追加任务2
for (int i = 0; i < 2; ++i) {
NSLog(@"2---%@",[NSThread currentThread]);
}
});
```

![GCD1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/多线程/GCD1.png)

根据打印结果可知，`同步串行队列即没有开启新的线程，也没有异步执行`
 

**同步并行队列**

```
dispatch_queue_t queue = dispatch_queue_create("test", DISPATCH_QUEUE_CONCURRENT);
dispatch_sync(queue, ^{
// 追加任务1
for (int i = 0; i < 2; ++i) {
NSLog(@"1---%@",[NSThread currentThread]);
}
});

dispatch_sync(queue, ^{
// 追加任务2
for (int i = 0; i < 2; ++i) {
NSLog(@"2---%@",[NSThread currentThread]);
}
});
```
![GCD1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/多线程/GCD1.png)

 
根据两种打印我们发现：`同步函数`既不会开启新的线程，也不会执行并发任务


**异步串行队列**

```
NSLog(@"主线程：%@",[NSThread currentThread]);
dispatch_queue_t queue = dispatch_queue_create("test", DISPATCH_QUEUE_CONCURRENT);
dispatch_async(queue, ^{
for (int i = 0; i < 2; ++i) {
NSLog(@"1====%@",[NSThread currentThread]);      // 打印当前线程
}

});
dispatch_async(queue, ^{
for (int i = 0; i < 2; ++i) {
NSLog(@"2====%@",[NSThread currentThread]);      // 打印当前线程
}

});
```
![GCD2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/多线程/GCD2.png)

结果：`有开启新的线程，串行执行任务`

**异步并行队列**

```
NSLog(@"主线程：%@",[NSThread currentThread]);
dispatch_queue_t queue = dispatch_queue_create("test", DISPATCH_QUEUE_CONCURRENT);
dispatch_async(queue, ^{
for (int i = 0; i < 2; ++i) {
[NSThread sleepForTimeInterval:2];
NSLog(@"1====%@",[NSThread currentThread]);      // 打印当前线程
}

});
dispatch_async(queue, ^{
for (int i = 0; i < 2; ++i) {
[NSThread sleepForTimeInterval:2];
NSLog(@"2====%@",[NSThread currentThread]);      // 打印当前线程
}

});
```

![GCD3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/多线程/GCD3.png)

结果：`有开启新的线程，并发执行任务`。想要出现明显的并发执行效果，可以`sleep`一下
































