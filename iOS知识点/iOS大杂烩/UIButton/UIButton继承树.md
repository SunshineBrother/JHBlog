 
### 继承树


UIButton -> UIControl -> UIView -> UIResponder -> NSObject

![UIKit](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/UIKit.png)


- NSObject：所有 Objective-C 对象的基类，封装了内存管理，消息的传递机制等底层逻辑。
- UIResponder：UIResponder 定义了响应和处理事件的接口。它是 UIApplication 和 UIView 的父类，而 UIView 则是 UIWindow 的父类。
	- 点击事件（Touche Events）
	- 手势事件（Motion Events）
	- 远程控制事件（Remote Control Events）
	- 重压事件（Press Events）（iOS 9.0 3D Touch）

- UIView：UIView 定义了一个屏幕上的矩形区域，以及管理这个区域内容的接口。UIView 提供了一个基本行为就是为这个矩形区域填充背景色（Background Color）。
- UIControl：UIControl 是 UIButton，UISwitch，UITextField 以及 UISegmentedControl 等类的父类。不要使用 UIControl 的实例，而是写 UIControl 的子类。UIControl 子类的主要工作就是将 UIResponder 收集到的复杂事件，变成简单的控制事件（UIControl Events）。而为了实现这个过程，UIControl 引入了 Target-Action 机制
- UIButton：UIButton 将 UIResponder 接受的 Events 处理成简单事件。
 


































