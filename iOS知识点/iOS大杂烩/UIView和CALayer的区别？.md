## UIView和CALayer的区别？


UIView和CALayer的区别？

UIView 和 CALayer 都是 UI 操作的对象。两者都是 NSObject 的子类，发生在 UIView 上的操作本质上也发生在对应的 CALayer 上。
UIView 是 CALayer 用于交互的抽象。UIView 是 UIResponder 的子类（ UIResponder 是 NSObject 的子类），提供了很多 CALayer 所没有的交互上的接口，主要负责处理用户触发的种种操作。
CALayer 在图像和动画渲染上性能更好。这是因为 UIView 有冗余的交互接口，而且相比 CALayer 还有层级之分。CALayer 在无需处理交互时进行渲染可以节省大量时间。
CALayer的动画要通过逻辑树、动画树和显示树来实现


loadView是干嘛用的？

loadView用来自定义view，只要实现了这个方法，其他通过xib或storyboard创建的view都不会被加载 。


layoutIfNeeded、layoutSubviews和setNeedsLayout的区别？

layoutIfNeeded：方法调用后，在主线程对当前视图及其所有子视图立即强制更新布局。
layoutSubviews：方法只能重写，我们不能主动调用，在屏幕旋转、滑动或触摸界面、子视图修改时被系统自动调用，用来调整自定义视图的布局。
setNeedsLayout：方法与layoutIfNeeded相似，不同的是方法被调用后不会立即强制更新布局，而是在下一个布局周期进行更新。

 
