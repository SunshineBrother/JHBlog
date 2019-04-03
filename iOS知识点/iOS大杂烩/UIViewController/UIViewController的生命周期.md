## UIViewController的生命周期 
 
 
 ![生命周期](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/生命周期.png)
 
 **视图的生命历程**
 
 - 1、`initWithCoder:`或`initWithNibName:Bundle` 首先从归档文件中加载`UIViewController`对象。即使是纯代码，也会把nil作为参数传给后者。
 - 2、`awakeFromNib` 作为第一个方法的助手，方法处理一些额外的设置
 - 3、`loadView`创建或加载一个view并把它赋值给`UIViewController`的`view`属性
 - 4、`viewDidLoad` 此时整个视图层次(`view hierarchy`)已经放到内存中，可以移除一些视图，修改约束，加载数据等
 - 5、`viewWillAppear` 视图加载完成，并即将显示在屏幕上。还没设置动画，可以改变当前屏幕方向或状态栏的风格等
 - 6、`viewWillLayoutSubviews`即将开始子视图位置布局
 - 7、`viewDidLayoutSubviews`用于通知视图的位置布局已经完成
 - 8、`viewDidAppear`视图已经展示在屏幕上，可以对视图做一些关于展示效果方面的修改。
 - 9、`viewWillDisappear`视图即将消失
 - 10、`viewDidDisappear`视图已经消失
 - 11、`dealloc`视图销毁的时候调用
 
 **总结**
 
 - 只有`init`系列的方法,如`initWithNibName`需要自己调用，其他方法如`loadView`和`awakeFromNib`则是系统自动调用 
 
 - 纯代码写视图布局时需要注意，要手动调用`loadView`方法，而且不要调用父类的`loadView`方法。纯代码和用IB的区别仅存在于`loadView`方法及其之前，编程时需要注意的也就是`loadView`方法。
 
 - 除了`initWithNibName`和`awakeFromNib`方法是处理视图控制器外，其他方法都是处理视图。这两个方法在视图控制器的生命周期里只会调用一次。
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 **参考**

[iOS开发笔记（九）：UIViewController的生命周期](https://juejin.im/post/5a706cf05188257323357286)


[iOS程序执行顺序和UIViewController 的生命周期(整理)](https://www.jianshu.com/p/d60b388b19f5)

[UIViewController的生命周期](https://bestswifter.com/uiviewlifetime/)
