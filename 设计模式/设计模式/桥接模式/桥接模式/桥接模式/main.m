//
//  main.m
//  桥接模式
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "commonMessage.h"
#import "abstractMessage.h"
#import "messageEmail.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        messageEmail *email  = [messageEmail new];
        abstractMessage *msg = [[commonMessage alloc]initWithImplement:email];
        [msg send:@"桥接模式测试"];

    }
    return 0;
}
