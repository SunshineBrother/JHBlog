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
        
        
        
        setUPFrom()
        
        
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
    
    
    
    
    
    
    
    
    
}



























