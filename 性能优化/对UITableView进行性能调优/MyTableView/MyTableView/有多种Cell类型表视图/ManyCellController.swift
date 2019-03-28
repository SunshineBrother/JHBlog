//
//  ManyCellController.swift
//  UITableView架构
//
//  Created by yunna on 2019/3/16.
//  Copyright © 2019年 yunna. All rights reserved.
//

import UIKit

class ManyCellController: UIViewController {
    var tableView:UITableView!
    let viewModel = ProfileViewModel()
    override func viewDidLoad() {
        super.viewDidLoad()
        tableView = UITableView(frame: self.view.bounds)
        self.view.addSubview(tableView)
        
        tableView?.dataSource = viewModel
        
        tableView?.estimatedRowHeight = 100
        tableView?.rowHeight = UITableView.automaticDimension
        
        tableView?.register(AboutCell.nib, forCellReuseIdentifier: AboutCell.identifier)
        tableView?.register(NamePictureCell.nib, forCellReuseIdentifier: NamePictureCell.identifier)
        tableView?.register(FriendCell.nib, forCellReuseIdentifier: FriendCell.identifier)
        tableView?.register(AttributeCell.nib, forCellReuseIdentifier: AttributeCell.identifier)
        tableView?.register(EmailCell.nib, forCellReuseIdentifier: EmailCell.identifier)
    }
    

    

}
