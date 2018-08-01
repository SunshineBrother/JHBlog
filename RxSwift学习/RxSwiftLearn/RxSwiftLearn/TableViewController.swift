//
//  TableViewController.swift
//  SwiftToolTest
//
//  Created by yunna on 2018/4/28.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import SwiftyJSON

class TableViewController: UITableViewController {
    ///数据源
    let dataList = NSMutableArray()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationItem.title = "RxSwift"
        //获取数据源
        obtainDataSource()
    }
 
    ///获取数据源
    func obtainDataSource() {
        let filePath = Bundle.main.path(forResource: "RxSwift", ofType: "plist")
        let fileDic = NSDictionary.init(contentsOfFile: filePath!) ?? [String : Any]() as NSDictionary
        let json = JSON(fileDic)
        for (key,value) in json {
            let GModel = groupModel()
            GModel.groupName = key
            let detailArr = JSON(value).arrayValue
            for item in detailArr{
                let model = Model()
                model.title = item["Title"].stringValue
                model.className = item["Class"].stringValue
                GModel.detailArr.add(model)
            }
            
            self.dataList.add(GModel)
            
        }
  
        
    }
 

    // MARK: - Table view data source
    override func numberOfSections(in tableView: UITableView) -> Int {
        return self.dataList.count
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let model = self.dataList[section] as! groupModel
        return model.detailArr.count
    }

    override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        let model = self.dataList[section] as! groupModel
        return model.groupName
    }
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "cell")
        if cell == nil {
            cell = UITableViewCell.init(style: UITableViewCellStyle.default, reuseIdentifier: "cell")
        }
        let GModel = self.dataList[indexPath.section] as! groupModel
        let model = GModel.detailArr[indexPath.row] as! Model
        
        cell?.textLabel?.text = model.title
        
        return cell!
    }
 
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        let GModel = self.dataList[indexPath.section] as! groupModel
        let model = GModel.detailArr[indexPath.row] as! Model
        
        let nameSpace = Bundle.main.infoDictionary?["CFBundleName"] as? String ?? ""
        guard let cls = NSClassFromString(nameSpace + "." + model.className) as? UIViewController.Type else {
            return
        }
        // 通过得到的class类型创建对象
        let vcClass = cls.init()
        vcClass.view.backgroundColor = UIColor.white
        vcClass.title = model.title
        self.navigationController?.pushViewController(vcClass, animated: true)
 
    }

}






























