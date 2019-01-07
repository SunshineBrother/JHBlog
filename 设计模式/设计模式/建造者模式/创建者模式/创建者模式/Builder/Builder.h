//
//  Builder.h
//  创建者模式
//
//  Created by yunna on 2019/1/7.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DesignProtocol.h"
#import "ConstructionProtocol.h"
#import "BuilderProtocol.h"
@interface Builder : NSObject
// 设计图纸
@property (nonatomic,strong) id<DesignProtocol,BuilderProtocol> design;
// 建筑队
@property (nonatomic,strong) id<ConstructionProtocol,BuilderProtocol> construction;
 
/**
 *  构建所有部件
 */
- (void)buildAllParts;


@end


