## NSOperation介绍 

NSOperation、NSOperationQueue 是苹果提供给我们的一套多线程解决方案。实际上 NSOperation、NSOperationQueue 是基于 GCD 更高一层的封装，完全面向对象

好处
- 1、可添加完成的代码块，在操作完成后执行
- 2、添加操作之间的依赖关系，方便的控制执行顺序
- 3、设定操作执行的优先级
- 4、可以很方便的取消一个操作的执行
- 5、使用 KVO 观察对操作执行状态的更改：isExecuteing、isFinished、isCancelled


既然是基于 GCD 的更高一层的封装。那么，GCD 中的一些概念同样适用于 NSOperation、NSOperationQueue。在 NSOperation、NSOperationQueue 中也有类似的任务（操作）和队列（操作队列）的概念

**操作（Operation）**
- 1、执行操作的意思，换句话说就是你在线程中执行的那段代码
- 2、在 `GCD `中是放在 `block` 中的。在 `NSOperation` 中，我们使用 NSOperation 子类 `NSInvocationOperation`、`NSBlockOperation`，或者自定义子类来封装操作

**操作队列（Operation Queues）**
- 1、这里的队列指操作队列，即用来存放操作的队列。不同于 GCD 中的调度队列 FIFO（先进先出）的原则。NSOperationQueue 对于添加到队列中的操作，首先进入准备就绪的状态（就绪状态取决于操作之间的依赖关系），然后进入就绪状态的操作的开始执行顺序（非结束执行顺序）由操作之间相对的优先级决定（优先级是操作对象自身的属性）。
- 2、操作队列通过设置最大并发操作数（maxConcurrentOperationCount）来控制并发、串行
- 3、NSOperationQueue 为我们提供了两种不同类型的队列：主队列和自定义队列。主队列运行在主线程之上，而自定义队列在后台执行


### 常用API

**NSOperation常用属性和方法**
- 1、开始取消操作
    - `- (void)start`：对于并发Operation需要重写该方法，也可以不把operation加入到队列中，手动触发执行，与调用普通方法一样
    - `- (void)main`：非并发Operation需要重写该方法
    - `- (void)cancel`：可取消操作，实质是标记 isCancelled 状态
- 2、判断操作状态方法
    - `- (BOOL)isFinished;` 判断操作是否已经结束
    - `- (BOOL)isCancelled` 判断操作是否已经标记为取消
    - `- (BOOL)isExecuting;`判断操作是否正在在运行
    - `- (BOOL)isReady;`判断操作是否处于准备就绪状态，这个值和操作的依赖关系相关。

- 3、操作同步
    - `- (void)waitUntilFinished;`阻塞当前线程，直到该操作结束。可用于线程执行顺序的同步
    - `- (void)setCompletionBlock:(void (^)(void))block;`  会在当前操作执行完毕时执行 completionBlock 
    - `- (void)addDependency:(NSOperation *)op;` 添加依赖，使当前操作依赖于操作 op 的完成
    - `- (void)removeDependency:(NSOperation *)op;` 移除依赖，取消当前操作对操作 op 的依赖。
    - `@property (readonly, copy) NSArray<NSOperation *> *dependencies;` 在当前操作开始执行之前完成执行的所有操作对象数组。


**NSOperationQueue 常用属性和方法**

- 1、取消/暂停/恢复操作
    - `- (void)cancelAllOperations;` 可以取消队列的所有操作
    - `- (BOOL)isSuspended;` 判断队列是否处于暂停状态。 YES 为暂停状态，NO 为恢复状态
    - `- (void)setSuspended:(BOOL)b;` 可设置操作的暂停和恢复，YES 代表暂停队列，NO 代表恢复队列

- 2、操作同步
    - `- (void)waitUntilAllOperationsAreFinished;` 阻塞当前线程，直到队列中的操作全部执行完毕。
