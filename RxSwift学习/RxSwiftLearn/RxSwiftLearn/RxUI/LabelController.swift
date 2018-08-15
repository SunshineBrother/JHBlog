//
//  LabelController.swift
//  RxSwiftLearn
//
//  Created by yunna on 2018/8/15.
//  Copyright © 2018年 yunna. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
class LabelController: UIViewController {
    @IBOutlet weak var label1: UILabel!
    @IBOutlet weak var label2: UILabel!
    
    let disposeBag = DisposeBag()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        //创建一个计时器（每0.1秒发送一个索引数）
        let timer = Observable<Int>.interval(0.1, scheduler: MainScheduler.instance)
        
        timer.map{[weak self] _ in self?.transform()}
            .bind(to: label1.rx.text)
            .disposed(by: disposeBag)
        
        
        //将数据绑定到 attributedText 属性上（富文本）
        timer.map{[weak self] _ in self?.formatTimeInterval(text: (self?.transform())!)}
            .bind(to: label2.rx.attributedText)
            .disposed(by: disposeBag)
        
        
        
    }
    
    
    
    func transform() -> String{
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY-MM-dd HH:mm:ss"
        return dateFormatter.string(from: Date())
        
    }
    
    //将数字转成对应的富文本
    func formatTimeInterval(text: String) -> NSMutableAttributedString {
        //富文本设置
        let attributeString = NSMutableAttributedString(string: text)
        //从文本0开始6个字符字体HelveticaNeue-Bold,16号
        attributeString.addAttribute(NSAttributedStringKey.font,
                                     value: UIFont(name: "HelveticaNeue-Bold", size: 16)!,
                                     range: NSMakeRange(0, 10))
        //设置字体颜色
        attributeString.addAttribute(NSAttributedStringKey.foregroundColor,
                                     value: UIColor.white, range: NSMakeRange(0, 10))
        //设置文字背景颜色
        attributeString.addAttribute(NSAttributedStringKey.backgroundColor,
                                     value: UIColor.orange, range: NSMakeRange(0, 10))
        return attributeString
    }
}















