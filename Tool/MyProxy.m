//
//  MyProxy.m
//  定时器
//
//  Created by yunna on 2018/11/13.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "MyProxy.h"

@implementation MyProxy
+ (instancetype)proxyWithTarget:(id)target
{
    // NSProxy对象不需要调用init，因为它本来就没有init方法
    MyProxy *proxy = [MyProxy alloc];
    proxy.target = target;
    return proxy;
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel
{
    return [self.target methodSignatureForSelector:sel];
}

- (void)forwardInvocation:(NSInvocation *)invocation
{
    [invocation invokeWithTarget:self.target];
}

@end
