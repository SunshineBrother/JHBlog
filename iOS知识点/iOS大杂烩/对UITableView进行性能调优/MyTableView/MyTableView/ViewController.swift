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
    
    // FoldingCell
    @IBAction func buttonEvent2(_ sender: Any) {
        let vc = FoldingCellController()
        self.navigationController?.pushViewController(vc, animated: true)
    }
    
    
    //复杂列表
    @IBAction func buttonEvent3(_ sender: Any) {
        let vc = IGListController()
        self.navigationController?.pushViewController(vc, animated: true)
    }
    
}

