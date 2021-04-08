 ## NSThread介绍

NSThread 是苹果官方提供的，使用起来比 pthread 更加面向对象，简单易用，可以直接操作线程对象。不过也需要需要程序员自己管理线程的生命周期(主要是创建)，我们在开发的过程中偶尔使用 NSThread。比如我们会经常调用[NSThread currentThread]来显示当前的进程信息

#### NSThread的创建与运行
 
 ```
 //使用target对象的selector作为线程的任务执行体，该selector方法最多可以接收一个参数，该参数即为argument
- (instancetype)initWithTarget:(id)target selector:(SEL)selector object:(nullable id)argument
 
 //使用block作为线程的任务执行体
 - (instancetype)initWithBlock:(void (^)(void))block
 
 
 /*
 类方法，返回值为void
 使用一个block作为线程的执行体，并直接启动线程
 上面的实例方法返回NSThread对象需要手动调用start方法来启动线程执行任务
 */
 + (void)detachNewThreadWithBlock:(void (^)(void))block
 
 
 /*
 类方法，返回值为void
 使用target对象的selector作为线程的任务执行体，该selector方法最多接收一个参数，该参数即为argument
 同样的，该方法创建完县城后会自动启动线程不需要手动触发
 */
 + (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(nullable id)argument
 ```
简单运用

```
- (void)viewDidLoad {
	[super viewDidLoad];


	NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(firstThread:) object:@"Hello, World"];
	//设置线程的名字，方便查看
	[thread setName:@"firstThread"];
	//启动线程
	[thread start];

}


//线程的任务执行体并接收一个参数arg
- (void)firstThread:(id)arg
{
	NSLog(@"Task %@ %@", [NSThread currentThread], arg);
	NSLog(@"Thread Task Complete");
}
```

![NSThread1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSThread1.png)


#### 常见API
```
// 获得主线程
+ (NSThread *)mainThread;    

// 判断是否为主线程(对象方法)
- (BOOL)isMainThread;

// 判断是否为主线程(类方法)
+ (BOOL)isMainThread;    

// 获得当前线程
NSThread *current = [NSThread currentThread];

// 线程的名字——setter方法
- (void)setName:(NSString *)n;    

// 线程的名字——getter方法
- (NSString *)name;

```


#### 线程状态控制方法

```
// 线程进入就绪状态 -> 运行状态。当线程任务执行完毕，自动进入死亡状态
- (void)start;

// 线程进入阻塞状态
+ (void)sleepUntilDate:(NSDate *)date;
+ (void)sleepForTimeInterval:(NSTimeInterval)ti;

//强制停止线程  线程进入死亡状态
+ (void)exit;
```

#### 线程之间的通信

在开发中，我们经常会在子线程进行耗时操作，操作结束后再回到主线程去刷新 UI。这就涉及到了子线程和主线程之间的通信。我们先来了解一下官方关于 NSThread 的线程间通信的方法。

```
// 在主线程上执行操作
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait;
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait modes:(NSArray<NSString *> *)array;
// equivalent to the first method with kCFRunLoopCommonModes

// 在指定线程上执行操作
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(id)arg waitUntilDone:(BOOL)wait modes:(NSArray *)array NS_AVAILABLE(10_5, 2_0);
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(id)arg waitUntilDone:(BOOL)wait NS_AVAILABLE(10_5, 2_0);

// 在当前线程上执行操作，调用 NSObject 的 performSelector:相关方法
- (id)performSelector:(SEL)aSelector;
- (id)performSelector:(SEL)aSelector withObject:(id)object;
- (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;

```


### 线程的状态转换

当我们新建一条线程NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(run) object:nil];，在内存中的表现为：

 ![NSThread2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSThread2.png)

当调用[thread start];后，系统把线程对象放入可调度线程池中，线程对象进入就绪状态，如下图所示。


 ![NSThread3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSThread3.png)

- 如果CPU现在调度当前线程对象，则当前线程对象进入运行状态，如果CPU调度其他线程对象，则当前线程对象回到就绪状态。
- 如果CPU在运行当前线程对象的时候调用了sleep方法\等待同步锁，则当前线程对象就进入了阻塞状态，等到sleep到时\得到同步锁，则回到就绪状态。
- 如果CPU在运行当前线程对象的时候线程任务执行完毕\异常强制退出，则当前线程对象进入死亡状态。

 


































