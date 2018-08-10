//
//  otherObservableController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/3.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
class otherObservableController: UIViewController {
    
    let disposeBag = DisposeBag()
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    
    @IBAction func single(_ sender: Any) {
        getRepo("ReactiveX/RxSwift")
            .subscribe(onSuccess: { data in
                let dict = try? JSONSerialization.jsonObject(with: data as! Data, options: []) as! [String: AnyObject]
                print("返回结果：\(String(describing: dict))")
            }, onError: { error in
                print("Error: ", error)
            })
            .disposed(by: disposeBag)
    }
    
    
    @IBAction func completable(_ sender: Any) {
        let completable = Completable.create { (com) -> Disposable in
            if arc4random()%2 == 1{
                com(.completed)
            }else{
                com(.error(self.getError()))
            }
            return Disposables.create()
        }
        
        
        completable.subscribe(onCompleted: {
            print("走到完成事件")
        }) { (error) in
            print("走到了错误事件")
        }.disposed(by: disposeBag)
        
        
    }
    
  
    
  
}

extension otherObservableController{
    
    
    func getError() -> NSError {
        let userInfo = ["error":"获得一个错误"]
        let error = NSError.init(domain: "error", code: 1, userInfo: userInfo)
        return error
    }
    
    
    //MARK:single
    func getRepo(_ repo: String) -> Single<Any>{
        let sing = Single<Any>.create { (single) -> Disposable in
            
            let url = URL(string: "https://api.github.com/repos/\(repo)")!
            let task = URLSession.shared.dataTask(with: url) {
                data, _, error in
                
                if let error = error {
                    single(.error(error))
                    return
                }
                
                guard let data = data else {
                    single(.error(self.getError()))
                    return
                }
                
                single(.success(data))
                
            }
            
            task.resume()
            return Disposables.create()
        }
        
       
        return sing
    }
    
    
    
    
}



















