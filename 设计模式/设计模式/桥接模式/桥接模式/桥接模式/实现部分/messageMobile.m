//
//  messageMobile.m
//  桥接模式
//
//  Created by Mia on 16/12/15.
//  Copyright © 2016年 Mia. All rights reserved.
//

#import "messageMobile.h"

@implementation messageMobile
-(void)sendMessage:(NSString *)message{
    NSLog(@"使用手机方式发送消息，消息内容：%@", message);
}
@end
