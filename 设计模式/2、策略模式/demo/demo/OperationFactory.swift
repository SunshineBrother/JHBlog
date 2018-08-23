//
//  OperationFactory.swift
//  demo
//
//  Created by yunna on 2018/8/23.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class OperationFactory: NSObject {

    func creatOperationWithSymbol(symbolStr:String) -> Operation {
        
        switch symbolStr {
        case "+":
            return OperationAdd()
        case "-":
            return OperationSub()
        case "*":
            return OperationMUL()
        case "/":
            return OperationDiv()
        default:
            return Operation()
            
        }
    }
    
}











