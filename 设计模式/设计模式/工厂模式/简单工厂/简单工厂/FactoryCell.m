//
//  FactoryCell.m
//  简单工厂
//
//  Created by yunna on 2018/12/25.
//  Copyright © 2018年 yunna. All rights reserved.
//

#import "FactoryCell.h"
#import "OneCell.h"
#import "TwoCell.h"
#import "ThreeCell.h"
@implementation FactoryCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

+ (UITableViewCell *)configUI:(NSInteger)tag withTableView:(UITableView *)tableView{
    if (tag == 0) {
        
        OneCell *cell = [tableView dequeueReusableCellWithIdentifier:@"OneCell"];
        [cell configUI];  //不同样式的Cell所展示的UI各不相同，由于是Demo样例，这里并未配置相关数据源
        return cell;
    }else if (tag == 1) {
        
        TwoCell *cell = [tableView dequeueReusableCellWithIdentifier:@"TwoCell"];
        [cell configUI];
        return cell;
    }else if (tag == 2) {
        
        ThreeCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ThreeCell"];
        [cell configUI];
        return cell;
    }
    
    return nil;
}





@end
