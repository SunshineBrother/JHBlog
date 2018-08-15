//
//  TextController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/15.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class TextController: UIViewController {
    let disposeBag = DisposeBag()
    
    @IBOutlet weak var acountTF: UITextField!
    @IBOutlet weak var passwordTF: UITextField!
    
    @IBOutlet weak var login: UILabel!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
//        initTF1()
//        initTF2()
//        initTF3()
        loginEvent()
    }

    
    //简单使用
    //.orEmpty 可以将 String? 类型的 ControlProperty 转成 String，省得我们再去解包。
    func initTF1() {
        let sub = acountTF.rx.text
        sub.orEmpty
            .subscribe(onNext: {
                print("您输入的是：\($0)")
            })
        .disposed(by: disposeBag)
        
    }
    
    //绑定到其他控件中
    func initTF2() {
        let observable = acountTF.rx.text
        observable.orEmpty.asDriver()
                .throttle(0.5)
                .map({ (text) -> String in
                    return "输出：" + text
                })
                .drive(login.rx.text)
                .disposed(by: disposeBag)
        
    }
    //事件监听
    //通过 rx.controlEvent 可以监听输入框的各种事件，且多个事件状态可以自由组合。除了各种 UI 控件都有的 touch 事件外，输入框还有如下几个独有的事件：
    func initTF3() {
        acountTF.rx.controlEvent([.editingDidBegin]) //状态可以组合
            .asObservable()
            .subscribe(onNext: { _ in
                print("开始编辑内容!")
            }).disposed(by: disposeBag)
    }
 
    //登录事件
    func loginEvent()  {
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
        
       
      
    }
    
}









