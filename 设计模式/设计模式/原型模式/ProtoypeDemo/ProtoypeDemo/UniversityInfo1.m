//
//  UniversityInfo1.m
//  ProtoypeDemo
//
//  Created by yunna on 2019/1/8.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "UniversityInfo1.h"

@implementation UniversityInfo1

- (id)copyWithZone:(NSZone *)zone{
    UniversityInfo1 *info = [[UniversityInfo1 alloc]init];
    //完成复制信息
    info.university = self.university;
    info.major      = self.major;
    info.startYear  = self.startYear;
    info.endYear    = self.endYear;
    return info;
}


- (id)mutableCopyWithZone:(NSZone *)zone{
    UniversityInfo1 *info = [[UniversityInfo1 alloc]init];
    //完成复制信息
    info.university = self.university;
    info.major      = self.major;
    info.startYear  = self.startYear;
    info.endYear    = self.endYear;
    return info;
}



@end
