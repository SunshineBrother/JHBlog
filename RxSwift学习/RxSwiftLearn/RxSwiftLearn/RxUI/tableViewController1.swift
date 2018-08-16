//
//  tableViewController1.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/16.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class tableViewController1: UIViewController {
    var tableView:UITableView!
    let disposeBag = DisposeBag()

    override func viewDidLoad() {
        super.viewDidLoad()

        
        //创建表格
        self.tableView = UITableView(frame: self.view.frame)
        //创建从用的单元格
        self.tableView.register(UITableViewCell.self, forCellReuseIdentifier: "cell")
        self.view.addSubview(self.tableView)
        
        //初始化数据
        let items = Observable.just([
            "标题1",
            "标题2",
            "标题3",
            "标题4"
            ])
        
        //设置单元格 其实就是对 cellForRowAt 的封装
        items.bind(to: self.tableView.rx.items){ (tableView, row, element) in
            let cell = tableView.dequeueReusableCell(withIdentifier: "cell")!
            cell.textLabel?.text = "\(row)：\(element)"
            return cell
            }
            .disposed(by: disposeBag)
        
        //单元格选中事件响应
        //获取选中项的索引
        let itemSelect = tableView.rx.itemSelected
        itemSelect.subscribe(onNext: { indexPath in
            print("选中项的indexPath为：\(indexPath)")
        }).disposed(by: disposeBag)
        
        //获取选中项的内容
        let modelSelect = tableView.rx.modelSelected(String.self)
        modelSelect.subscribe(onNext: {item in
             print(item)
        }).disposed(by: disposeBag)
        
        //当然同时获取选中项的索引及内容也是可以的：
        Observable.zip(tableView.rx.itemSelected, tableView.rx.modelSelected(String.self))
            .bind { indexPath, item in
                print("选中项的indexPath为：\(indexPath)")
                print("选中项的标题为：\(item)")
            }
            .disposed(by: disposeBag)
        
        //单元格取消选中事件响应
        //获取被取消选中项的索引
        tableView.rx.itemDeselected.subscribe({ indexPath in
            print("被取消选中项的indexPath为：\(indexPath)")
        }).disposed(by: disposeBag)
        
        //获取被取消选中项的内容
        tableView.rx.modelDeselected(String.self).subscribe(onNext: { item in
            print("被取消选中项的的标题为：\(item)")
        }).disposed(by: disposeBag)
        
        
        
        //获取删除项的索引
        tableView.rx.itemDeleted.subscribe(onNext: { indexPath in
            print("删除项的indexPath为：\(indexPath)")
        }).disposed(by: disposeBag)
        
        //获取删除项的内容
        tableView.rx.modelDeleted(String.self).subscribe(onNext: {item in
            print("删除项的的标题为：\(item)")
        }).disposed(by: disposeBag)
        
        
        
    }

    
    
    
    
    
    
    
    
    
}































































































