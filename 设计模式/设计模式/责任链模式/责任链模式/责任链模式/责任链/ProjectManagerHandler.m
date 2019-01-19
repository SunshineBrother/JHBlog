//
//  ProjectManagerHandler.m
//  责任链模式
//
//  Created by yunna on 2019/1/19.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "ProjectManagerHandler.h"

@implementation ProjectManagerHandler
- (void)ApplayForFee:(NSInteger)fee{
    if (fee < 500) {
        NSLog(@"项目经理审批");
    }else{
        NSLog(@"项目经理处理不了，需要向上申请");
        [self.handler ApplayForFee:fee];
    }
}
@end
