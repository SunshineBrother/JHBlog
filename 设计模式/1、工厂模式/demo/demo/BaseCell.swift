//
//  BaseCell.swift
//  demo
//
//  Created by yunna on 2018/8/22.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class BaseCell: UITableViewCell {

    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

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
