//
//  BuilderProtocol.h
//  BuilderPattern
//
//  Created by YouXianMing on 15/10/18.
//  Copyright © 2015年 YouXianMing. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol BuilderProtocol <NSObject>

@required
/**
 *  构建对象
 *
 *  @return 返回构建的对象
 */
- (id)build;

@end
