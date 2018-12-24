//
//  main.m
//  简单工厂0
//
//  Created by yunna on 2018/12/24.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PhoneFactory.h"
#import "IPhone.h"
#import "MIPhone.h"
#import "HWPhone.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        PhoneFactory *Factory = [PhoneFactory new];
        IPhone *phone = (IPhone *)[Factory sellPhone:@"IPhone"];
        [phone sellPhone];
    }
    return 0;
}
