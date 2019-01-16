//
//  FundFacade.m
//  外观模式
//
//  Created by yunna on 2019/1/16.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "FundFacade.h"
#import "HWStock.h"
#import "XMStock.h"
#import "IPhoneStock.h"
@implementation FundFacade
///买股票
- (void)buyStock{
    HWStock *HW         = [HWStock new];
    XMStock *XM         = [XMStock new];
    IPhoneStock *IPhone = [IPhoneStock new];
 
    [HW buyStock];
    [XM buyStock];
    [IPhone buyStock];
    NSLog(@"==================");
}
///卖股票
- (void)sellStock{
    HWStock *HW         = [HWStock new];
    XMStock *XM         = [XMStock new];
    IPhoneStock *IPhone = [IPhoneStock new];
    
    [HW sellStock];
    [XM sellStock];
    [IPhone sellStock];
}
@end
