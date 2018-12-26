//
//  FactoryCell.h
//  简单工厂
//
//  Created by yunna on 2018/12/25.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface FactoryCell : UITableViewCell
+ (UITableViewCell *)configUI:(NSInteger)tag withTableView:(UITableView *)tableView;
@end

NS_ASSUME_NONNULL_END
