//
//  PhoneFactory.m
//  简单工厂0
//
//  Created by yunna on 2018/12/24.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "PhoneFactory.h"
 
@implementation PhoneFactory

- (void)sellPhone{
    @throw ([NSException exceptionWithName:@"继承错误" reason:@"子类必须重写该方法" userInfo:nil]);
}
@end
