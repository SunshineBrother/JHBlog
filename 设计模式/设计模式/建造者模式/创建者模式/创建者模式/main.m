//
//  main.m
//  创建者模式
//
//  Created by yunna on 2018/12/26.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Builder.h"
#import "A_Construction.h"
#import "B_Construction.h"
#import "C_Construction.h"
#import "A_Design.h"
#import "B_Design.h"
#import "C_Design.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // 创建组装者
        Builder *builder = [[Builder alloc] init];
        //指定具体部件
        builder.design = [A_Design new];
        builder.construction = [B_Construction new];
        // 构建所有的部件
        [builder buildAllParts];
      
        
    }
    return 0;
}
