//
//  mergeController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/3.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
class mergeController: UIViewController {

    let disposeBag = DisposeBag()
    override func viewDidLoad() {
        super.viewDidLoad()

        
    }

  
    @IBAction func merge(_ sender: Any) {
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
    
    }
    
    
    
    
}


























