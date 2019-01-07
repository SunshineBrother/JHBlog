//
//  B_Design.m
//  创建者模式
//
//  Created by yunna on 2019/1/7.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "B_Design.h"

@implementation B_Design
- (void)DesignDrawings{
    NSLog(@"设计图纸是小洋楼");
}

- (id)build{
    return self;
}
@end
