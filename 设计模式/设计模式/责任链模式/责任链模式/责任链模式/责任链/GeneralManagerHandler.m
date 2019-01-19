//
//  GeneralManagerHandler.m
//  责任链模式
//
//  Created by yunna on 2019/1/19.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "GeneralManagerHandler.h"

@implementation GeneralManagerHandler
- (void)ApplayForFee:(NSInteger)fee{
    if (fee < 2000) {
        NSLog(@"总经理审批");
    }else{
        NSLog(@"总经理处理不了，需要向上申请");
        [self.handler ApplayForFee:fee];
    }
}
@end
