//
//  ViewModel.h
//  MVVM
//
//  Created by yunna on 2018/12/1.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ViewModel : NSObject
- (instancetype)initWithController:(UIViewController *)controller;
@end

NS_ASSUME_NONNULL_END
