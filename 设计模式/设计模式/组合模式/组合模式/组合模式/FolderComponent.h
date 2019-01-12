//
//  FolderComponent.h
//  组合模式
//
//  Created by yunna on 2019/1/12.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FolderComponent : NSObject
/**
 文件名称
 */
@property (nonatomic,copy) NSString *FolderName;
/**
 返回当前文件
 @param FolderName FolderName
 @return FolderName
 */
+ (FolderComponent *)getFolderNameWithFolderName:(NSString *)FolderName;
/**
 所有子文的集合
 */
@property (nonatomic, strong) NSMutableArray <FolderComponent *>  *childFolders;
/**
 添加子文件
 */
- (void)addChildFolder:(FolderComponent *)ChildFolder;
/**
 移除子文件
 */
- (void)removeChildFolder:(FolderComponent *)ChildFolder;
/**
 获取第几个编号的子节点
 */
- (FolderComponent *)childFolderAtIndex:(NSInteger)index;
/**
 打印所有子文件
 */
- (void)printAllChildFolder;


@end

NS_ASSUME_NONNULL_END
