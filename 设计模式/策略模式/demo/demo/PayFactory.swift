//
//  PayFactory.swift
//  demo
//
//  Created by yunna on 2018/8/24.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

@objc protocol PayStrategyProtocal {
    //去支付
    func goToPay()

}

class PayFactory: NSObject {

    var delegate:PayStrategyProtocal?
    init(payProtocal:PayStrategyProtocal) {
        super.init()
        self.delegate = payProtocal
    }
    
    func pay() {
        delegate?.goToPay()
    }
    
}













