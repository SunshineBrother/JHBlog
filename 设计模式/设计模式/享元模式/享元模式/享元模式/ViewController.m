//
//  ViewController.m
//  享元模式
//
//  Created by yunna on 2019/1/17.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "ViewController.h"
#define JHScreenWidth          [[UIScreen mainScreen] bounds].size.width
#define JHScreenHeight         [[UIScreen mainScreen] bounds].size.height
@interface ViewController ()
@property (nonatomic,strong) NSMutableDictionary *dataDic;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    for (NSInteger i = 0; i < 10000; i++) {
        CGFloat x = (arc4random() % (NSInteger)JHScreenWidth);
        CGFloat y = (arc4random() % (NSInteger)JHScreenHeight);
        UIImageView *iv = [[UIImageView alloc]initWithFrame:CGRectMake(x, y, 50, 50)];
        iv.image = [self FlyWeightFlowerViewWithType:arc4random()%5];
        [self.view addSubview:iv];

    }
}



/**
 未使用享元模式
 
 */
- (UIImage *)flowerViewWithType:(NSInteger)type
{
    
    UIImage *flowerImage;
    
    switch (type)
    {
        case 0:
            flowerImage = [UIImage imageNamed:@"OneFlowes"];
            break;
        case 1:
            flowerImage = [UIImage imageNamed:@"TwoFlowes"];
            break;
        case 2:
            flowerImage = [UIImage imageNamed:@"ThreeFlowes"];
            break;
        case 3:
            flowerImage = [UIImage imageNamed:@"FourFlowes"];
            break;
        case 4:
            flowerImage = [UIImage imageNamed:@"FiveFlowes"];
            break;
        default:
            break;
    }
    NSLog(@"==%ld:%p==",type,flowerImage);
    return flowerImage;
}


- (UIImage *)FlyWeightFlowerViewWithType:(NSInteger)type
{
    UIImage *flowerImage;
    
    switch (type)
    {
        case 0:
            flowerImage = [self obtainImage:@"OneFlowes"];
            break;
        case 1:
            flowerImage = [self obtainImage:@"TwoFlowes"];
            break;
        case 2:
            flowerImage = [self obtainImage:@"ThreeFlowes"];
            break;
        case 3:
            flowerImage = [self obtainImage:@"FourFlowes"];
            break;
        case 4:
            flowerImage = [self obtainImage:@"FiveFlowes"];
            break;
        default:
            break;
    }
    
    return flowerImage;
}

- (UIImage *)obtainImage:(NSString *)imageName{
    UIImage *flowerImage;
    //先看看字典中有没有改image
    UIImage *image = self.dataDic[imageName];
    if (image == nil) {
        flowerImage = [UIImage imageNamed:imageName];
        NSLog(@"创建新的image：%@",imageName);
        [self.dataDic setObject:flowerImage forKey:imageName];
    }else{
        flowerImage = image;
    }
    return flowerImage;
}







@end
