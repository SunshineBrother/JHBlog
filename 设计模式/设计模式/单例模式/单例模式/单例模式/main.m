//
//  main.m
//  单例模式
//
//  Created by yunna on 2018/12/26.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UserInfoManagerCenter.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        
        
        UserInfoManagerCenter *manager = [[UserInfoManagerCenter alloc]init];
        UserInfoManagerCenter *manager1 = [UserInfoManagerCenter sharedInstance];
        UserInfoManagerCenter *manager2 = [manager copy];
        UserInfoManagerCenter *manager3 = [manager mutableCopy];
        NSLog(@"\n%@\n%@\n%@\n%@\n",manager,manager1,manager2,manager3);
        
        
    }
    return 0;
}
