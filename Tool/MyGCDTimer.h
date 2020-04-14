//
//  MyGCDTimer.h
//  定时器
//
//  Created by yunna on 2018/11/13.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyGCDTimer : NSObject

+ (NSString *)execTask:(void(^)(void))task
                 start:(NSTimeInterval)start
              interval:(NSTimeInterval)interval
               repeats:(BOOL)repeats
                 async:(BOOL)async;

+ (NSString *)execTask:(id)target
              selector:(SEL)selector
                 start:(NSTimeInterval)start
              interval:(NSTimeInterval)interval
               repeats:(BOOL)repeats
                 async:(BOOL)async;

+ (void)cancelTask:(NSString *)name;
@end
