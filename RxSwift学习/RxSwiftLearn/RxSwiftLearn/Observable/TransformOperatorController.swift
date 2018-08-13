//
//  TransformOperatorController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/11.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class TransformOperatorController: UIViewController {
    let disposeBag = DisposeBag()
    override func viewDidLoad() {
        super.viewDidLoad()

//        initMap()
//        initFlatMap()
//        initFlatMapLatest()
//        initConcatMap()
        initScan()
        
    }

    func initMap() {
        Observable.of(1, 2, 3)
            .map { $0 * 10 }
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
    }
    
    func initFlatMap()  {
       
        
        let subject1 = BehaviorSubject(value: "A")
        let subject2 = BehaviorSubject(value: "1")
        
        let variable = Variable(subject1)
        
        variable.asObservable()
            .flatMap { $0 }
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
        
        subject1.onNext("B")
        variable.value = subject2
        subject2.onNext("2")
        subject1.onNext("C")
    }
    
    
    func initFlatMapLatest() {
        let subject1 = BehaviorSubject(value: "A")
        let subject2 = BehaviorSubject(value: "1")
        
        let variable = Variable(subject1)
        
        variable.asObservable()
            .flatMapLatest { $0 }
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
        
        subject1.onNext("B")
        variable.value = subject2
        subject2.onNext("2")
        subject1.onNext("C")
    }
    
    func initConcatMap() {
        let subject1 = BehaviorSubject(value: "A")
        let subject2 = BehaviorSubject(value: "1")
        
        let variable = Variable(subject1)
        
        variable.asObservable()
            .concatMap { $0 }
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
        
        subject1.onNext("B")
        variable.value = subject2
        subject2.onNext("2")
        subject1.onNext("C")
        subject1.onCompleted() //只有前一个序列结束后，才能接收下一个序列
    }
    

    func initScan() {
        Observable.of(2, 4, 6)
            .scan(1) { aggregateValue, newValue in
            aggregateValue * newValue
            }
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
    }
    
    
    
    
    
    
    
}














