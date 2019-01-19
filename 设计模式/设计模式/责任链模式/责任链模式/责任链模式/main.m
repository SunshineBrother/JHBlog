//
//  main.m
//  责任链模式
//
//  Created by yunna on 2019/1/18.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HandlerRaise.h"
#import "ProjectManagerHandler.h"
#import "DepManagerHandler.h"
#import "GeneralManagerHandler.h"
#import "PresidentHandler.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        
        ProjectManagerHandler *handler1 = [ProjectManagerHandler new];
        DepManagerHandler * handler2    = [DepManagerHandler new];
        GeneralManagerHandler *handler3 = [GeneralManagerHandler new];
        ProjectManagerHandler *handler4 = [ProjectManagerHandler new];
        //责任链
        handler1.handler = handler2;
        handler2.handler = handler3;
        handler3.handler = handler4;
        //处理事务
        [handler1 ApplayForFee:1500];
        
        
        
        
    }
    return 0;
}