- 3、添加/获取操作
    - `- (void)addOperationWithBlock:(void (^)(void))block;` 向队列中添加一个 NSBlockOperation 类型操作对象
    - `- (void)addOperations:(NSArray *)ops waitUntilFinished:(BOOL)wait;`向队列中添加操作数组，wait 标志是否阻塞当前线程直到所有操作结束
    - `- (NSArray *)operations;` 当前在队列中的操作数组（某个操作执行结束后会自动从这个数组清除）
    - `- (NSUInteger)operationCount;` 当前队列中的操作数
- 4、获取队列
    -   `+ (id)currentQueue;` 获取当前队列，如果当前线程不是在 NSOperationQueue 上运行则返回 nil。
    - `+ (id)mainQueue;`  获取主队列。



### 简单使用

NSOperation 需要配合 NSOperationQueue 来实现多线程。因为默认情况下，NSOperation 单独使用时系统同步执行操作，配合 NSOperationQueue 我们能更好的实现异步执行

实现步骤
- 1、创建操作：先将需要执行的操作封装到一个 NSOperation 对象中
- 2、创建队列：创建 NSOperationQueue 对象
- 3、将操作加入到队列中：将 NSOperation 对象添加到 NSOperationQueue 对象中


NSOperation 是个抽象类，不能用来封装操作。我们只有使用它的子类来封装操作
- 1、使用子类 NSInvocationOperation
- 2、使用子类 NSBlockOperation
- 3、自定义继承自 NSOperation 的子类，通过实现内部相应的方法来封装操作。

#### 使用子类 `NSInvocationOperation`

在主线程中操作
```
- (void)Operation1{
    //1、创建NSInvocationOperation对象
    NSInvocationOperation *op = [[NSInvocationOperation alloc]initWithTarget:self selector:@selector(test) object:nil];
    //2、开始调用
    [op start];
}


- (void)test{
    for (NSInteger i = 0; i < 2; i++) {
        NSLog(@"当前线程:%@",[NSThread currentThread]);
    }
}
```

![NSOperation1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSOperation1.png)



如果在其他线程中操作
```
NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(Operation1) object:@"Hello, World"];
//设置线程的名字，方便查看
[thread setName:@"firstThread"];
//启动线程
[thread start];
```
![NSOperation2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSOperation2.png)


**总结**：在没有使用 `NSOperationQueue`、在主线程中单独使用使用子类 `NSInvocationOperation` 执行一个操作的情况下，操作是在当前线程执行的，并`没有开启新线程`。



#### 使用子类 `NSBlockOperation`

在主线程中
```
- (void)Operation2{
    //1、使用NSBlockOperation
    NSBlockOperation *op = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"当前线程:%@",[NSThread currentThread]);
    }];
    //2、开始调用
    [op start];
}
```

![NSOperation3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSOperation3.png)


```
NSThread *thread = [[NSThread alloc] initWithTarget:self selector:@selector(Operation2) object:@"Hello, World"];
//设置线程的名字，方便查看
[thread setName:@"firstThread"];
//启动线程
[thread start];
```
![NSOperation4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSOperation4.png)


**总结**：在没有使用 `NSOperationQueue`、在主线程中单独使用使用子类 `NSBlockOperation` 执行一个操作的情况下，操作是在当前线程执行的，并`没有开启新线程`。


**addExecutionBlock**

`NSBlockOperation` 还提供了一个方法 `addExecutionBlock:`，通过 `addExecutionBlock:` 就可以为 `NSBlockOperation` 添加额外的操作。这些操作（包括 blockOperationWithBlock 中的操作）可以在不同的线程中同时`（并发）`执行。只有当所有相关的操作已经完成执行时，才视为完成。每添加一个`addExecutionBlock:`就是开启一个异步并发执行事件
```
//1、使用NSBlockOperation
NSBlockOperation *op = [NSBlockOperation blockOperationWithBlock:^{
    NSLog(@"当前线程:%@",[NSThread currentThread]);
}];
[op addExecutionBlock:^{
    for (int i = 0; i < 2; i++) {
        NSLog(@"当前线程2：%@", [NSThread currentThread]); // 打印当前线程
    }
}];
[op addExecutionBlock:^{
    for (int i = 0; i < 2; i++) {
        NSLog(@"当前线程3：%@", [NSThread currentThread]); // 打印当前线程
    }
}];
[op addExecutionBlock:^{
    for (int i = 0; i < 2; i++) {
        NSLog(@"当前线程4：%@", [NSThread currentThread]); // 打印当前线程
    }
}];


//2、开始调用
[op start];
```


