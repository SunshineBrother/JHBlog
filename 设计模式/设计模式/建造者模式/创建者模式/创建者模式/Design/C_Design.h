//
//  C_Design.h
//  创建者模式
//
//  Created by yunna on 2019/1/7.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DesignProtocol.h"
#import "BuilderProtocol.h"
NS_ASSUME_NONNULL_BEGIN

@interface C_Design : NSObject<BuilderProtocol,DesignProtocol>

@end

NS_ASSUME_NONNULL_END
