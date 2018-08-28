//
//  simpleFactory.swift
//  demo
//
//  Created by yunna on 2018/8/24.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class simpleFactory: NSObject {
    func configUI(model: Model, tableView: UITableView, indexPath: IndexPath) -> UITableViewCell {
        print(model.reuseId)
        let cell = tableView.dequeueReusableCell(withIdentifier: model.reuseId!, for: indexPath)
        if model.reuseId == "OneBaseCell" {
            (cell as! OneBaseCell).configCell(model)
        }else if model.reuseId == "TwoBaseCell" {
            (cell as! TwoBaseCell).configCell(model)
        }else{
            (cell as! ThreeBaseCell).configCell(model)
        }
        
        return cell
    }
    
    
    
    
}
