## Mac系统占用空间大、空间不够、查看系统文件大小分布

[文章转载：Mac系统占用空间大、空间不够、查看系统文件大小分布](https://blog.csdn.net/u011423056/article/details/79450845)


**背景：**

最近老提示空间不够，这就比较讨厌了，为什么存储空间这么快就花完了。。。

![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/1.png)

如图，256的空间，就剩下几个G了，其中最大头的系统占用：160G，占比60%多，我勒个擦。。。

正常情况下：我们可以点击管理，进入到系统磁盘优化界面：


![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/2.png)


这种适用于简单的文件占用分析，一般我们能够通过 清理文稿 和 回收箱 来解决空间不够的问题。
- 1、清空回收站。
- 2、在文稿里，按文件大小排序，删除不需要的文件。
- 3、对于GarageBand，这个是系统上的模拟乐器，一般都使用不到。

清除方法：
```
rm -rf /Library/Application\ Support/GarageBand
rm -rf /Library/Application\ Support/Logic
rm -rf /Library/Audio/Apple\ Loops
```


不过，对于罪魁祸首，系统的160G，我们怎么才能知道她的内部存储分布呢？

### 正文

呐、下面就是重点了：关于如何查看系统的文件占用详情。

**一、首先打开终端，输入**

```
du -sh *
```

这个命令用来查看根目录下，所有文件的大小分布，如图所示：



![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/3.png)

其中，我们很容易能看到每个文件的大小占比，快速定位到最大占比的文件：Library

**二、输入命令，进入到Library文件路径**

```
cd ~/Library
```


![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/4.png)

然后，查看Library下的所有文件大小分布。

输入：
```
du -d 1 -h
```


![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/5.png)


很容易我们可以找到最大的文件：／Developer

当然，其他的文件大小，我们也都能看到，一目了然。

**三、到这里，我们基本就能知道下面的套路了，我们可以继续往下查看**

比如，我这里继续进入到Developer文件，再查看他的每个子文件大小：

![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/6.png)

基本，查看个两三层，就基本能知道大概的原因了，我这边由于是程序猿，所以Xcode是根本原因，占了系统160G的一半大小。

到这里为止，如果你也是程序猿，有兴趣的，可以继续看；如果没有兴趣的可以直接跳第四步。



![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/7.png)


![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/8.png)


基本这就到底了，大概的空间占用分布从上面几张图，也基本有数了。



以上是讲如何查看及分析文件，如果你是iOS程序猿，这边附上几个清理步骤（清理Xcode缓存）

经过测试，我暂时发现这几个文件可以适当清理下


![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/9.png)

1  ./Archives  这个文件存储的是你所有的历史打包文件，你可以将一些历史的包删掉，最近的如果不放心可以先留着，不过全部删除也是没问题的，但是，如果你删除了，我们Xcode打包上传界面就看不到东西了（如下图所示，该界面的东西就没了）

![](https://github.com/SunshineBrother/JHBlog/blob/master/工具/Mac系统占用空间大/10.png)


2  ./DerivedData 这个文件大家应该比较熟悉了，存储的是所有项目的一些缓存数据、包括编译缓存文件等等，这个文件是可以全部清理的，当然，你也可以保留一些最近的项目，先暂时清理历史项目的缓存。

3  ./iOS DeviceSupport 这个文件里面存储的是xcode对手机各个版本的支持文件，这里如果你的项目不再需要支持iOS6、iOS7等，可以先把里面的基于iOS6、iOS7的支持文件清除

4 ./Device Logs

此文件夹存储了devices链接真机后下载的真机log，包含crashlog。可以全部删除，建议备份。

**四、经过第三步的层层分析，我们基本能知道了每个文件的大小分布，也能找到一些不需要用的垃圾文件，其中大多以缓存文件居多，大家可以适当进行清理～**



1、移除对旧设备的支持
影响：可重新生成；再连接旧设备调试时，会重新自动生成。我移除了4.3.2, 5.0, 5.1等版本的设备支持。
路径：~/Library/Developer/Xcode/iOS DeviceSupport

2、移除旧版本的模拟器支持
影响：不可恢复；如果需要旧版本的模拟器，就需要重新下载了。我移除了4.3.2, 5.0, 5.1等旧版本的模拟器。
路径：~/Library/Application Support/iPhone Simulator

3、移除模拟器的临时文件
影响：可重新生成；如果需要保留较新版本的模拟器，但tmp文件夹很大。放心删吧，tmp文件夹里的内容是不重要的。在iOS Device中，存储空间不足时，tmp文件夹是可能被清空的。
路径：~/Library/Application Support/iPhone Simulator/6.1/tmp (以iOS Simulator 6.1为例)

4、移除模拟器中安装的Apps
影响：不可恢复；对应的模拟器中安装的Apps被清空了，如果不需要就删了吧。
路径：~/Library/Application Support/iPhone Simulator/6.1/Applications (以iOS Simulator 6.1为例)

5、移除Archives
影响：不可恢复；Adhoc或者App Store版本会被删除。建议备份dSYM文件夹
路径：~/Library/Developer/Xcode/Archives

6、移除DerivedData
影响：可重新生成；会删除build生成的项目索引、build输出以及日志。重新打开项目时会重新生成，大的项目会耗费一些时间。
路径：~/Library/Developer/Xcode/DerivedData

7、移除旧的Docsets
影响：不可恢复；将删除旧的Docsets文档
路径：~/Library/Developer/Shared/Documentation/DocSets


8、真机log  Device Logs

影响：此文件夹存储了devices链接真机后下载的真机log，包含crashlog。可以全部删除，建议备份
路径：~/Library/Developer/Xcode/iOS Device Logs













