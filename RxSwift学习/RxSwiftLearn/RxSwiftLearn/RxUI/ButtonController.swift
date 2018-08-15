//
//  ButtonController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/15.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class ButtonController: UIViewController {
    @IBOutlet weak var button: UIButton!
    let disposeBag = DisposeBag()
    override func viewDidLoad() {
        super.viewDidLoad()

        buttonEvent2()
    }

    //事件绑定
    func buttonEvent1() {
        let btn = button.rx.tap
        btn.throttle(1, scheduler: MainScheduler.instance)
            .subscribe(onNext: {[unowned self] in
                self.showMessage("点击button")
                })
            .disposed(by: disposeBag)
       
    }
    
    //按钮标题（title）的绑定
    func buttonEvent2() {
        //创建一个计时器（每1秒发送一个索引数）
        let timer = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        
        //根据索引数拼接最新的标题，并绑定到button上
        timer.map{"计数\($0)"}
            .bind(to: button.rx.title(for: .normal))
            .disposed(by: disposeBag)
        
    }
    //按钮图标（image）的绑定
    func buttonEvent3() {
        
        //创建一个计时器（每1秒发送一个索引数）
        let timer = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        
        //根据索引数选择对应的按钮图标，并绑定到button上
        timer.map({
            let name = $0%2 == 0 ? "back" : "forward"
            return UIImage(named: name)!
        })
            .bind(to: button.rx.image())
            .disposed(by: disposeBag)
    }
    
    
    //显示消息提示框
    func showMessage(_ text: String) {
        let alertController = UIAlertController(title: text, message: nil, preferredStyle: .alert)
        let cancelAction = UIAlertAction(title: "确定", style: .cancel, handler: nil)
        alertController.addAction(cancelAction)
        self.present(alertController, animated: true, completion: nil)
    }

}








































