 ## 更新cocoapod
 
 
 总结下来，要想成功升级cocoapods需要一个正确的操作流程和命令语句。
 
 1、更新gem：sudo gem update --system
 
 2、删除gem源：gem sources --remove https://ruby.taobao.org/
 
 3、修改gem源：gem sources -a https://gems.ruby-china.org
 
 4、查看gem源是否是最新的：gem sources -l
 
 5、升级cocoapods：sudo gem install -n /usr/local/bin cocoapods --pre
 
 6、查看升级后的cocoapods版本：pod --version



[CocoaPods 历险 - 总览](https://www.desgard.com/cocoapods-1/)
