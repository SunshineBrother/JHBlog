//
//  Operation.swift
//  demo
//
//  Created by yunna on 2018/8/23.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class Operation: NSObject {

    var numberA:Double = 0
    var numberB:Double = 0
    
    func getResult() -> Double{
        return 0
    }
    
    
}

//MARK: -- 子类 --
//MARK: - 加法运算 --
class OperationAdd: Operation {
    
    override func getResult() -> Double {
        return numberA + numberB
    }
    
}
//MARK: - 减法运算 --
class OperationSub: Operation {
    override func getResult() -> Double {
        return numberA - numberB
    }
}

//MARK: - 乘法运算 --
class OperationMUL: Operation {
    override func getResult() -> Double {
        return numberA * numberB
    }
}
//MARK: - 除法运算 --
class OperationDiv: Operation {
    override func getResult() -> Double {
        guard numberB != 0 else {
            return 0
        }
        return numberA / numberB
    }
}







