## GCD介绍 

- 1、GCD简介
- 2、GCD任务和队列
- 3、GCD 的基本使用
- 4、GCD 线程间的通信
- 5、GCD 的其他方法（栅栏方法：dispatch_barrier_async、延时执行方法：dispatch_after、一次性代码（只执行一次）：dispatch_once、快速迭代方法：dispatch_apply、队列组：dispatch_group、信号量：dispatch_semaphore）
 

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

![GCD](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD.png)

`使用sync函数往当前串行队列中添加任务，会卡住当前的串行队列（产生死锁`

`并发功能只有在异步函数才会生效`


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

![GCD1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD1.png)

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
![GCD1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD1.png)

 
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
![GCD2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD2.png)

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

![GCD3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD3.png)

结果：`有开启新的线程，并发执行任务`。想要出现明显的并发执行效果，可以`sleep`一下




**sync函数造成的线程死锁**

首先你要理解同步和异步执行的概念，同步和异步目的不是为了是否创建一个新的线程，同步会阻塞当前函数的返回，异步函数会立即返回执行下面的代码；队列是一种数据结构，队列有FIFO,LIFO等，控制任务的执行顺序，至于是否开辟一个新的线程，因为同步函数会等待函数的返回，所以在当前线程执行就行了，没必要浪费资源再开辟新的线程，如果是异步函数，当前线程需要立即函数返回，然后往下执行，所以函数里面的任务必须要开辟一个新的线程去执行这个任务。

`队列上是放任务的,而线程是去执行队列上的任务的`


【问题1】：以下代码是在主线程执行的，会不会产生死锁？会！
```
NSLog(@"执行任务1");
dispatch_queue_t queue = dispatch_get_main_queue();
dispatch_sync(queue, ^{
	NSLog(@"执行任务2");
});

NSLog(@"执行任务3");
```
 

![GCD4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD4.png)

`dispatch_sync立马在当前线程同步执行任务`

分析：
- 1、主线程中任务执行：`任务1`、`sync`、`任务3`、
- 2、主队列：`viewDidLoad`、`任务2`、

其中在主队列`viewDidLoad`里面的`任务3`执行结束才会执行`任务2`；而主线程中是执行完`sync`才会执行`任务3`。也就是`任务2`等待`任务3`执行，`任务3`再也等待`任务2`执行，造成死锁

![GCD5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD5.png)


【问题2】：以下代码是在主线程执行的，会不会产生死锁？不会！
```
- (void)interview02
{
 
	NSLog(@"执行任务1");

	dispatch_queue_t queue = dispatch_get_main_queue();
	dispatch_async(queue, ^{
		NSLog(@"执行任务2");
	});

	NSLog(@"执行任务3");

	// dispatch_async不要求立马在当前线程同步执行任务
}
```

因为`dispatch_async`不要求立马在当前线程同步执行任务，不会造成线程死锁



【问题3】：以下代码是在主线程执行的，会不会产生死锁？会！

```
NSLog(@"执行任务1");

dispatch_queue_t queue = dispatch_queue_create("myqueu", DISPATCH_QUEUE_SERIAL);
dispatch_async(queue, ^{ // 0
	NSLog(@"执行任务2");

	dispatch_sync(queue, ^{ // 1
		NSLog(@"执行任务3");
	});

	NSLog(@"执行任务4");
});

NSLog(@"执行任务5");
```
![GCD6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD6.png)

其中`执行任务3`和`执行任务4`之间造成死锁

【问题4】：以下代码是在主线程执行的，会不会产生死锁？不会！
```
- (void)interview04
{
 
	NSLog(@"执行任务1");

	dispatch_queue_t queue = dispatch_queue_create("myqueu", DISPATCH_QUEUE_CONCURRENT);

	dispatch_async(queue, ^{ // 0
		NSLog(@"执行任务2");

		dispatch_sync(queue, ^{ // 1
			NSLog(@"执行任务3");
		});

		NSLog(@"执行任务4");
	});

	NSLog(@"执行任务5");
}
```

### 4、GCD 线程间的通信

在iOS开发过程中，我们一般在主线程里边进行UI刷新，例如：点击、滚动、拖拽等事件。我们通常把一些耗时的操作放在其他线程，比如说图片下载、文件上传等耗时操作。而当我们有时候在其他线程完成了耗时操作时，需要回到主线程，那么就用到了线程之间的通讯。
```
- (void)communication {
	// 获取全局并发队列
	dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0); 
	// 获取主队列
	dispatch_queue_t mainQueue = dispatch_get_main_queue(); 

	dispatch_async(queue, ^{
		// 异步追加任务
		for (int i = 0; i < 2; ++i) {
			[NSThread sleepForTimeInterval:2];              // 模拟耗时操作
			NSLog(@"1---%@",[NSThread currentThread]);      // 打印当前线程
		}

		// 回到主线程
		dispatch_async(mainQueue, ^{
			// 追加在主线程中执行的任务
			[NSThread sleepForTimeInterval:2];              // 模拟耗时操作
			NSLog(@"2---%@",[NSThread currentThread]);      // 打印当前线程
		});
	});
}
 
```


