//
//  Model.swift
//  demo
//
//  Created by yunna on 2018/8/22.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit

class Model: NSObject {
    var reuseId: String!
    var imagePath: String!
    var title: String!
    
    init(reuseId:String,imagePath:String? = "",title:String? = "") {
    
        self.reuseId = reuseId
        self.imagePath = imagePath
        self.title = title
    }
    
    
}
