//
//  ObserverControllerViewController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/10.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa

class ObserverControllerViewController: UIViewController {
    let disposeBag = DisposeBag()
    @IBOutlet weak var label: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    
    @IBAction func button(_ sender: Any) {
        
//        initSubscribe()
//        initBind()
//        initAnyObserver1()
//        initAnyObserver2()
//        initBinder()
        initbind1()
        
        
    }
    
    
    
    
    
    //1、在 subscribe 方法中创建
    func initSubscribe() {
        let observable = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        observable.subscribe(onNext: { [weak self] element in
            let text = "当前索引\(element)"
            self?.label.text = text
        }, onError: { error in
            print(error)
        }, onCompleted: {
            print("completed")
        }).disposed(by: disposeBag)
    }
    
    
    //2，在 bind 方法中创建
    func initBind() {
        //Observable序列（每隔1秒钟发出一个索引数）
        let observable = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        observable
        .map { "当前索引数：\($0)"}
        .bind { [weak self](text) in
                self?.label.text = text
        }
        .disposed(by: disposeBag)
     
    }
    
    //3、 AnyObserver 创建观察者
    func initAnyObserver1() {
        //观察者
        let observer:AnyObserver<Int> = AnyObserver {[weak self] (event) in
            switch event{
            case .next(let text):
                self?.label.text = "当前索引数：\(text)"
            case .error(let error):
                print(error)
            case .completed:
                print("completed")
            }
        }
        
        
        //序列
        let observable = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        observable.subscribe(observer).disposed(by: disposeBag)
        
    }
    
    //3、 AnyObserver 创建观察者  配合 bindTo 方法使用
    func initAnyObserver2() {
        //观察者
        let observer:AnyObserver<String> = AnyObserver { [weak self](event) in
            switch event {
            case .next(let text):
                //收到发出的索引数后显示到label上
                self?.label.text = text
            default:
                break
            }
        }
       
        
        //Observable序列（每隔1秒钟发出一个索引数）
        let observable = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        observable
            .map { "当前索引数：\($0 )"}
            .bind(to: observer)
            .disposed(by: disposeBag)
      
    }
    
    //4、Binder 创建观察者
    func initBinder()  {
        //观察者
        let observer:Binder<String> = Binder(label){ (view, text) in
            //收到发出的索引数后显示到label上
            view.text = text
        }
        
        //Observable序列（每隔1秒钟发出一个索引数）
        let observable = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        observable
            .map { "当前索引数：\($0 )"}
            .bind(to: observer)
            .disposed(by: disposeBag)
    }
        
        
    func initbind1() {
        let observable = Observable<Int>.interval(1, scheduler: MainScheduler.instance)
        observable
            .map { $0 % 2 == 0 }
            .bind(to: self.label.rx.isHidden)
            .disposed(by: disposeBag)
    }
    
    
    
    
    
    
    
}