![NSOperation5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSOperation5.png)

#### 自定义继承自 NSOperation 的子类

如果使用子类` NSInvocationOperation`、`NSBlockOperation `不能满足日常需求，我们可以使用自定义继承自 NSOperation 的子类。可以通过重写 `main `或者 `start `方法 来定义自己的 `NSOperation 对象`。重写`main`方法比较简单，我们不需要管理操作的状态属性` isExecuting` 和 `isFinished`。当 main 执行完返回的时候，这个操作就结束了
 
```
@interface JHOperation : NSOperation

@end
#import "JHOperation.h"

@implementation JHOperation
- (void)main {
    if (!self.isCancelled) {
        for (int i = 0; i < 2; i++) {

             NSLog(@"当前线程：%@", [NSThread currentThread]);
        }
    }
}

@end
```
调用
```
- (void)Operation3{
    // 1.创建 JHOperation 对象
    JHOperation *op = [[JHOperation alloc] init];
    // 2.调用 start 方法开始执行操作
    [op start];
}
```



### `NSOperationQueue` 创建队列

 NSOperationQueue 一共有两种队列：主队列、自定义队列。其中自定义队列同时包含了串行、并发功能

**主队列**
凡是添加到主队列中的操作，都会放到主线程中执行（注：不包括操作使用addExecutionBlock:添加的额外操作)
```
// 主队列获取方法
NSOperationQueue *queue = [NSOperationQueue mainQueue];
```
**自定义队列**
添加到这种队列中的操作，就会自动放到子线程中执行。同时包含了：串行、并发功能。
```
// 自定义队列创建方法
NSOperationQueue *queue = [[NSOperationQueue alloc] init];
```

#### 将操作加入到队列中

NSOperation 需要配合 NSOperationQueue 来实现多线程，总共有两种方法：
- 1、`- (void)addOperation:(NSOperation *)op;` 需要先创建操作，再将创建好的操作加入到创建好的队列中去
- 2、`- (void)addOperationWithBlock:(void (^)(void))block;` 无需先创建操作，在 block 中添加操作，直接将包含操作的 block 加入到队列中。

**addOperation**

```
- (void)Operation4{
    //1、创建队列
    NSOperationQueue *queue = [[NSOperationQueue alloc]init];

    //2、创建操作
    NSBlockOperation *op1 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"当前线程1:%@",[NSThread currentThread]);
    }];
    NSBlockOperation *op2 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"当前线程2:%@",[NSThread currentThread]);
    }];
    NSBlockOperation *op3 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"当前线程3:%@",[NSThread currentThread]);
    }];

    //3、添加操作
    [queue addOperation:op1];
    [queue addOperation:op2];
    [queue addOperation:op3];
}
```

![NSOperation6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSOperation6.png)


**addOperationWithBlock**

无需先创建操作，在 block 中添加操作，直接将包含操作的 block 加入到队列中。

```
- (void)Operation5{
    NSOperationQueue *queue = [[NSOperationQueue alloc]init];
    [queue addOperationWithBlock:^{
        NSLog(@"当前线程1:%@",[NSThread currentThread]);
    }];
    [queue addOperationWithBlock:^{
        NSLog(@"当前线程2:%@",[NSThread currentThread]);
    }];
    [queue addOperationWithBlock:^{
        NSLog(@"当前线程3:%@",[NSThread currentThread]);
    }];
}

```
#### 最大并发操作数量 `maxConcurrentOperationCount`

