//
//  UserInfoController.swift
//  MyTableView
//
//  Created by yunna on 2019/4/25.
//  Copyright © 2019年 yunna. All rights reserved.
//

import UIKit
import IGListKit

class UserInfoController: ListSectionController {

    var entry: UserInfoModel!
    
    override func numberOfItems() -> Int {
        return 1
    }
    
    override func sizeForItem(at index: Int) -> CGSize {
        let width: CGFloat! = collectionContext?.containerSize(for: self).width
        return CGSize(width: width, height: 80)
    }
    
    override func cellForItem(at index: Int) -> UICollectionViewCell {
        guard let cell = collectionContext?.dequeueReusableCell(withNibName: "UserInfoCell", bundle: nil, for: self, at: index) as? UserInfoCell else { fatalError() }
        cell.nameLabel.text = "测试：\(arc4random() % 100)"
        return UICollectionViewCell()
    }
    
    override func didUpdate(to object: Any) {
        entry = object as? UserInfoModel
    }
    
    override func didSelectItem(at index: Int) {}
    
}





