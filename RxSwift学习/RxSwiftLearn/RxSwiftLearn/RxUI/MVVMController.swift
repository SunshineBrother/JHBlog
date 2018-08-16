//
//  MVVMController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/15.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class MVVMController: UIViewController {
    let disposeBag = DisposeBag()
    
    
    @IBOutlet weak var acountTF: UITextField!
    
    @IBOutlet weak var acoundDes: UILabel!
    
    @IBOutlet weak var psTF: UITextField!
    
    @IBOutlet weak var psDes: UILabel!
    
    @IBOutlet weak var login: UIButton!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

       
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
         
    }
 
    @IBAction func LoginEvent(_ sender: Any) {
        let alertController = UIAlertController(title: "去登录", message: nil, preferredStyle: .alert)
        let cancelAction = UIAlertAction(title: "确定", style: .cancel, handler: nil)
        alertController.addAction(cancelAction)
        self.present(alertController, animated: true, completion: nil)
    }
    
    
 
    
}












