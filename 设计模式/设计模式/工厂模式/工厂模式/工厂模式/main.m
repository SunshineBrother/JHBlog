//
//  main.m
//  工厂模式
//
//  Created by yunna on 2018/12/26.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HWPhone.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        HWPhone *phone = [HWPhone new];
        [phone sellPhone];
        
    }
    return 0;
}
