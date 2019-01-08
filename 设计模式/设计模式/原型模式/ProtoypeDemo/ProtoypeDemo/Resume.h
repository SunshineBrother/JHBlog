//
//  Resume.h
//  ProtoypeDemo
//
//  Created by yunna on 2019/1/7.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UniversityInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface Resume : NSObject
//姓名
@property (nonatomic,copy) NSString *name;
//性别
@property (nonatomic,assign) NSInteger sex;
//年龄
@property (nonatomic,assign) NSInteger age;
//学历
@property (nonatomic,strong) UniversityInfo *university;

@end

NS_ASSUME_NONNULL_END
