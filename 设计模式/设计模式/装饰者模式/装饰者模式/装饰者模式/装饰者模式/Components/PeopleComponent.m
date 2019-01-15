//
//  PeopleComponent.m
//  装饰者模式
//
//  Created by yunna on 2019/1/15.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "PeopleComponent.h"

@implementation PeopleComponent


- (NSInteger)calculateSalary:(NSInteger)monthSales  sumSales:(NSInteger)sumSales{
    return self.wage;
}


@end
