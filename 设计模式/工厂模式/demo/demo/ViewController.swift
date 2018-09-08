//
//  ViewController.swift
//  demo
//
//  Created by yunna on 2018/8/22.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
 
    lazy var tableView: UITableView = {
        let tableView = UITableView(frame: self.view.frame, style: .plain)
        
        for (index,item) in reuseIdArr.enumerated(){
            tableView.register(cellArr[index], forCellReuseIdentifier: item)
        }
        tableView.delegate = self
        tableView.dataSource = self
        return tableView
    }()
    
    lazy var dataArr: Array<Model> = {
        let data = [
            Model.init(reuseId: "OneBaseCell", imagePath: "header", title: "我是第一个cell"),
            Model.init(reuseId: "TwoBaseCell", imagePath: "header", title: nil),
            Model.init(reuseId: "ThreeBaseCell", imagePath: "", title: "我是第三个cell")
        ]
        return data
    }()
    
    let reuseIdArr = ["OneBaseCell","TwoBaseCell","ThreeBaseCell"]
    let cellArr = [OneBaseCell.self,TwoBaseCell.self,ThreeBaseCell.self]
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        self.view.addSubview(self.tableView)
    }
 

}
extension ViewController: UITableViewDelegate, UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.dataArr.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = FactoryCell().configUI(model: self.dataArr[indexPath.row], tableView: tableView, indexPath: indexPath)
        
        return cell
    }
}
