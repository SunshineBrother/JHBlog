//
//  ThreeBaseCell.swift
//  demo
//
//  Created by yunna on 2018/8/22.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class ThreeBaseCell: UITableViewCell {
 
    func configCell(_ model: Model) {
        self.textLabel?.text = model.title
        self.backgroundColor = UIColor.red
    }
    
    
    
}
