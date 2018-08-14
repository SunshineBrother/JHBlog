//
//  CombiningController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/14.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class CombiningController: UIViewController {
    let disposeBag = DisposeBag()
    override func viewDidLoad() {
        super.viewDidLoad()

//        initMerge()
//        initConcat()
//        initZip()
        initCombineLatest()
    }

    func initMerge() {
        let subject1 = PublishSubject<String>()
        let subject2 = PublishSubject<String>()
        Observable.of(subject1,subject2)
        .merge()
        .subscribe(onNext: {print($0)})
        .disposed(by: disposeBag)
        
        subject1.onNext("A")
        subject1.onNext("B")
        subject2.onNext("1")
        subject1.onNext("C")
        subject2.onNext("2")
        
        
        
    }
    
    func initConcat() {
        let subject1 = BehaviorSubject(value: 1)
        let subject2 = BehaviorSubject(value: 2)
        
        let variable = Variable(subject1)
        variable.asObservable()
            .concat()
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
        
        subject2.onNext(2)
        subject1.onNext(1)
        subject1.onNext(1)
        subject1.onCompleted()
        
        variable.value = subject2
        subject2.onNext(2)
        

    }
    
    func initZip()  {
        let subject1 = PublishSubject<String>()
        let subject2 = PublishSubject<String>()
        Observable.zip(subject1,subject2){
            "\($0)\($1)"
            }
        .subscribe(onNext: {print($0)})
        .disposed(by: disposeBag)
        
        subject1.onNext("A")
        subject1.onNext("B")
        subject2.onNext("1")
        subject1.onNext("C")
        subject2.onNext("2")
    }
    
    
    func initCombineLatest() {
        let subject1 = PublishSubject<String>()
        let subject2 = PublishSubject<String>()
        
        Observable.combineLatest(subject1, subject2) {
            "\($0)\($1)"
            }
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
        
        subject1.onNext("A")
        subject1.onNext("B")
        subject2.onNext("1")
        subject1.onNext("C")
        subject2.onNext("2")
    }
    
  
}




















