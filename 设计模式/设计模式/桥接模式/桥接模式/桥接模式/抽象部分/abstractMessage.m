//
//  abstractMessage.m
//  桥接模式
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "abstractMessage.h"

@implementation abstractMessage
- (instancetype)initWithImplement:(id<messageImplement>)implement
{
    self = [super init];
    if (self) {
        self.messageIm = implement;
    }
    return self;
}

//发送消息
- (void)send:(NSString*)message{
    
}
 
@end
