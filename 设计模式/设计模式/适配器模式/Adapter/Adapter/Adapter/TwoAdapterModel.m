
//
//  TwoAdapterModel.m
//  Adapter
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "TwoAdapterModel.h"

@interface TwoAdapterModel ()
@property (nonatomic,strong) NSDictionary*data;
@end

@implementation TwoAdapterModel
- (instancetype)initWithData:(NSDictionary *)dataDic
{
    self = [super init];
    if (self) {
        self.data = dataDic;
    }
    return self;
}

- (NSDictionary *)dealData{
    return self.data;
}
@end
