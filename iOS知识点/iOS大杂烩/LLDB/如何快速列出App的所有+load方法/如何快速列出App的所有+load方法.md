## 如何快速列出App的所有+load方法

点击一下Pause，然后输入
```
br s -r "\+\[.+ load\]$"
```
然后输入
```
br list
```

![load](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/LLDB/如何快速列出App的所有%2Bload方法/load.png)

```
br s -r "正则"
就是
breakpoint set -r "正则"
```

通过正则匹配符号设置断点

















