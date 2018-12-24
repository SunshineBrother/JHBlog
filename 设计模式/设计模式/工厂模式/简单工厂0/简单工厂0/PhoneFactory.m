//
//  PhoneFactory.m
//  简单工厂0
//
//  Created by yunna on 2018/12/24.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "PhoneFactory.h"
#import "IPhone.h"
#import "MIPhone.h"
#import "HWPhone.h"
@implementation PhoneFactory

- (void)sellPhone:(NSString *)type{
    
    if ([type isEqualToString:@"IPone"]) {
        IPhone *phone = [IPhone new];
        [phone sellPhone];
    }else if ([type isEqualToString:@"MIPhone"]){
        MIPhone *phone = [MIPhone new];
        [phone sellPhone];
    }else if ([type isEqualToString:@"HWPone"]){
        HWPhone *phone = [HWPhone new];
        [phone sellPhone];
    }
    
}

@end
