//
//  HandlerRaise.h
//  责任链模式
//
//  Created by yunna on 2019/1/19.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HandlerRaise : NSObject

@property(strong,nonatomic)HandlerRaise *handler;
- (void)ApplayForFee:(NSInteger)fee;
@end

NS_ASSUME_NONNULL_END