### 5、GCD 的其他方法


#### 5.1、GCD 栅栏方法：`dispatch_barrier_async`

![GCD7](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD7.png)


就是我们在异步执行一些操作的时候，我们使用`dispatch_barrier_async`函数把异步操作暂时性的做成同步操作，就行一个`栅栏`一样分开

```
- (void)viewDidLoad {
	[super viewDidLoad];

	self.queue = dispatch_queue_create("rw_queue", DISPATCH_QUEUE_CONCURRENT);

	for (int i = 0; i < 10; i++) {
		[self read];
		[self read];
		[self read];
		[self write];
	}
}


- (void)read {
	dispatch_async(self.queue, ^{
		sleep(1);
		NSLog(@"read");
	});
}

- (void)write
{
	dispatch_barrier_async(self.queue, ^{
		sleep(1);
		NSLog(@"write");
	});
}

```
![GCD8](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/GCD8.png)
我们观察时间可以看到在执行`dispatch_barrier_async`写操作的时候是同步执行的，不会出现异步情况

#### 5.2、GCD 延时执行方法：dispatch_after

我们经常会遇到这样的需求：在指定时间（例如3秒）之后执行某个任务。可以用 GCD 的dispatch_after函数来实现。
需要注意的是：dispatch_after函数并不是在指定时间之后才开始执行处理，而是在指定时间之后将任务追加到主队列中。严格来说，这个时间并不是绝对准确的，但想要大致延迟执行任务，dispatch_after函数是很有效的。

 ```
 /**
 * 延时执行方法 dispatch_after
 */
 - (void)after {
	 NSLog(@"currentThread---%@",[NSThread currentThread]);  // 打印当前线程
	 NSLog(@"asyncMain---begin");
	 
	 dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
		 // 2.0秒后异步追加任务代码到主队列，并开始执行
		 NSLog(@"after---%@",[NSThread currentThread]);  // 打印当前线程
	 });
 }
 
 
 ```

#### 5.3、GCD 一次性代码（只执行一次）：dispatch_once

我们在创建单例、或者有整个程序运行过程中只执行一次的代码时，我们就用到了 GCD 的 dispatch_once 函数
```
static dispatch_once_t onceToken;
dispatch_once(&onceToken, ^{
// 只执行1次的代码(这里面默认是线程安全的)
});
```

#### 5.4、GCD 队列组：dispatch_group

有时候我们会有这样的需求：分别异步执行2个耗时任务，然后当2个耗时任务都执行完毕后再回到主线程执行任务。这时候我们可以用到 GCD 的队列组

- 调用队列组的 `dispatch_group_async` 先把任务放到队列中，然后将队列放入队列组中。或者使用队列组的 `dispatch_group_enter`、`dispatch_group_leave` 组合 来实现`dispatch_group_async`。
- 调用队列组的 `dispatch_group_notify `回到指定线程执行任务。或者使用 `dispatch_group_wait` 回到当前线程继续向下执行（会阻塞当前线程）。
- `dispatch_group_enter `标志着一个任务追加到 group，执行一次，相当于 group 中未执行完毕任务数+1
- `dispatch_group_leave` 标志着一个任务离开了 group，执行一次，相当于 group 中未执行完毕任务数-1
- 当 group 中未执行完毕任务数为0的时候，才会使`dispatch_group_wait`解除阻塞，以及执行追加到`dispatch_group_notify`中的任务。

```
/**
* 队列组 dispatch_group_notify
*/
- (void)groupNotify {
	NSLog(@"currentThread---%@",[NSThread currentThread]);  // 打印当前线程
	NSLog(@"group---begin");

	dispatch_group_t group =  dispatch_group_create();

	dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
		// 追加任务1
		for (int i = 0; i < 2; ++i) {
			[NSThread sleepForTimeInterval:2];              // 模拟耗时操作
			NSLog(@"1---%@",[NSThread currentThread]);      // 打印当前线程
		}
	});

	dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
		// 追加任务2
		for (int i = 0; i < 2; ++i) {
			[NSThread sleepForTimeInterval:2];              // 模拟耗时操作
			NSLog(@"2---%@",[NSThread currentThread]);      // 打印当前线程
		}
	});

	dispatch_group_notify(group, dispatch_get_main_queue(), ^{
		// 等前面的异步任务1、任务2都执行完毕后，回到主线程执行下边任务
		for (int i = 0; i < 2; ++i) {
			[NSThread sleepForTimeInterval:2];              // 模拟耗时操作
			NSLog(@"3---%@",[NSThread currentThread]);      // 打印当前线程
		}
		NSLog(@"group---end");
	});
}

```



#### 5.5、GCD 信号量：dispatch_semaphore

Dispatch Semaphore 提供了三个函数。

- `dispatch_semaphore_create`：创建一个信号量，具有整形的数值，即为信号的总量。
- `dispatch_semaphore_signal`：发送一个信号，让信号总量加1
- `dispatch_semaphore_wait`：可以使总信号量减1，当信号总量为0时就会一直等待（阻塞所在线程），否则就可以正常执行。

 

























