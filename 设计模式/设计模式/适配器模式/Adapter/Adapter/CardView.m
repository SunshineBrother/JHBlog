//
//  CardView.m
//  Adapter
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "CardView.h"
@interface CardView ()

@property (nonatomic, strong) UILabel  *nameLabel;
@property (nonatomic, strong) UIView   *lineView;
@property (nonatomic, strong) UILabel  *phoneNumberLabel;

@end
@implementation CardView


#pragma mark - 初始化
- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setup];
    }
    return self;
}

- (void)setup {
    
    self.backgroundColor     = [UIColor whiteColor];
    self.layer.borderWidth   = 0.5f;
    self.layer.shadowOpacity = 0.5f;
    self.layer.shadowOffset  = CGSizeMake(5, 5);
    self.layer.shadowRadius  = 1.f;
    self.layer.shadowColor   = [UIColor grayColor].CGColor;
    
    
    self.nameLabel      = [[UILabel alloc] initWithFrame:CGRectMake(15, 10, 150, 25)];
    self.nameLabel.font = [UIFont fontWithName:@"Avenir-Light" size:20.f];
    [self addSubview:self.nameLabel];
    
    
    self.lineView                 = [[UIView alloc] initWithFrame:CGRectMake(0, 45, 200, 5)];
    [self addSubview:self.lineView];
    
    
    self.phoneNumberLabel               = [[UILabel alloc] initWithFrame:CGRectMake(41, 105, 150, 20)];
    self.phoneNumberLabel.textAlignment = NSTextAlignmentRight;
    self.phoneNumberLabel.font          = [UIFont fontWithName:@"AvenirNext-UltraLightItalic" size:16.f];
    [self addSubview:self.phoneNumberLabel];
}



//赋值
- (void)loadData:(id<AdapterProtocol>)data{
    NSDictionary *dic = [data dealData];
    self.nameLabel.text         = dic[@"name"];
    self.phoneNumberLabel.text  = dic[@"phone"];
}


@end
