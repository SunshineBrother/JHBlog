//
//  groupBonusDecorator.m
//  装饰者模式
//
//  Created by Mia on 16/12/14.
//  Copyright © 2016年 Mia. All rights reserved.
//

#import "groupBonusDecorator.h"

@implementation groupBonusDecorator
-(NSInteger)calculateSalary:(NSInteger)monthSales sumSales:(NSInteger)sumSales{
    NSInteger salary = [self.components calculateSalary:monthSales sumSales:sumSales];
    NSInteger bonus = 100000 * 0.01;
    NSLog(@"团队奖金：%zd", bonus);
    return salary += bonus;
}
@end