`maxConcurrentOperationCount`最大并发操作数量
- maxConcurrentOperationCount 默认情况下为-1，表示不进行限制，可进行并发执行。
- maxConcurrentOperationCount 为1时，队列为串行队列。只能串行执行。
- maxConcurrentOperationCount 大于1时，队列为并发队列。操作并发执行，当然这个值不应超过系统限制，即使自己设置一个很大的值，系统也会自动调整为 min{自己设定的值，系统设定的默认最大值}

 ```
 NSOperationQueue *queue = [[NSOperationQueue alloc]init];
 queue.maxConcurrentOperationCount = 1; // 串行队列
 queue.maxConcurrentOperationCount = 2; // 并发队列，一次只能执行两个并发队列
 [queue addOperationWithBlock:^{
    NSLog(@"当前线程1:%@",[NSThread currentThread]);
 }];
 [queue addOperationWithBlock:^{
    NSLog(@"当前线程2:%@",[NSThread currentThread]);
 }];
 [queue addOperationWithBlock:^{
    NSLog(@"当前线程3:%@",[NSThread currentThread]);
 }];
 ```
 
 ####  NSOperation 操作依赖
 
NSOperation、NSOperationQueue 最吸引人的地方是它能添加操作之间的依赖关系。通过操作依赖，我们可以很方便的控制操作之间的执行先后顺序

- `- (void)addDependency:(NSOperation *)op; `添加依赖，使当前操作依赖于操作 op 的完成。
- `- (void)removeDependency:(NSOperation *)op; `移除依赖，取消当前操作对操作 op 的依赖。
- `@property (readonly, copy) NSArray<NSOperation *> *dependencies;` 在当前操作开始执行之前完成执行的所有操作对象数组

 
```
- (void)Operation6{
    NSOperationQueue *queue = [[NSOperationQueue alloc]init];
    //2、创建操作
    NSBlockOperation *op1 = [NSBlockOperation blockOperationWithBlock:^{
    [NSThread sleepForTimeInterval:1];
        NSLog(@"当前线程1:%@",[NSThread currentThread]);
    }];
    NSBlockOperation *op2 = [NSBlockOperation blockOperationWithBlock:^{
        [NSThread sleepForTimeInterval:2];
        NSLog(@"当前线程2:%@",[NSThread currentThread]);
    }];
    NSBlockOperation *op3 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"当前线程3:%@",[NSThread currentThread]);
    }];


    //3、添加依赖
    [op3 addDependency:op1];
    [op3 addDependency:op2];
    //4、添加操作
    [queue addOperation:op1];
    [queue addOperation:op2];
    [queue addOperation:op3];

}
```
上面`op3`依赖`op1&op2`执行完成才能执行


![NSOperation7](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/多线程/NSOperation7.png)



#### NSOperation 优先级

NSOperation 提供了`queuePriority（优先级）`属性，`queuePriority`属性适用于同一操作队列中的操作，不适用于不同操作队列中的操作。默认情况下，所有新创建的操作对象优先级都是`NSOperationQueuePriorityNormal`。但是我们可以通过`setQueuePriority:`方法来改变当前操作在同一队列中的执行优先级
 
```
// 优先级的取值
typedef NS_ENUM(NSInteger, NSOperationQueuePriority) {
NSOperationQueuePriorityVeryLow = -8L,
NSOperationQueuePriorityLow = -4L,
NSOperationQueuePriorityNormal = 0,
NSOperationQueuePriorityHigh = 4,
NSOperationQueuePriorityVeryHigh = 8
};

 
```


对于添加到队列中的操作，首先进入准备就绪的状态（`就绪状态取决于操作之间的依赖关系`），然后进入就绪状态的操作的开始执行顺序由操作之间相对的优先级决定（优先级是操作对象自身的属性）


说明：优先级高的任务，调用的几率会更大。



[参考：iOS 多线程：『NSOperation、NSOperationQueue』详尽总结](https://www.jianshu.com/p/4b1d77054b35)





















