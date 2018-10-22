## armv7,armv7s,arm64,i386,x86_64

平时项目开发中，可能使用第三方提供的静态库.a，如果.a提供方技术不成熟，使用的时候就会出现问题，例如：
```
在真机上编译报错：No architectures to compile for (ONLY_ACTIVE_ARCH=YES, active arch=x86_64, VALID_ARCHS=i386).

在模拟器上编译报错：No architectures to compile for (ONLY_ACTIVE_ARCH=YES, active arch=armv7s, VALID_ARCHS=armv7 armv6).
```
要解决以上问题，就要了解一下Apple移动设备处理器指令集相关的一些细节知识
 

### 几个重要概念

iOS测试分为模拟器测试和真机测试，处理器分为32位处理器，和64位处理器，

模拟器32位处理器测试需要i386架构，（iphone5,iphone5s以下的模拟器）
模拟器64位处理器测试需要x86_64架构，(iphone6以上的模拟器)
真机32位处理器需要armv7,或者armv7s架构，（iphone4真机/armv7,      ipnone5,iphone5s真机/armv7s）
真机64位处理器需要arm64架构。(iphone6,iphone6p以上的真机)

```
project -> target -> building setting -> Arhitectures 设置
```
#### ARM

ARM处理器，特点是体积小、低功耗、低成本、高性能，所以几乎所有手机处理器都基于ARM，在嵌入式系统中应用广泛

armv6｜armv7｜armv7s｜arm64都是ARM处理器的指令集，这些指令集都是向下兼容的，例如armv7指令集兼容armv6，只是使用armv6的时候无法发挥出其性能，无法使用armv7的新特性，从而会导致程序执行效率没那么高


#### Architectures

指定工程被编译成可支持哪些指令集类型，而支持的指令集越多，就会编译出包含多个指令集代码的数据包，对应生成二进制包就越大，也就是ipa包会变大


#### Valid Architectures

限制可能被支持的指令集的范围，也就是Xcode编译出来的二进制包类型最终从这些类型产生，而编译出哪种指令集的包，将由Architectures与Valid Architectures（因此这个不能为空）的交集来确定


#### Build Active Architecture Only

指定是否只对当前连接设备所支持的指令集编译
当其值设置为YES，这个属性设置为yes，是为了debug的时候编译速度更快，它只编译当前的architecture版本，而设置为no时，会编译所有的版本。 所以，一般debug的时候可以选择设置为yes，release的时候要改为no，以适应不同设备。

 















