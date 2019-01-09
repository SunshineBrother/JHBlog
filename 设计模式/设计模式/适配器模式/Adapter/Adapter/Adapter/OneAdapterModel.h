//
//  OneAdapterModel.h
//  Adapter
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AdapterProtocol.h"
NS_ASSUME_NONNULL_BEGIN

@interface OneAdapterModel : NSObject<AdapterProtocol>

- (instancetype)initWithData:(NSArray *)dataArr;

@end

NS_ASSUME_NONNULL_END
