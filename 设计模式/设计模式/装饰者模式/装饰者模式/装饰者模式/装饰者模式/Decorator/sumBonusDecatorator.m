//
//  sumBonusDecatorator.m
//  装饰者模式
//
//  Created by Mia on 16/12/14.
//  Copyright © 2016年 Mia. All rights reserved.
//

#import "sumBonusDecatorator.h"

@implementation sumBonusDecatorator

-(NSInteger)calculateSalary:(NSInteger)monthSales sumSales:(NSInteger)sumSales{
    NSInteger salary = [self.components calculateSalary:monthSales sumSales:sumSales];
    NSInteger bonus = sumSales * 0.01;
    NSLog(@"累积销售奖金：%zd", bonus);
    return salary += bonus;
}

@end
