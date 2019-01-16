//
//  main.m
//  外观模式
//
//  Created by yunna on 2019/1/16.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FundFacade.h"
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        FundFacade *facade = [FundFacade new];
        //买入
        [facade buyStock];
        //卖出
        [facade sellStock];
         
        
      
    }
    return 0;
}
