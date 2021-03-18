//
//  ViewController.m
//  Adapter
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "ViewController.h"
#import "CardView.h"
#import "OneAdapterModel.h"
#import "TwoAdapterModel.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    CardView *card = [[CardView alloc]initWithFrame:CGRectMake(0, 0, 200, 150)];
    card.center = self.view.center;
    [self.view addSubview:card];
    TwoAdapterModel *model = [[TwoAdapterModel alloc]initWithData:@{@"name":@"辉哥",@"phone":@"19999999999"}];
    [card loadData:model];
    
    
//    OneAdapterModel *model = [[OneAdapterModel alloc]initWithData:@[@"辉哥",@"19999999999"]];
//    [card loadData:model];
    
    
}


@end
