### merge 
 将多个 Observables 合并成一个
 通过使用 merge 操作符你可以将多个 Observables 合并成一个，当某一个 Observable 发出一个元素时，他就将这个元素发出。
 如果，某一个 Observable 发出一个 onError 事件，那么被合并的 Observable 也会将它发出，并且立即终止序列。
 
  ![merge](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/merge.png)
 
 ```
 let subject1 = PublishSubject<String>()
 let subject2 = PublishSubject<String>()
 
 Observable
 .of(subject1,subject2)
 .merge()
 .subscribe(onNext: { print($0) })
 .disposed(by: disposeBag)
 
 
 
 subject2.onNext("A")
 subject2.onNext("B")
 subject1.onNext("1")
 subject1.onNext("2")
 subject1.onNext("3")
 subject2.onNext("C")
 ```
 打印结果
 ```
 A
 B
 1
 2
 3
 C
 ```
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
