//
//  TwoAdapterModel.h
//  Adapter
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AdapterProtocol.h"
NS_ASSUME_NONNULL_BEGIN

@interface TwoAdapterModel : NSObject<AdapterProtocol>

- (instancetype)initWithData:(NSDictionary *)dataDic;


@end

NS_ASSUME_NONNULL_END
