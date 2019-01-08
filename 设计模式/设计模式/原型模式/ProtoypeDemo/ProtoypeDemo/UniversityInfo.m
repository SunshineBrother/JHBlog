//
//  UniversityInfo.m
//  ProtoypeDemo
//
//  Created by yunna on 2019/1/7.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "UniversityInfo.h"

@implementation UniversityInfo

- (id)clone{
    UniversityInfo * university = [[[self class] alloc]init];
    
    //完成复制信息
    university.university = self.university;
    university.major      = self.major;
    university.startYear  = self.startYear;
    university.endYear    = self.endYear;
     
    return university;
}

@end
