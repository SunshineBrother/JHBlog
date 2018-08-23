//
//  ViewController.swift
//  demo
//
//  Created by yunna on 2018/8/23.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    //工厂模式
    @IBAction func button1(_ sender: Any) {
        let factory = OperationFactory().creatOperationWithSymbol(symbolStr: "+")
        factory.numberA = 10
        factory.numberB = 20
        let result = factory.getResult()
        print("result:\(result)")
    }
    //策略模式
    @IBAction func button2(_ sender: Any) {
    }
}

















