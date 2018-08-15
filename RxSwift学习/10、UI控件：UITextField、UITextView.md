## UITextField 与 UITextView 
 
 ### 简单使用
 
 .orEmpty 可以将 String? 类型的 ControlProperty 转成 String，省得我们再去解包。

打印输入框内容
 ```
 let sub = acountTF.rx.text
 sub.orEmpty
 .subscribe(onNext: {
 print("您输入的是：\($0)")
 })
 .disposed(by: disposeBag)
 ```
 ### 绑定到其他控件
 ```
 let observable = acountTF.rx.text
 observable.orEmpty.asDriver()
 .throttle(0.5)
 .map({ (text) -> String in
 return "输出：" + text
 })
 .drive(login.rx.text)
 .disposed(by: disposeBag)
 ```

### 事件监听

通过 rx.controlEvent 可以监听输入框的各种事件，且多个事件状态可以自由组合。除了各种 UI 控件都有的 touch 事件外，输入框还有如下几个独有的事件：

- editingDidBegin：开始编辑（开始输入内容）
- editingChanged：输入内容发生改变
- editingDidEnd：结束编辑
- editingDidEndOnExit：按下 return 键结束编辑
- allEditingEvents：包含前面的所有编辑相关事件

```
acountTF.rx.controlEvent([.editingDidBegin]) //状态可以组合
.asObservable()
.subscribe(onNext: { _ in
print("开始编辑内容!")
}).disposed(by: disposeBag)
```

### UITextView 独有的方法


UITextView 还封装了如下几个委托回调方法：
- didBeginEditing：开始编辑
- didEndEditing：结束编辑
- didChange：编辑内容发生改变
- didChangeSelection：选中部分发生变化

```
//开始编辑响应
textView.rx.didBeginEditing
.subscribe(onNext: {
print("开始编辑")
})
.disposed(by: disposeBag)

//结束编辑响应
textView.rx.didEndEditing
.subscribe(onNext: {
print("结束编辑")
})
.disposed(by: disposeBag)

//内容发生变化响应
textView.rx.didChange
.subscribe(onNext: {
print("内容发生改变")
})
.disposed(by: disposeBag)

//选中部分变化响应
textView.rx.didChangeSelection
.subscribe(onNext: {
print("选中部分发生变化")
})
.disposed(by: disposeBag)
}
```

### 登录
要求：用户名和密码字符数量都超过6

```
//判断账号的输入是否可用
let accountValid:Observable = acountTF.rx.text.orEmpty.map{ value in
return value.count >= 6
}
//判断密码的输入是否可用
let passwordValid:Observable = passwordTF.rx.text.orEmpty.map{ value in
return value.count >= 6
}
//登录按钮的可用与否
let loginObserver = Observable<Bool>.combineLatest(accountValid,passwordValid){(account,password) in
print("account:\(account)" + "password:\(password)")
return account && password
}

//绑定按钮
loginObserver.subscribe(onNext: { [unowned self](valid) in
print(valid)
self.login.alpha = valid ? 1 : 0.5
}).disposed(by: disposeBag)
```


















