//
//  HandlerRaise.m
//  责任链模式
//
//  Created by yunna on 2019/1/19.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "HandlerRaise.h"

@implementation HandlerRaise
- (void)ApplayForFee:(NSInteger)fee{
    if (self.handler) {
        [self.handler ApplayForFee:fee];
    }
}
@end
