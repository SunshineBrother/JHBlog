//
//  DepManagerHandler.m
//  责任链模式
//
//  Created by yunna on 2019/1/19.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "DepManagerHandler.h"

@implementation DepManagerHandler
- (void)ApplayForFee:(NSInteger)fee{
    if (fee < 1000) {
        NSLog(@"部门经理审批");
    }else{
        NSLog(@"部门经理处理不了，需要向上申请");
        [self.handler ApplayForFee:fee];
    }
}
@end
