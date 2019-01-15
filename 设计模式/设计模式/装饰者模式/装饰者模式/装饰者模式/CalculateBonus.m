//
//  CalculateBonus.m
//  装饰者模式
//
//  Created by yunna on 2019/1/15.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "CalculateBonus.h"

@implementation CalculateBonus

//当月奖金
+ (NSInteger)monthBonus:(NSInteger)monthSales{
    return monthSales * 0.003;
}

//累积奖金
+ (NSInteger)sumBonus:(NSInteger)sumSales{
    return  sumSales * 0.001;
}
//团队奖金
+ (NSInteger)groupBonus:(NSInteger)groupMoney{
    //简单起见，团队的销售总额设置为100000
    return groupMoney * 0.01;
}


@end
