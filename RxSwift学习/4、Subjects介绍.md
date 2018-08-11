## Subjects

从前面的几篇文章可以发现，当我们创建一个 Observable 的时候就要预先将要发出的数据都准备好，等到有人订阅它时再将数据通过 Event 发出去。
 
 但有时我们希望 Observable 在运行时能动态地“获得”或者说“产生”出一个新的数据，再通过 Event 发送出去。比如：订阅一个输入框的输入内容，当用户每输入一个字后，这个输入框关联的 Observable 就会发出一个带有输入内容的 Event，通知给所有订阅者。
 
 ```
 “// 作为可被监听的序列
 let observable = textField.rx.text
 observable.subscribe(onNext: { text in show(text: text) })”
 
 ```
 
 
 ```
 “// 作为观察者
 let observer = textField.rx.text
 let text: Observable<String?> = ...
 text.bind(to: observer)”
 
 ```
 “有许多 UI 控件都存在这种特性，例如：`switch`的开关状态，`segmentedControl`的选中索引号，`datePicker`的选中日期等等。”
  
 这个就可以使用下面将要介绍的 Subjects 来实现。
 
 ### Subjects 基本介绍
 
 （1）Subjects 既是订阅者，也是 Observable：
 
 - 说它是订阅者，是因为它能够动态地接收新的值。
 - 说它又是一个 Observable，是因为当 Subjects 有了新的值之后，就会通过 Event 将新值发出给他的所有订阅者。
 
 （2）一共有四种 Subjects，分别为：PublishSubject、BehaviorSubject、ReplaySubject、Variable。他们之间既有各自的特点，也有相同之处：
 
 - 首先他们都是 Observable，他们的订阅者都能收到他们发出的新的 Event。
 - 直到 Subject 发出 .complete 或者 .error 的 Event 后，该 Subject 便终结了，同时它也就不会再发出 .next 事件。
 - 对于那些在 Subject 终结后再订阅他的订阅者，也能收到 subject 发出的一条 .complete 或 .error 的 event，告诉这个新的订阅者它已经终结了。
 - 他们之间最大的区别只是在于：当一个新的订阅者刚订阅它的时候，能不能收到 Subject 以前发出过的旧 Event，如果能的话又能收到多少个。
 
 ### AsyncSubject
  ![AsyncSubject](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/AsyncSubject.png)
 
 AsyncSubject“将在源 Observable 产生完成事件后，发出最后一个元素（仅仅只有最后一个元素），如果源 Observable 没有发出任何元素，“只有一个完成事件。那 AsyncSubject 也只有一个完成事件。”
 

 “如果源 Observable 因为产生了一个 error 事件而中止， AsyncSubject 就不会发出任何元素，而是将这个 error 事件发送出来”
 
 ```
 let subject = AsyncSubject<String>()
 
 subject
 .subscribe { print("Subscription: 1 Event:", $0) }
 .disposed(by: disposeBag)
 
 subject.onNext("🐶")
 subject.onNext("🐱")
 subject.onNext("🐹")
 subject.onCompleted()
 ```
 输出结果
 ```
 Subscription: 1 Event: next(🐹)
 Subscription: 1 Event: completed

 ```
 
 ### PublishSubject
 
   ![PublishSubject](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/PublishSubject.png)
 
 
PublishSubject 的订阅者从他们开始订阅的时间点起，可以收到订阅后 Subject 发出的新 Event，而不会收到他们在订阅前已发出的 Event
 
 
 “如果源 Observable 因为产生了一个 error 事件而中止， PublishSubject 就不会发出任何元素，而是将这个 error 事件发送出来”
 
 ```
 let subject = PublishSubject<String>()
 subject.onNext("此时没有订阅者，所以这条信息不会输出到控制台")
 
 subject
 .subscribe { print("Subscription: 1 Event:", $0) }
 .disposed(by: disposeBag)
 
 subject.onNext("🐶")
 subject.onNext("🐱")
 
 subject
 .subscribe { print("Subscription: 2 Event:",$0) }
 .disposed(by: disposeBag)
 
 subject.onNext("🅰️")
 subject.onNext("🅱️")
 ```
 
 打印结果
 ```
 Subscription: 1 Event: next(🐶)
 Subscription: 1 Event: next(🐱)
 Subscription: 1 Event: next(🅰️)
 Subscription: 2 Event: next(🅰️)
 Subscription: 1 Event: next(🅱️)
 Subscription: 2 Event: next(🅱️)
 ```
 
 
 ### ReplaySubject
 
 
