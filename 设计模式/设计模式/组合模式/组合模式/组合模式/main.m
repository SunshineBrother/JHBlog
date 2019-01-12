//
//  main.m
//  组合模式
//
//  Created by yunna on 2019/1/12.
//  Copyright © 2019年 yunna. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FolderComponent.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
       
        //========赋值=======
        //根文件夹
        FolderComponent *rootFolder = [FolderComponent getFolderNameWithFolderName:@"📂根文件夹"];
        // 创建第一级子节点(一级文件夹、一级文件A，一级文件B，一级文件C)
        FolderComponent *oneFolder = [FolderComponent getFolderNameWithFolderName:@"📂一级文件夹"];
        [rootFolder addChildFolder:oneFolder];
        [rootFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃一级文件A"]];
         [rootFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃一级文件B"]];
         [rootFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃一级文件C"]];
        
        // 创建第二级子节点(二级文件夹、二级文件A，二级文件B，二级文件C)
        FolderComponent *twoFolder = [FolderComponent getFolderNameWithFolderName:@"📂二级文件夹"];
        [oneFolder addChildFolder:twoFolder];
        [oneFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃二级文件A"]];
        [oneFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃二级文件B"]];
        [oneFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃二级文件C"]];
        
        
        // 创建第3级子节点(三级文件夹、三级文件A，三级文件B，三级文件C)
        FolderComponent *threeFolder = [FolderComponent getFolderNameWithFolderName:@"📂三级文件夹"];
        [twoFolder addChildFolder:threeFolder];
        [twoFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃三级文件A"]];
        [twoFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃三级文件B"]];
        [twoFolder addChildFolder:[FolderComponent getFolderNameWithFolderName:@"📃三级文件C"]];
        
        
        //=======================================
        // 客户端操作
        // 操作一：打印所有
        [rootFolder printAllChildFolder];
        
        
        
        
        
        
        
    }
    return 0;
}
