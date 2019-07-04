# 给工程添加忽略文件.gitignore 

目前iOS 项目 主要忽略 临时文件、配置文件、或者生成文件等，在不同开发端这些文件会大有不同，如果 git add .把这些文件都push到远程， 就会造成不同开发端频繁改动和提交的问题

- 1 .  在工程目录下
-  2 . `touch .gitignore`   在目录下生成.gitignore  文件
-  3 . `open .gitignore`   打开.gitignore （txt）文件 。去GitHub搜索gitignore  找到对应语言的内容，然后把内容通过文本编辑器或者Sublime粘贴到.gitignore文件里面
-  4 . 写入忽略目录


但是如果你需要忽略的文件已经存在在远端中了，那么你需要将远端中的文件删除掉才可以

```
git rm -r --cached .
git add .
git commit -m 'update .gitignore'
```




这里iOS 项目，使用CocosPods 框架管理工具会生成Podfile、Podfile.lock、Pods文件夹和.xcworkspace四个。其中

![image.png](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/忽略文件/image.png)



以上除Podfile外，其它三个文件都不是必须提交的。
"其中Pods目录没必要提交，里面的文件都是根据Podfile描述的依赖库的配置信息下载和生成的文件。
因为CocoaPods支持语义化版本号，所以需要Podfile.lock文件记住当前使用的版本，当然这个文件也不是必须。不过提交这个的好处是，可以提醒团队里面的人，依赖库版本已经更新”。


### 到gitignore.io去选择自定义配置

[github忽略文件网址](https://github.com/github/gitignore)


在[gitignore.io](https://link.jianshu.com/?t=https://www.gitignore.io/)输入侧你需要配置的语言，会帮助你自动生成一份配置。比如，输入侧`Objective-C``Swift`会帮助你生成下面的配置。

```
# Xcode
.DS_Store
*/build/*
*.pbxuser
!default.pbxuser
*.mode1v3
!default.mode1v3
*.mode2v3
!default.mode2v3
*.perspectivev3
!default.perspectivev3
xcuserdata
profile
*.moved-aside
DerivedData
.idea/
*.hmap
*.xccheckout
*.xcworkspace
!default.xcworkspace

#CocoaPods
Pods
!Podfile
!Podfile.lock
```




### Git 忽略规则匹配语法

在 .gitignore 文件中，每一行的忽略规则的语法如下：

- 空格不匹配任意文件，可作为分隔符，可用反斜杠转义
- `#` 开头的模式标识注释，可以使用反斜杠进行转义
- `! `开头的模式标识否定，该文件将会再次被包含，如果排除了该文件的父级目录，则使用` ! `也不会再次被包含。可以使用反斜杠进行转义
- `/ `结束的模式只匹配文件夹以及在该文件夹路径下的内容，但是不匹配该文件。`/` 开始的模式匹配项目跟目录。如果一个模式不包含斜杠，则它匹配相对于当前 .gitignore 文件路径的内容，如果该模式不在 .gitignore 文件中，则相对于项目根目录
- `**`匹配多级目录，可在开始，中间，结束
- `?`通用匹配单个字符
- `[]`通用匹配单个字符列表















































