 ## 更新cocoapod
 
 
 总结下来，要想成功升级cocoapods需要一个正确的操作流程和命令语句。
 
 1、更新gem：sudo gem update --system
 
 2、删除gem源：gem sources --remove https://ruby.taobao.org/
 
 3、修改gem源：gem sources -a https://gems.ruby-china.org
 
 4、查看gem源是否是最新的：gem sources -l
 
 5、升级cocoapods：sudo gem install -n /usr/local/bin cocoapods --pre
 
 6、查看升级后的cocoapods版本：pod --version
 --------------------- 
 作者：番薯大佬 
 来源：CSDN 
 原文：https://blog.csdn.net/potato512/article/details/62235282 
 版权声明：本文为博主原创文章，转载请附上博文链接！
