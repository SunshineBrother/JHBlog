//
//  messageEmail.m
//  桥接模式
//
//  Created by Mia on 16/12/15.
//  Copyright © 2016年 Mia. All rights reserved.
//

#import "messageEmail.h"

@implementation messageEmail
-(void)sendMessage:(NSString *)message{
    NSLog(@"使用Email方式发送消息，消息类型：%@", message);
}
@end
