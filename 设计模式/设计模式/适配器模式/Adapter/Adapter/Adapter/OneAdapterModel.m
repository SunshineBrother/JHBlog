//
//  OneAdapterModel.m
//  Adapter
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "OneAdapterModel.h"
@interface OneAdapterModel ()
@property (nonatomic,strong) NSDictionary*data;
@end
@implementation OneAdapterModel

- (instancetype)initWithData:(NSArray *)dataArr
{
    self = [super init];
    if (self) {
        self.data = @{@"name":dataArr[0],
                      @"phone":dataArr[1]
                      };
    }
    return self;
}

- (NSDictionary *)dealData{
    return self.data;
}

@end
