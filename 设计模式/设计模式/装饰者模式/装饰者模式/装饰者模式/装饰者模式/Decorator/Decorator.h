//
//  Decorator.h
//  装饰者模式
//
//  Created by yunna on 2019/1/15.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "PeopleComponent.h"

NS_ASSUME_NONNULL_BEGIN

@interface Decorator : PeopleComponent
@property(strong,nonatomic)PeopleComponent *components;
- (instancetype)initWithComponet:(PeopleComponent *)component;
@end

NS_ASSUME_NONNULL_END
