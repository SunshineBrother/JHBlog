//
//  monthBonusDecorator.m
//  装饰者模式
//
//  Created by Mia on 16/12/14.
//  Copyright © 2016年 Mia. All rights reserved.
//

#import "monthBonusDecorator.h"

@implementation monthBonusDecorator

-(NSInteger)calculateSalary:(NSInteger)monthSales sumSales:(NSInteger)sumSales{
    NSInteger salary = [self.components calculateSalary:monthSales sumSales:sumSales];
    NSInteger bonus = monthSales * 0.03;
    NSLog(@"当月销售奖金：%zd", bonus);
    return salary += bonus;
}
@end
