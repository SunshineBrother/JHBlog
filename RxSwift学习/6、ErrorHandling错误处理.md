## Error Handling 错误处理 
 一旦序列里面产出了一个 error 事件，整个序列将被终止。RxSwift 主要有两种错误处理机制：
 
- retry 重试
- catch 恢复

###  retry 重试

retry 可以让序列在发生错误后重试：
```
// 请求 JSON 失败时，立即重试，
// 重试 3 次后仍然失败，就将错误抛出

let rxJson: Observable<JSON> = ...

rxJson
.retry(3)
.subscribe(onNext: { json in
print("取得 JSON 成功: \(json)")
}, onError: { error in
print("取得 JSON 失败: \(error)")
})
.disposed(by: disposeBag)
```
以上的代码非常直接 retry(3) 就是当发生错误时，就进行重试操作，并且最多重试 3 次。


### retryWhen

如果我们需要在发生错误时，经过一段延时后重试，那可以这样实现

```
// 请求 JSON 失败时，等待 5 秒后重试，
let retryDelay: Double = 5  // 重试延时 5 秒

rxJson
.retryWhen { (rxError: Observable<Error>) -> Observable<Int> in
return Observable.timer(retryDelay, scheduler: MainScheduler.instance)
}
.subscribe(...)
.disposed(by: disposeBag)  
```

这里我们需要用到 retryWhen 操作符，这个操作符主要描述应该在何时重试，并且通过闭包里面返回的 Observable 来控制重试的时机： 
```
.retryWhen { (rxError: Observable<Error>) -> Observable<Int> in
...
}  
```
闭包里面的参数是 Observable<Error> 也就是所产生错误的序列，然后返回值是一个 Observable。当这个返回的 Observable 发出一个元素时，就进行重试操作。当它发出一个 error 或者 completed 事件时，就不会重试，并且将这个事件传递给到后面的观察者 



如果需要加上一个最大重试次数的限制： 

```
// 请求 JSON 失败时，等待 5 秒后重试，
// 重试 4 次后仍然失败，就将错误抛出

let maxRetryCount = 4       // 最多重试 4 次
let retryDelay: Double = 5  // 重试延时 5 秒

rxJson
.retryWhen { (rxError: Observable<Error>) -> Observable<Int> in
return rxError.flatMapWithIndex { (error, index) -> Observable<Int> in
guard index <  
maxRetryCount else {
return Observable.error(error)
}
return Observable<Int>.timer(retryDelay, scheduler: MainScheduler.instance)
}
}
.subscribe(...)
.disposed(by: disposeBag) 

```
### catchError - 恢复

catchError 可以在错误产生时，用一个备用元素或者一组备用元素将错误替换掉： 

```
// 先从网络获取数据，如果获取失败了，就从本地缓存获取数据

let rxData: Observable<Data> = ...      // 网络请求的数据
let cahcedData: Observable<Data> = ...  // 之前本地缓存的数据

rxData
.catchError { _ in cahcedData }
.subscribe(onNext: { date in
print("获取数据成功: \(date.count)") 
})
.disposed(by: disposeBag)
```



















