//
//  ViewController.swift
//  UITableView架构
//
//  Created by yunna on 2019/3/16.
//  Copyright © 2019年 yunna. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    
    
    //MARK:构建具有多种 Cell 类型的表视图
    @IBAction func buttonEvent1(_ sender: Any) {
        let vc = ManyCellController()
        self.navigationController?.pushViewController(vc, animated: true)
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    

}

