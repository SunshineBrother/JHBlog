//
//  ThreeBaseCell.swift
//  demo
//
//  Created by yunna on 2018/8/22.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class ThreeBaseCell: FactoryCell {
 
    
    override func configUI(model: Model, tableView: UITableView, indexPath: IndexPath) -> UITableViewCell {
       
        let cell =  tableView.dequeueReusableCell(withIdentifier: model.reuseId!, for: indexPath)
        self.configCell(model)
        return cell
    }
    
    func configCell(_ model: Model) {
        self.textLabel?.text = model.title
        self.backgroundColor = UIColor.red
    }
    
    
    
}
