//
//  PeopleComponent.h
//  装饰者模式
//
//  Created by yunna on 2019/1/15.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PeopleComponent : NSObject
///基础工资
@property (nonatomic,assign) NSInteger wage;
- (NSInteger)calculateSalary:(NSInteger)monthSales  sumSales:(NSInteger)sumSales;
@end

NS_ASSUME_NONNULL_END
