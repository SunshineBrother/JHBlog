//
//  UniversityInfo1.h
//  ProtoypeDemo
//
//  Created by yunna on 2019/1/8.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface UniversityInfo1 : NSObject<NSCopying,NSMutableCopying>

@property (nonatomic,copy) NSString *university;    //大学
@property (nonatomic,copy) NSString *major;         //专业
@property (nonatomic,copy) NSString *startYear;     //开始年份
@property (nonatomic,copy) NSString *endYear;       //结束年份

@end

NS_ASSUME_NONNULL_END
