//
//  main.m
//  装饰者模式
//
//  Created by yunna on 2019/1/15.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CalculateBonus.h"
#import "PeopleComponent.h"
#import "groupBonusDecorator.h"
#import "monthBonusDecorator.h"
#import "sumBonusDecatorator.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
       
        //基本工资，被装饰对象
        PeopleComponent *c1 = [PeopleComponent new];
        c1.wage = 8000;
        //装饰器
        Decorator *d1 = [[monthBonusDecorator alloc]initWithComponet:c1];
        Decorator *d2 = [[sumBonusDecatorator alloc]initWithComponet:d1];
        NSInteger salary1 = [d2 calculateSalary:10000 sumSales:12212];
        NSLog(@"\n奖金组合方式：当月销售奖金 + 累积销售奖金 \n 总工资 = %zd", salary1);
        
    }
    return 0;
}

void test (){
    //甲的总工资 = 基本工资 + 当月销售奖金 + 环比奖金
    NSInteger A_MonthBonus = [CalculateBonus monthBonus:4000];
    NSInteger A_SumBonus   = [CalculateBonus sumBonus:5000];
    NSInteger A_AllMoney   = 3000 + A_MonthBonus + A_SumBonus;
    NSLog(@"销售奖金：%ld，环比奖金：%ld，甲的总工资：%ld",A_MonthBonus,A_SumBonus,A_AllMoney);
    
    //乙的工资 = 基本工资 + 环比奖金
    NSInteger B_SumBonus = [CalculateBonus sumBonus:5000];
    NSInteger B_AllMoney = 3000 + B_SumBonus;
    NSLog(@"环比奖金：%ld,乙的总工资：%ld",B_SumBonus,B_AllMoney);
    
    //丙的工资 = 基本工资 + 环比奖金 + 团队奖金
    NSInteger C_SumBonus   = [CalculateBonus sumBonus:5000];
    NSInteger C_GroupBonus = [CalculateBonus groupBonus:10000];
    NSInteger C_AllMoney   = 3000 + C_SumBonus + C_GroupBonus;
    NSLog(@"环比奖金：%ld,团队奖金：%ld,丙的总工资：%ld",C_SumBonus,C_GroupBonus,C_AllMoney);
}