![ReplaySubject](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/ReplaySubject.png)
 
 - ReplaySubject 在创建时候需要设置一个 bufferSize，表示它对于它发送过的 event 的缓存个数。
 
 - 比如一个 ReplaySubject 的 bufferSize 设置为 2，它发出了 3 个 .next 的 event，那么它会将后两个（最近的两个）event 给缓存起来。此时如果有一个 subscriber 订阅了这个 ReplaySubject，那么这个 subscriber 就会立即收到前面缓存的两个 .next 的 event。
 
 - 如果一个 subscriber 订阅已经结束的 ReplaySubject，除了会收到缓存的 .next 的 event 外，还会收到那个终结的 .error 或者 .complete 的 event。
 
 - 如果把 ReplaySubject 当作观察者来使用，注意不要在多个线程调用 onNext, onError 或 onCompleted。这样会导致无序调用，将造成意想不到的结果
  
 
 
 ```
 //创建一个bufferSize为2的ReplaySubject
 let subject = ReplaySubject<String>.create(bufferSize: 2)
 
 //连续发送3个next事件
 subject.onNext("111")
 subject.onNext("222")
 subject.onNext("333")
 
 //第1次订阅subject
 subject.subscribe { event in
 print("第1次订阅：", event)
 }.disposed(by: disposeBag)
 
 //再发送1个next事件
 subject.onNext("444")
 
 //第2次订阅subject
 subject.subscribe { event in
 print("第2次订阅：", event)
 }.disposed(by: disposeBag)
 
 //让subject结束
 subject.onCompleted()
 
 //第3次订阅subject
 subject.subscribe { event in
 print("第3次订阅：", event)
 }.disposed(by: disposeBag)
 ```
 
打印结果
```
第1次订阅： next(222)
第1次订阅： next(333)
第1次订阅： next(444)
第2次订阅： next(333)
第2次订阅： next(444)
第1次订阅： completed
第2次订阅： completed
第3次订阅： next(333)
第3次订阅： next(444)
第3次订阅： completed
```

 
 ### BehaviorSubject

当观察者对 BehaviorSubject 进行订阅时，它会将源 Observable 中最新的元素发送出来（如果不存在最新的元素，就发出默认元素）。然后将随后产生的元素发送出来。

 
 如果源 Observable 因为产生了一个 error 事件而中止， BehaviorSubject 就不会发出任何元素，而是将这个 error 事件发送出来。
 
 ```
 //创建一个BehaviorSubject
 let subject = BehaviorSubject(value: "111")
 subject.onNext("222")
 subject.onNext("333")
 //第1次订阅subject
 subject.subscribe { event in
 print("第1次订阅：", event)
 }.disposed(by: disposeBag)
 
 //发送next事件
 subject.onNext("444")
 subject.onNext("555")
 
 //发送error事件
 subject.onError(NSError(domain: "local", code: 0, userInfo: nil))
 
 //第2次订阅subject
 subject.subscribe { event in
 print("第2次订阅：", event)
 }.disposed(by: disposeBag)
 ```
 打印结果
 
 ```
 第1次订阅： next(333)
 第1次订阅： next(444)
 第1次订阅： next(555)
 第1次订阅： error(Error Domain=local Code=0 "(null)")
 第2次订阅： error(Error Domain=local Code=0 "(null)")
 ```
 
 
 
 
 
 
 
 
 
 
 
 


















