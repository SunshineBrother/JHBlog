//
//  ViewController.swift
//  MyTableView
//
//  Created by yunna on 2019/3/28.
//  Copyright © 2019年 yunna. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    //有多种Cell类型表视图
    @IBAction func buttonEvent1(_ sender: Any) {
        let vc = ManyCellController()
        self.navigationController?.pushViewController(vc, animated: true)
    }
    
    //实现列表预加载
    @IBAction func buttonEvent2(_ sender: Any) {
    }
    
    
    //WebView和TableView混合使用
    @IBAction func buttonEvent3(_ sender: Any) {
    }
    
}

