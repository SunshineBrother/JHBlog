//
//  CreateController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/1.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
class CreateController: UIViewController {
    
    let disposeBag = DisposeBag()
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //create方法
//        setUpCreate()
        
        //产生特定的一个元素 just
//        setUPJust()
        
        
        
//        setUPFrom()
        
        
//        setUPRepeatElement()
        
        
//        setUPDeferredt()
        
        
//        setUPInterval()
        
        setUPTimer()
    }
 
}

extension CreateController {
    //MARK:create方法
    func setUpCreate()  {
        let observable = Observable<Any>.create { (observer) -> Disposable in
            
            observer.onNext("测试create1")
            observer.onNext("测试create2")
            observer.onNext("测试create3")
            observer.onCompleted()
            
            return Disposables.create()
        }
        
        //订阅测试
        observable.subscribe(onNext: { (result) in
            print(result)
        }, onError: { (error) in
            print(error)
        }, onCompleted: {
            print("结束")
        }).disposed(by: disposeBag)
        
    }
    
    
    //MARK:产生特定的一个元素 just
    func setUPJust(){
        let observable = Observable<Int>.just(5)
        observable.subscribe(onNext: { (result) in
            print(result)
        }, onError: { (error) in
            
        }, onCompleted: {
            print("结束")
        }).disposed(by: disposeBag)
    }
    
    //MARK:from
    //将其他类型或者数据结构转换为 Observable
    //当你在使用 Observable 时，如果能够直接将其他类型转换为 Observable，这将是非常省事的。from 操作符就提供了这种功能。
    func setUPFrom() {
        let observable = Observable.from([1,2,3,4,5])
//        let observable = Observable.from(["1":"one","2":"two"])
        
        observable.subscribe(onNext: { (result) in
            print(result)
        }, onError: { (error) in
            
        }, onCompleted: {
            print("结束")
        }).disposed(by: disposeBag)
  
    }
    
    //MARK:repeatElement
    //该方法创建一个可以无限发出给定元素的 Event 的 Observable 序列（永不终止）。
    func setUPRepeatElement() {
        let observable = Observable.repeatElement(2)
        observable.subscribe(onNext: { (result) in
            print(result)
        }, onError: { (error) in
            
        }, onCompleted: {
            print("结束")
        }).disposed(by: disposeBag)
    }
    
    //MARK:deferred
    //直到订阅发生，才创建 Observable，并且为每位订阅者创建全新的 Observable
    func setUPDeferredt() {
        //用于标记是奇数、还是偶数
        var isOdd = true
        
        //使用deferred()方法延迟Observable序列的初始化，通过传入的block来实现Observable序列的初始化并且返回。
        let factory : Observable<Int> = Observable.deferred {
            
            //让每次执行这个block时候都会让奇、偶数进行交替
            isOdd = !isOdd
            
            //根据isOdd参数，决定创建并返回的是奇数Observable、还是偶数Observable
            if isOdd {
                return Observable.of(1, 3, 5 ,7)
            }else {
                return Observable.of(2, 4, 6, 8)
            }
        }
        
        //第1次订阅测试
        factory.subscribe { event in
            print("\(isOdd)", event)
        }.disposed(by: disposeBag)
        
        //第2次订阅测试
        factory.subscribe { event in
            print("\(isOdd)", event)
        }.disposed(by: disposeBag)
    }

    //MARK:Interval
    //interval 操作符将创建一个 Observable，它每隔一段设定的时间，发出一个索引数的元素。它将发出无数个元素。
    func setUPInterval() {
        let observable = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        observable.subscribe { event in
            print(event)
        }.disposed(by: disposeBag)
        
    }
    //MARK:timer
    func setUPTimer() {
        //（1）这个方法有两种用法，一种是创建的 Observable 序列在经过设定的一段时间后，产生唯一的一个元素。
        let observable = Observable<Int>.timer(5, scheduler: MainScheduler.instance)
        //延时5秒种后，每隔1秒钟发出一个元素
//        let observable = Observable<Int>.timer(5, period: 1, scheduler: MainScheduler.instance)
        observable.subscribe { event in
            print(event)
        }.disposed(by: disposeBag)
     
    }
    
    
    //MARK:empty
    //该方法创建一个空内容的 Observable 序列。
    func setUPEmpty() {
        let _ = Observable<String>.empty()
    }
    
}



























