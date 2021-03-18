//
//  LoginViewModel.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/15.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
class LoginViewModel: NSObject {

    //输入源
    var usernameValid:Observable<Bool>!
    var pdValid:Observable<Bool>!
    var everythingValid:Observable<Bool>!
 
    init(username:Observable<String>,pd:Observable<String>) {
        usernameValid = username.map({ (text) -> Bool in
            return text.count > 5
        })
        pdValid = pd.map({ (text) -> Bool in
            return text.count > 5
        })
        everythingValid = Observable.combineLatest(usernameValid,pdValid){ $0 && $1}
        
    }
    
 
    
}
