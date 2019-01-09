//
//  CardView.h
//  Adapter
//
//  Created by yunna on 2019/1/9.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AdapterProtocol.h"
NS_ASSUME_NONNULL_BEGIN

@interface CardView : UIView

//赋值
- (void)loadData:(id<AdapterProtocol>)data;
 
@end

NS_ASSUME_NONNULL_END
