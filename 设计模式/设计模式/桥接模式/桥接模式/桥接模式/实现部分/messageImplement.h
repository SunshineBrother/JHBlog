//
//  messageImplement.h
//  桥接模式
//
//  Created by Mia on 16/12/15.
//  Copyright © 2016年 Mia. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol messageImplement <NSObject>

- (void)sendMessage:(NSString *)message;

@end
