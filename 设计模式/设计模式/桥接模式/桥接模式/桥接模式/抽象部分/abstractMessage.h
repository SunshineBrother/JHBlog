//
//  abstractMessage.h
//  桥接模式
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "messageImplement.h"
NS_ASSUME_NONNULL_BEGIN

@interface abstractMessage : NSObject

@property(strong,nonatomic)id<messageImplement> messageIm;
//初始化
- (instancetype)initWithImplement:(id<messageImplement>)implement;
//发送消息
- (void)send:(NSString*)message;

@end

NS_ASSUME_NONNULL_END
