//
//  C_Construction.h
//  创建者模式
//
//  Created by yunna on 2019/1/7.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ConstructionProtocol.h"
#import "BuilderProtocol.h"
NS_ASSUME_NONNULL_BEGIN

@interface C_Construction : NSObject<BuilderProtocol,ConstructionProtocol>

@end

NS_ASSUME_NONNULL_END
