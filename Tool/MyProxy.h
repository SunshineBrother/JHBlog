//
//  MyProxy.h
//  定时器
//
//  Created by yunna on 2018/11/13.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyProxy : NSProxy
+ (instancetype)proxyWithTarget:(id)target;
@property (weak, nonatomic) id target;
@end
