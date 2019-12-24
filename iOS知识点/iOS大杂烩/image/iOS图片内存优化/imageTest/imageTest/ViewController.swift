//
//  ViewController.swift
//  imageTest
//
//  Created by yunna on 2019/12/20.
//  Copyright © 2019 yunna. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        
 
    }


    
    @IBAction func buttonEvent(_ sender: Any) {
        let image = UIImage(named: "shengdanlaoren")
        let iv = UIImageView(frame: CGRect(x: 0, y: 0, width: 100, height: 100))
        iv.image = image
        iv.center = self.view.center
        self.view.addSubview(iv)
    }
    
    
    
}

