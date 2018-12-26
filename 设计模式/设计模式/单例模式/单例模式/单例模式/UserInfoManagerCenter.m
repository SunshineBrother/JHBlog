//
//  UserInfoManagerCenter.m
//  单例模式
//
//  Created by yunna on 2018/12/26.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "UserInfoManagerCenter.h"

@implementation UserInfoManagerCenter

+ (instancetype)sharedInstance
{
    static UserInfoManagerCenter *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[super allocWithZone:NULL] init] ;
    }) ;
    return sharedInstance ;
}

+ (id)allocWithZone:(struct _NSZone *)zone
{
    return [UserInfoManagerCenter sharedInstance] ;
}

- (id)copyWithZone:(struct _NSZone *)zone
{
    return [UserInfoManagerCenter sharedInstance];
}

- (id)mutableCopyWithZone:(NSZone *)zone
{
    return [UserInfoManagerCenter sharedInstance];
}








@end
