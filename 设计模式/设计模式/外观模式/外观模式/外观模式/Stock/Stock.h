//
//  Stock.h
//  外观模式
//
//  Created by yunna on 2019/1/16.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Stock : NSObject

///买股票
- (void)buyStock;
///卖股票
- (void)sellStock;

@end

NS_ASSUME_NONNULL_END
