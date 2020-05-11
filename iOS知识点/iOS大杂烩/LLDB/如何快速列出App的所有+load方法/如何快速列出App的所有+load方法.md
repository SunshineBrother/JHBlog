## 如何快速列出App的所有+load方法

点击一下Pause，然后输入
```
br s -r "\+\[.+ load\]$"
```
然后输入
```
br list
```

```
br s -r "正则"
就是
breakpoint set -r "正则"
```

通过正则匹配符号设置断点

















