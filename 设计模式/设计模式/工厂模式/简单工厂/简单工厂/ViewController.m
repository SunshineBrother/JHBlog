//
//  ViewController.m
//  简单工厂
//
//  Created by yunna on 2018/12/24.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "ViewController.h"
#import "FactoryCell.h"
#import "OneCell.h"
#import "TwoCell.h"
#import "ThreeCell.h"
@interface ViewController ()<UITableViewDelegate,UITableViewDataSource>
@property (nonatomic,strong) UITableView *tableview;
@property (nonatomic,strong) NSMutableArray *dataList;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
   
    self.tableview = [[UITableView alloc]initWithFrame:self.view.frame style:UITableViewStylePlain];
    self.tableview.delegate = self;
    self.tableview.dataSource = self;
    [self.view addSubview:self.tableview];
    
    
    
}


#pragma -- tableView代理事件 --

//返回指定组行数
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.dataList.count;
}
///注册cell
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    return [FactoryCell configUI:indexPath.row withTableView:tableView];
}



@end
