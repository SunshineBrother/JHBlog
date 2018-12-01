//
//  ViewController.m
//  MVP
//
//  Created by yunna on 2018/12/1.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "ViewController.h"
#import "APPPresenter.h"
@interface ViewController ()
@property (strong, nonatomic) APPPresenter *presenter;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.presenter = [[APPPresenter alloc]initWithController:self];
    
}


@end
