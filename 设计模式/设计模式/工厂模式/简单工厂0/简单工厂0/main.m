//
//  main.m
//  简单工厂0
//
//  Created by yunna on 2018/12/24.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PhoneFactory.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        PhoneFactory *phone = [PhoneFactory new];
        [phone sellPhone:@"IPone"];
    }
    return 0;
}
