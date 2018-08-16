## MVVM

 MVVM 是 Model-View-ViewModel 的简写。如果你已经对 MVC 非常熟悉了，那么上手 MVVM 也是非常容易的。

 
 #### MVC

   ![MVC](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/MVC.png)


MVC 是 Model-View-Controller 的简写。MVC 主要有三层：
- Model 数据层，读写数据
- View 页面层，和用户交互，向用户显示页面，反馈用户行为
- ViewController 逻辑层，更新数据，或者页面，处理业务逻辑

MVC 可以帮助你很好的将数据，页面，逻辑的代码分离开来。使得每一层相对独立。这样你就能够将一些可复用的功能抽离出来，化繁为简。只不过，一旦 App 的交互变复杂，你就会发现 ViewController 将变得十分臃肿。大量代码被添加到控制器中，使得控制器负担过重。此时，你就需要想办法将控制器里面的代码进一步地分离出来，对 APP 进行重新分层。而 MVVM 就是一种进阶的分层方案。

#### MVVM

   ![MVVM](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/MVVM.png)

MVVM 和 MVC 十分相识。只不过他的分层更加详细：
- Model 数据层，读写数据 
- View 页面层，提供用户输入行为，并且显示输出状态
- ViewModel 逻辑层，它将用户输入行为，转换成输出状态
- ViewController 主要负责数据绑定

没错，ViewModel 现在是逻辑层，而控制器只需要负责数据绑定。如此一来控制器的负担就减轻了许多。并且 ViewModel 与控制器以及页面相独立


#### 事例

   ![loginMVVM](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/loginMVVM.gif)

在重构前
```
class SimpleValidationViewController : ViewController {

...

override func viewDidLoad() {
super.viewDidLoad()

...

let usernameValid = usernameOutlet.rx.text.orEmpty
.map { $0.characters.count >= minimalUsernameLength }
.share(replay: 1)

let passwordValid = passwordOutlet.rx.text.orEmpty
.map { $0.characters.count >= minimalPasswordLength }
.share(replay: 1)

let everythingValid = Observable.combineLatest(
usernameValid,
passwordValid
) { $0 && $1 }
.share(replay: 1)

usernameValid
.bind(to: passwordOutlet.rx.isEnabled)
.disposed(by: disposeBag)

usernameValid
.bind(to: usernameValidOutlet.rx.isHidden)
.disposed(by: disposeBag)

passwordValid
.bind(to: passwordValidOutlet.rx.isHidden)
.disposed(by: disposeBag)

everythingValid
.bind(to: doSomethingOutlet.rx.isEnabled)
.disposed(by: disposeBag)

doSomethingOutlet.rx.tap
.subscribe(onNext: { [weak self] in self?.showAlert() })
.disposed(by: disposeBag)
}

...

}
```

**ViewModel**
   ![ViewModel](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/ViewModel.png)

ViewModel 将用户输入行为，转换成输出的状态：
```
//输入源
var usernameValid:Observable<Bool>!
var pdValid:Observable<Bool>!
var everythingValid:Observable<Bool>!

init(
username:Observable<String>,
pd:Observable<String>
) {

usernameValid = username.map({ (text) -> Bool in
return text.count > 5
})

pdValid = pd.map({ (text) -> Bool in
return text.count > 5
})

everythingValid = Observable.combineLatest(usernameValid,pdValid){ $0 && $1}

}
```
输入：
- username 输入的用户名
- passwordValid 输入的密码
输出:
- usernameValid 用户名是否有效
- passwordValid 密码是否有效
- everythingValid 所有输入是否有效
在 init 方法内部，将输入转换为输出。


ViewController 主要负责数据绑定：
```
let viewModel = LoginViewModel(
username: acountTF.rx.text.orEmpty.asObservable(),
pd: psTF.rx.text.orEmpty.asObservable()
)

viewModel.usernameValid
.bind(to: acoundDes.rx.isHidden)
.disposed(by: disposeBag)

viewModel.pdValid
.bind(to: psDes.rx.isHidden)
.disposed(by: disposeBag)


viewModel.everythingValid
.bind(to: login.rx.isEnabled)
.disposed(by: disposeBag)

viewModel.everythingValid
.subscribe(onNext: { [unowned self](valid) in
print(valid)
self.login.alpha = valid ? 1 : 0.5
}).disposed(by: disposeBag)
```

输入：

- username 将输入的用户名传入 ViewModel
- password 将输入的密码传入 ViewModel
输出：
- usernameValid 用用户名是否有效，来控制提示语是否隐藏，密码输入框是否可用
- passwordValid 用密码是否有效，来控制提示语是否隐藏
- everythingValid 用两者是否同时有效，来控制按钮是否可点击
当 App 的交互变复杂时，你仍然可以保持控制器结构清晰。这样可以大大的提升代码可读性。将来代码维护起来也就会容易许多了。

















