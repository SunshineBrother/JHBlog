//
//  FilteringObservablesController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/13.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class FilteringObservablesController: UIViewController {
    let disposeBag = DisposeBag()
    override func viewDidLoad() {
        super.viewDidLoad()

        
//        initFilter()
//        initElementAt()
//        initSkip()
//        initSkipUntil()
//        initTake()
//        initTakeUntil()
//        initTakeWhile()
//        initSample()
        initdistinctUntilChanged()
        
        
        
        
        
        
        
    }

 
    func initFilter() {
        Observable.of(2, 30, 22, 5, 60, 3, 40 ,9)
            .filter {
                $0 > 10
            }
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
    }
    
    func initElementAt() {
        Observable.of("🐱", "🐰", "🐶", "🐸", "🐷", "🐵")
            .elementAt(2)
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
    }
    
    func initSkip() {
        Observable.of("🐱", "🐰", "🐶", "🐸", "🐷", "🐵")
        .skip(2)
        .subscribe(onNext: { print($0) })
        .disposed(by: disposeBag)
    }
    
    func initSkipUntil() {
        let sourceSequence1 = PublishSubject<Any>()
        let referenceSequence1 = PublishSubject<Any>()
        
        sourceSequence1
            
            .skipUntil(referenceSequence1)
            
            .subscribe(onNext: { print($0,"->skipUntil") })
            
            .disposed(by: disposeBag)
        
        sourceSequence1.onNext("🐱")
        
        sourceSequence1.onNext("🐰")
        
        sourceSequence1.onNext("🐶")
        
        referenceSequence1.onNext("🔴")
        
        sourceSequence1.onNext("🐸")
        
        sourceSequence1.onNext("🐷")
        
        sourceSequence1.onNext("🐵")
       
    }
    
    func initTake()  {
        Observable.of("1","2","3","4","5")
        .take(2)
        .subscribe(onNext: {print($0)})
        .disposed(by: disposeBag)
    }
    
    func initTakeUntil() {
        let disposeBag = DisposeBag()
        
        let source = PublishSubject<String>()
        let notifier = PublishSubject<String>()
        
        source
            .takeUntil(notifier)
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
        
        source.onNext("1")
        source.onNext("2")
       
        
        //停止接收消息
        notifier.onNext("0")
        
        source.onNext("3")
        source.onNext("4")
       
    }
    
    func initTakeWhile() {
        Observable.of(2, 3, 4, 5, 6)
            .takeWhile { $0 < 4 }
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
    }
    
    func initSample() {
        let source = PublishSubject<Int>()
        let notifier = PublishSubject<String>()
        source
            .sample(notifier)
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
        source.onNext(1)
        //让源序列接收接收消息
        notifier.onNext("A")
        source.onNext(2)
        //让源序列接收接收消息
        notifier.onNext("B")
        notifier.onNext("C")
        source.onNext(3)
        source.onNext(4)
        //让源序列接收接收消息
        notifier.onNext("D")
        source.onNext(5)
        source.onNext(6)
        //让源序列接收接收消息
        notifier.onCompleted()
    }
    
    func initDebounce() {
        //定义好每个事件里的值以及发送的时间
        let times = [
            [ "value": 1, "time": 0.1 ],
            [ "value": 2, "time": 1.1 ],
            [ "value": 3, "time": 1.2 ],
            [ "value": 4, "time": 1.2 ],
            [ "value": 5, "time": 1.4 ],
            [ "value": 6, "time": 2.1 ]
        ]
        
        //生成对应的 Observable 序列并订阅
        Observable.from(times)
            .flatMap { item in
                return Observable.of(Int(item["value"]!))
                    .delaySubscription(Double(item["time"]!),
                                       scheduler: MainScheduler.instance)
            }
            .debounce(0.5, scheduler: MainScheduler.instance) //只发出与下一个间隔超过0.5秒的元素
            .subscribe(onNext: { print($0) })
            .disposed(by: disposeBag)
    
    }
    
    
    func initdistinctUntilChanged() {
        Observable.of("1","2","1","1","2","2","0")
            .distinctUntilChanged()
            .subscribe(onNext: {print($0)})
            .disposed(by: disposeBag)
    }
    
    

}





















































































