//
//  Decorator.m
//  装饰者模式
//
//  Created by yunna on 2019/1/15.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "Decorator.h"

@implementation Decorator
- (instancetype)initWithComponet:(PeopleComponent *)component
{
    self = [super init];
    if (self) {
        self.components = component;
    }
    return self;
}

- (NSInteger)calculateSalary:(NSInteger)monthSales sumSales:(NSInteger)sumSales{
    return 0;
}
@end
