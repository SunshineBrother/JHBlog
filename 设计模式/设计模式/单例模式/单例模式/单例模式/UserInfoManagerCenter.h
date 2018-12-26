//
//  UserInfoManagerCenter.h
//  单例模式
//
//  Created by yunna on 2018/12/26.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface UserInfoManagerCenter : NSObject

+ (instancetype)sharedInstance;

@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSNumber *age;


@end

NS_ASSUME_NONNULL_END
