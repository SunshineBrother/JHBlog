## Schedulers - 调度器 
 
  ![Schedulers](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/Schedulers.png)
 
 Schedulers 是 Rx 实现多线程的核心模块，它主要用于控制任务在哪个线程或队列运行。
 
 
 - CurrentThreadScheduler：表示当前线程 Scheduler。（默认使用这个）
 - MainScheduler：表示主线程。如果我们需要执行一些和 UI 相关的任务，就需要切换到该 Scheduler 运行。
 - SerialDispatchQueueScheduler：封装了 GCD 的串行队列。如果我们需要执行一些串行任务，可以切换到这个 Scheduler 运行。
 - ConcurrentDispatchQueueScheduler：封装了 GCD 的并行队列。如果我们需要执行一些并发任务，可以切换到这个 Scheduler 运行。
 - OperationQueueScheduler：封装了 NSOperationQueue。
 
 
 
 
在GCD中获取数据，然后在主线程中刷新，代码是这样写的
```
DispatchQueue.global(qos: .userInitiated).async {
let data = try? Data(contentsOf: url)
DispatchQueue.main.async {
self.data = data
}
}

```

如果用 RxSwift 来实现，大致是这样的
 
```
let rxData: Observable<Data> = ...

rxData
.subscribeOn(ConcurrentDispatchQueueScheduler(qos: .userInitiated))
.observeOn(MainScheduler.instance)
.subscribe(onNext: { [weak self] data in
self?.data = data
})
.disposed(by: disposeBag)
 
```

### subscribeOn

我们用 subscribeOn 来决定数据序列的构建函数在哪个 Scheduler 上运行。以上例子中，由于获取 Data 需要花很长的时间，所以用 subscribeOn 切换到 后台 Scheduler 来获取 Data。这样可以避免主线程被阻塞。

### observeOn

我们用 observeOn 来决定在哪个 Scheduler 监听这个数据序列。以上例子中，通过使用 observeOn 方法切换到主线程来监听并且处理结果。

一个比较典型的例子就是，在后台发起网络请求，然后解析数据，最后在主线程刷新页面。你就可以先用 subscribeOn 切到后台去发送请求并解析数据，最后用 observeOn 切换到主线程更新页面。


### MainScheduler

MainScheduler 代表主线程。如果你需要执行一些和 UI 相关的任务，就需要切换到该 Scheduler 运行。 


### SerialDispatchQueueScheduler

SerialDispatchQueueScheduler 抽象了窜行 DispatchQueue。如果你需要执行一些串行任务，可以切换到这个 Scheduler 运行。

 
 ### ConcurrentDispatchQueueScheduler

ConcurrentDispatchQueueScheduler 抽象了并行 DispatchQueue。如果你需要执行一些并发任务，可以切换到这个 Scheduler 运行。



### OperationQueueScheduler

OperationQueueScheduler 抽象了 NSOperationQueue。它具备 NSOperationQueue 的一些特点，例如，你可以通过设置 maxConcurrentOperationCount，来控制同时执行并发任务的最大数量。 









