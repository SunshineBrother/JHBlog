//
//  commonMessage.m
//  桥接模式
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "commonMessage.h"
@implementation commonMessage
//发送消息
- (void)send:(NSString*)message{
    NSString *msg = [NSString stringWithFormat:@"普通消息：%@",message];
    [self.messageIm sendMessage:msg];
}
@end
