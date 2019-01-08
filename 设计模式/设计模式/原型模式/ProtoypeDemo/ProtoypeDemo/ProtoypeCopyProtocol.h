//
//  ProtoypeCopyProtocol.h
//  ProtoypeDemo
//
//  Created by YouXianMing on 15/8/16.
//  Copyright (c) 2015年 YouXianMing. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ProtoypeCopyProtocol <NSObject>

@required

/**
 *  复制自己
 *
 *  @return 返回一个拷贝样本
 */
- (id)clone;

@end
