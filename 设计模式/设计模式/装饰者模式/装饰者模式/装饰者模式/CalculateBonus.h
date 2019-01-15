//
//  CalculateBonus.h
//  装饰者模式
//
//  Created by yunna on 2019/1/15.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CalculateBonus : NSObject
//当月奖金
+ (NSInteger)monthBonus:(NSInteger)monthSales;
//累积奖金
+ (NSInteger)sumBonus:(NSInteger)sumSales;
//团队奖金
+ (NSInteger)groupBonus:(NSInteger)groupMoney;


@end

NS_ASSUME_NONNULL_END
