//
//  Raise.m
//  责任链模式
//
//  Created by yunna on 2019/1/19.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "Raise.h"

@implementation Raise
- (void)ApplayForFee:(NSInteger)fee{
    if (fee < 500) {
        NSLog(@"项目经理可以审批");
    }else if(fee < 1000){
        NSLog(@"部门经理审批");
    }else if(fee < 2000){
        NSLog(@"总经理审批");
    }else{
        NSLog(@"总裁审批");
    }
}
@end
