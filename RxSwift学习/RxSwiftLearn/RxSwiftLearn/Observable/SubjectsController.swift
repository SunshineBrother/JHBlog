//
//  SubjectsController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/10.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class SubjectsController: UIViewController {
    
    let disposeBag = DisposeBag()
    override func viewDidLoad() {
        super.viewDidLoad()

        
//        initAsyncSubject()
//        initPublishSubject()
//        initReplaySubject()
//        initBehaviorSubject()
        
        
    }

  
    
    func initAsyncSubject() {
        let subject = AsyncSubject<String>()
        
        subject
            .subscribe { print("Subscription: 1 Event:", $0) }
            .disposed(by: disposeBag)
        
        subject.onNext("🐶")
        subject.onNext("🐱")
        subject.onNext("🐹")
        subject.onCompleted()
        
    }
    
    func initPublishSubject()  {
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
        
    }
    
    
    func initReplaySubject() {
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
        
    }
    
    
    
    func initBehaviorSubject() {
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
    }
    
    

}






















