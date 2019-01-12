//
//  FolderComponent.m
//  组合模式
//
//  Created by yunna on 2019/1/12.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import "FolderComponent.h"

@implementation FolderComponent
 
- (instancetype)init
{
    self = [super init];
    if (self) {
        self.childFolders = [NSMutableArray new];
    }
    return self;
}


+ (FolderComponent *)getFolderNameWithFolderName:(NSString *)FolderName{
    FolderComponent *folder = [[FolderComponent alloc]init];
    folder.FolderName = FolderName;
    return folder;
}

/**
 添加子文件
 */
- (void)addChildFolder:(FolderComponent *)ChildFolder{
    [self.childFolders addObject:ChildFolder];
}

/**
 移除子文件
 */
- (void)removeChildFolder:(FolderComponent *)ChildFolder{
    [self.childFolders removeObject:ChildFolder];
}

/**
 获取第几个编号的子节点
 */
- (FolderComponent *)childFolderAtIndex:(NSInteger)index{
    if (index > self.childFolders.count) {
        return nil;
    }
    return self.childFolders[index];
}

- (void)printAllChildFolder{
    for (FolderComponent *component in self.childFolders) {
        NSLog(@"%@",component);
    }
    for (FolderComponent *component in self.childFolders) {
        [component printAllChildFolder];
    }
}

- (NSString *)description{
    return [NSString stringWithFormat:@"【名称】%@", self.FolderName];
}

@end
