//
//  APPView.h
//  MVC
//
//  Created by yunna on 2018/12/1.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class APPView;
@protocol MyAppViewDelegate <NSObject>
@optional
- (void)appViewDidClick:(APPView *)appView;
@end

@interface APPView : UIView

@property (nonatomic,strong) UIImageView *iconView;
@property (nonatomic,strong) UILabel *nameLabel;

@property (weak, nonatomic) id<MyAppViewDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
