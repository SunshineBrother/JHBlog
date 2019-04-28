//
//  IGListController.swift
//  MyTableView
//
//  Created by yunna on 2019/4/25.
//  Copyright © 2019年 yunna. All rights reserved.
//

import UIKit
import IGListKit
class IGListController: UIViewController {
    
    let collectionView: UICollectionView = {
        let flow = UICollectionViewFlowLayout()
        let collectionView = UICollectionView(frame: CGRect.zero, collectionViewLayout: flow)
        collectionView.backgroundColor = UIColor.groupTableViewBackground
        return collectionView
    }()
    //存放数据的数组，数据模型需要实现ListDiffable协议，主要实现判等，具体是什么后面再说
    var objects: [ListDiffable] = [ListDiffable]()
    lazy var adapter: ListAdapter = {
        let adapter = ListAdapter(updater: ListAdapterUpdater(), viewController: self)
        return adapter
    }()
    
   
 
    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor.white
        self.navigationItem.title = "复杂列表"
        
        
        view.addSubview(collectionView)
        adapter.collectionView = collectionView
        adapter.dataSource = self
        collectionView.frame = view.bounds
        
        
        //加载数据
        loadData()
    }
    
   
    
    
    //加载数据
    func loadData() {
        
        adapter.performUpdates(animated: true, completion: nil)
    }
    
 
}


extension IGListController : ListAdapterDataSource {
    func objects(for listAdapter: ListAdapter) -> [ListDiffable] {
        return objects
    }
    
    func listAdapter(_ listAdapter: ListAdapter, sectionControllerFor object: Any) -> ListSectionController {
        return UserInfoController()
    }
    
    func emptyView(for listAdapter: ListAdapter) -> UIView? {
        return nil
    }
}
