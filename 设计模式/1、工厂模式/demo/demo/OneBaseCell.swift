//
//  OneBaseCell.swift
//  demo
//
//  Created by yunna on 2018/8/22.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class OneBaseCell: UITableViewCell {

    var IV = UIImageView()
    var label = UILabel()
    
   
    override init(style: UITableViewCellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        IV.frame = CGRect(x: 20, y: 10, width: 30, height: 30)
        self.addSubview(IV)
        
        label.frame = CGRect(x: 50, y: 10, width: 200, height: 20)
        self.addSubview(label)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func configCell(_ model: Model) {
        self.IV.image = UIImage.init(named: model.imagePath)
        self.label.text = model.title
        self.backgroundColor = UIColor.gray
    }

}
