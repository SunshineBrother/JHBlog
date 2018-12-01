//
//  ViewController.m
//  MVVM
//
//  Created by yunna on 2018/12/1.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "ViewController.h"
#import "ViewModel.h"
@interface ViewController ()
@property (strong, nonatomic) ViewModel *viewModel;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
   
    
    self.viewModel = [[ViewModel alloc]initWithController:self];
    
}


@end
