//
//  Builder.m
//  创建者模式
//
//  Created by yunna on 2019/1/7.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "Builder.h"

@implementation Builder
/**
 *  构建所有部件
 */
- (void)buildAllParts{
    
    //创建所有部件
    [self.design build];
    [self.construction build];
    
    //组装产品
    [self.design DesignDrawings];
    [self.construction Construction];
    
    //出来产品
    NSLog(@"造出来房子了");
    
}

 
@end



