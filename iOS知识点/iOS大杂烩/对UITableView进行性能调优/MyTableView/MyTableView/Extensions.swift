//
//  Extensions.swift
//  MyTableView
//
//  Created by yunna on 2019/4/25.
//  Copyright © 2019年 yunna. All rights reserved.
//

import UIKit

extension UICollectionViewCell {
    static var cellIdentifier: String {
        get {
            let a = NSStringFromClass(self)
            let className = a.split(separator: ".").last
            return String(className!)
        }
    }
}
