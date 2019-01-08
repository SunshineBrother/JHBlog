//
//  main.m
//  ProtoypeDemo
//
//  Created by yunna on 2019/1/7.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Resume.h"
#import "UniversityInfo.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
       
        UniversityInfo *info = [[UniversityInfo alloc] init];
        info.university      = @"清华大学";
        info.major           = @"计算机";
        info.startYear       = @"2010-03-01";
        info.endYear         = @"2014-10-10";
        
        //小明简历
        Resume *resume1    = [[Resume alloc] init];
        resume1.name       = @"小明";
        resume1.sex        = 1;
        resume1.age        = 25;
        resume1.university = [info clone];
    
        
        //小红简历
        Resume *resume2    = [[Resume alloc] init];
        resume2.name       = @"小红";
        resume2.sex        = 0;
        resume2.age        = 26;
        resume2.university = [info clone];
        
        NSLog(@"\ninfo==============:%@\nresume1.university:%@\nresume2.university:%@",info,resume1.university,resume2.university);
         
    }
    return 0;
}
