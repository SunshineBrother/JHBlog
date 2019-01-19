//
//  PresidentHandler.m
//  责任链模式
//
//  Created by yunna on 2019/1/19.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "PresidentHandler.h"

@implementation PresidentHandler
- (void)ApplayForFee:(NSInteger)fee{
    NSLog(@"总裁审批，已经到达了最顶端");
}
@end
