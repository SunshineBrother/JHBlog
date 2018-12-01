//
//  ViewController.m
//  MVC
//
//  Created by yunna on 2018/12/1.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "ViewController.h"
#import "APPView.h"
#import "APPModel.h"
@interface ViewController ()<MyAppViewDelegate>

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    //创建view
    APPView *app = [[APPView alloc]initWithFrame:CGRectMake(100, 100, 100, 150)];
    app.delegate = self;
    [self.view addSubview:app];
    
    //创建model
    APPModel *model = [[APPModel alloc]init];
    model.name = @"我是一片云";
    model.image = @"cloud";
    
    //赋值
    app.model = model;
}

#pragma mark -- view点击事件 --
- (void)appViewDidClick:(APPView *)appView{
    NSLog(@"点击了view");
}






@end














