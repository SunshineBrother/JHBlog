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
 
 ### 1、ViewController 多种实例化方法
 
 先看一下 Demo 的文件结构，ViewController 为 A 控制器，TestViewController 为 B 控制器
 
  ![初始化](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/初始化.png)
 
 
 我们在`TestViewController`里面实现以下方法
 ```
 - (void)viewDidLoad {
    [super viewDidLoad];
    NSLog(@"%s",__func__);
 }
 
 - (instancetype)initWithCoder:(NSCoder *)coder
 {
    self = [super initWithCoder:coder];
    if (self) {
    NSLog(@"%s",__func__);
    }
    return self;
 }
 
 
 - (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        NSLog(@"%s",__func__);
        NSLog(@"NibName:%@-->bundle:%@",nibNameOrNil,nibBundleOrNil);
    }
    return self;
 }
 ```
 
 
 **1、不指定 xib 名称**
 
 ```
 -(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    TestViewController *vc = [[TestViewController alloc]initWithNibName:nil bundle:nil];
    [self.navigationController pushViewController:vc animated:YES];
 }
 ```
 
 如果我们不指定 xib 名称，loadView 就会加载与控制器同名的 xib (TestViewController.xib)，最终是这个样子的。
 
   ![TestViewController](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/TestViewController.png)
 
 打印结果
 ```
 2019-04-04 11:00:07.776131+0800 UIViewController的生命周期[1478:49312] -[TestViewController initWithNibName:bundle:]
 2019-04-04 11:00:07.776258+0800 UIViewController的生命周期[1478:49312] NibName:(null)-->bundle:(null)
 2019-04-04 11:00:07.780864+0800 UIViewController的生命周期[1478:49312] -[TestViewController viewDidLoad]

 ```
  
  **2、不指定 xib 名称2**
  
  我们先将 TestViewController.xib 这个文件删除掉，这个时候，我们再来运行程序，结果是这样的。
```
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    TestViewController *vc = [[TestViewController alloc]initWithNibName:nil bundle:nil];
    [self.navigationController pushViewController:vc animated:YES];
}
```
  
我们运行代码，会出现以下错误日志
```
reason: '-[UIViewController _loadViewFromNibNamed:bundle:] loaded the "TestView" nib but the view outlet was not set.'
```

这是因为里面有个默认的IBOutlet变量view,看一下后面有没有做关联，如果没有就拉到下面的View和视图做个关联。

![TestView](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/TestView.png)
  
 当没有指定 xib 名称，且没有与控制器同名的 xib 时，会加载前缀与控制器名相同而不带 Controller 的 xib (TestView.xib)。 
  
  
  **3、指定 xib 名称**
 ```
 -(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    TestViewController *vc = [[TestViewController alloc]initWithNibName:@"ATestController" bundle:nil];
    [self.navigationController pushViewController:vc animated:YES];
 }

 ```
 当我们指定了xib的名称，loadView方 法就会去加载对应的 xib (ATestController.xib)，最终是这个样子的。
 
![ATestController](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/ATestController.png)
 
 打印结果
 ```
 2019-04-04 11:04:54.255086+0800 UIViewController的生命周期[1570:54600] -[TestViewController initWithNibName:bundle:]
 2019-04-04 11:04:54.255207+0800 UIViewController的生命周期[1570:54600] NibName:ATestController-->bundle:(null)
 2019-04-04 11:04:54.264343+0800 UIViewController的生命周期[1570:54600] -[TestViewController viewDidLoad]

 ```
 
 **4、init**
 
 我们经常会用代码通过 init 手动创建一个 ViewController，如下：
 
 打印结果
 ```
 2019-04-04 11:40:33.242740+0800 UIViewController的生命周期[2241:93595] -[TestViewController initWithNibName:bundle:]
 2019-04-04 11:40:33.242848+0800 UIViewController的生命周期[2241:93595] NibName:(null)-->bundle:(null)
 2019-04-04 11:40:33.242915+0800 UIViewController的生命周期[2241:93595] -[TestViewController init]
 2019-04-04 11:40:33.246192+0800 UIViewController的生命周期[2241:93595] -[TestViewController viewDidLoad]

 ```
 
 其实本质还是调用了 `initWithNibName:bundle: `并且都传入了 nil，
 
 **5、storyboard 间接实例化(initWithCoder)**
 
 
 当你从 storyboard 初始化 ViewController 时，iOS 会使用 `initWithCoder`，而不是 `initWithNibName `来初始化这个 ViewController，然后那个 storyboard 会在自己内部生成一个 nib (storyboard 实例化 view / ViewController 时，会把 nib 的信息放在 Coder 中，调用 initWithCoder)。
 
 **注意**
  
 storyboard 加载的是控制器及控制器 view，而 xib 加载的仅仅只是控制器的 view 
 
 
 **awakeFromNib方法**
 
 `awakeFromNib`方法被调用时，所有视图的`outlet`和`action`已经连接，但还没有被确定。这个方法可以算作是和视图控制器的实例化配合在一起使用的，因为有些需要根据用户喜好来进行设置的内容，无法存在`storyboard`中，所以可以在`awakeFromNib`方法中被加载进来。
 
` awakeFromNib`方法在视图控制器的生命周期内只会被调用一次。因为它和视图控制器从`nib`文件中的解档密切相关，和`view`的关系却不大。
 
### loadView 
 
 
 这个方法中，要正式加载View了。首先我们得知道，控制器 view 是通过懒加载的方式进行加载的，即用到的时候再加载。永远不要主动调用这个方法。当我们用到控制器 view 时，就会调用控制器 view 的 get 方法，在 get 方法内部，首先判断 view 是否已经创建，如果已存在，则直接返回存在的 view，如果不存在，则调用控制器的 loadView 方法，在控制器没有被销毁的情况下，loadView 也可能会被执行多次。
 
 当 ViewController 有以下情况时都会在此方法中从 nib 文件加载 view ：
 - ViewController 是从 storyboard 中实例化的。
 - 通过 initWithNibName:bundle: 初始化。
 - 在 App Bundle 中有一个 nib 文件名称和本类名相同。
 
 符合以上三点时，也就不需要重写这个方法,否则你无法得到你想要的 nib 中的 view。
 如果这个 ViewController 与 nib 无关，你可以在这里手写 ViewController 的 view (这一步大概也可以在 viewDidLoad 里写，实际上我们也更常在 viewDidLoad 里写)。
 
 **是否需要调用 [super loadView]**
 
 loadView 方法的默认实现是这样：先寻找有关可用的 nib 文件的信息，根据这个信息来加载 nib 文件，如果没有有关 nib 文件的信息，默认实现会创建一个空白的 UIView 对象，然后让这个对象成为 controller 的主 view。
 
 所以，重写这个函数时，你也应该这么做。并把子类的 view 赋给 view 属性 (property) (你 create 的 view 必须是唯一的实例，并且不被其他任何 controller 共享)。
 如果你要进行进一步初始化你的 views，你应该在 viewDidLoad 函数中去做。在iOS 3.0 以及更高版本中，你应该重载 viewDidUnload 函数来释放任何对 view 的引用或者它里面的内容（子 view 等等）。
 
 回到关于 [super loadView] 的讨论中，如果我们的 ViewController 与 nib 有关，也就是说我们不需要重写 loadView 方法，也就不用关心 [super loadView]。而如果与 nib 无关，我们需要重写 loadView 方法，而 [super loadView] 根据上面的解释就会生成一个空白的 view，这恐怕并不能满足我们的需求，所以调用也没有多大意义。
 
 
 ### ViewController加载View过程
 
 ![加载View](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/加载View.png)
 
 从图中可以看到，在 view 加载过程中首先会调用 loadView 方法，在这个方法中主要完成一些关键 view 的初始化工作，比如 UINavigationViewController 和 UITabBarController 等容器类的 ViewController；接下来就是加载 view，加载成功后，会接着调用 viewDidLoad 方法，这里要记住的一点是，在 loadView 之前，是没有 view 的，也就是说，在这之前，view 还没有被初始化。完成 viewDidLoad 方法后，ViewController 里面就成功的加载 view了，如上图右下角所示。
 
 **死循环**
 
 若 loadView 没有加载 view，即为 nil，viewDidLoad 会一直调用 loadView 加载 view，因此构成了死循环，程序即卡死，所以我们常在 ViewDidLoad 里创建 view。
 
  
  ### ViewController卸载View过程
 
  ![卸载View](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/卸载View.png)
 
 
 从图中可以看到，当系统发出内存警告时，会调用 didReceiveMemoeryWarning 方法，如果当前有能被释放的 view，系统会调用 viewWillUnload 方法来释放 view，完成后调用 viewDidUnload方法，至此，view 就被卸载了。此时原本指向 view 的变量要被置为 nil，具体操作是在 viewDidUnload 方法中调用 self.myButton = nil。
 
 ### viewDidLoad
 
 loadView方法执行完之后，就会执行viewDidLoad方法。此时整个视图层次(view hierarchy)已经被放到内存中。
 
 无论是从nib文件加载，还是通过纯代码编写界面，viewDidLoad方法都会执行。我们可以重写这个方法，对通过nib文件加载的view做一些其他的初始化工作。比如可以移除一些视图，修改约束，加载数据等。
 
 viewDidLoad 方法，该方法与loadView 方法一样，也有可能被执行多次。在开发中，我们可能从未遇到过执行多次的情况，那什么时候会执行多次呢？
 
 比如 A 控制器 push 出 B 控制器，此时，窗口显示的是 B 控制器的 view，此时如果收到内存警告，我们一般会将 A 控制器中没用的变量及 view 销毁掉，之后当我们从 B 控制器 pop 到 A 控制器时，就会再次执行A控制器的 loadView 方法与 viewDidLoad 方法。
 
 
 ### viewWillAppear && viewDidAppear
 
 viewWillAppear 总是在 viewDidLoad 之后被调用，但不是立即，当你只是引用了属性 view，却没有立即把 view 添加到任何已经展示的视图上时，viewWillAppear 不会被调用，这在 view 被外部引用时，就会发生。当然，随着 ViewController 的多次推入，多次进入子页面后返回，该方法会被多次调用。与 viewDidLoad 不同，调用该方法就说明控制器一定会显示。
 
 
 **锁屏之后会被调用吗？**
 
 不会。viewWillAppear 关注的是 view 在层次中的显示与消失，锁屏并没有改变 App 本身的层次
 
 **Window叠加后，会被调用吗？**
 
 不会。同锁屏时的原因类似，叠加 Window 并没有改变 ViewController 所在 Window 的视图层次，换句话说，view 并没有被覆盖或删除 (相对于自己所在 Window)。
 
 如果控制器 A 被展示在另一个控制器 B 的 popover 中，那么控制器 B 不会调用该方法，直到控制器 A 清除。
 
 
 **viewWillAppear 与 viewDidAppear 之间发生了什么**
 
 以下两个方法将会被调用：
 ```
 - viewWillLayoutSubviews
 - viewDidLayoutSubviews
 ```
 
 - viewWillLayoutSubviews：该方法在通知控制器将要布局 view 的子控件时调用。每当视图的 bounds 改变，view 将调整其子控件位置。默认实现为空，可重写以在 view 布局子控件前做出改变。该方法调用时，AutoLayout 未起作用
 - viewDidLayoutSubviews：该方法在通知控制器已经布局 view 的子控件时调用。默认实现为空，可重写以在 view 布局子控件后做出改变。该方法调用时，AutoLayout 未起作用。
 
 ### didReceiveMemoryWarning && viewDidUnload (iOS6废除)

当系统内存不足时，首先 ViewController 的 didReceiveMemoryWarining 方法会被调用，而 didReceiveMemoryWarining 会判断当前 ViewController 的 view 是否显示在 window 上，如果没有显示在 window 上，则 didReceiveMemoryWarining 会自动将 ViewController 的 view 以及其所有子 view 全部销毁，然后调用 viewcontroller 的 viewdidunload 方法。如果当前 ViewController 的 view 显示在 window 上，则不销毁该 ViewController 的 view，当然，viewDidunload 也不会被调用了。

iOS 升级到 6.0 以后，不再支持 viewDidUnload 了。官方文档的解释是系统会自动控制大的 view 所占用的内存，其他小的 view 所占用的内存是极其微小的，不值得为了省内存而去清理然后在重新创建。如果你需要在内存警告的时候释放业务数据或者做些其他的特定处理，你可以实现  didReceiveMemoryWarning 这个函数。

 ```
 -(void)didReceiveMemoryWarning {
 [super didReceiveMemoryWarning];//即使没有显示在window上，也不会自动的将self.view释放。
 // Dispose of any resources that can be recreated.
 // 此处做兼容处理需要加上ios6.0的宏开关，保证是在6.0下使用的,6.0以前屏蔽以下代码，否则会在下面使用self.view时自动加载viewDidUnLoad
 if ([[UIDevice currentDevice].systemVersion floatValue] >= 6.0) {
 //需要注意的是self.isViewLoaded是必不可少的，其他方式访问视图会导致它加载 ，在WWDC视频也忽视这一点。
 if (self.isViewLoaded && !self.view.window) {// 是否是正在使用的视图
 //code
 self.view = nil;// 目的是再次进入时能够重新加载调用viewDidLoad函数。
 }
 }
 }
 ```
 
 
### dealloc
 
 当发出内存警告调用 viewDidUnload 方法时，只是释放了 view，并没有释放 ViewController，所以并不会调用 dealloc 方法。即 viewDidUnload 和 dealloc 方法并没有任何关系，dealloc 方法只会在 ViewController 被释放的时候调用。
 
 
### 多个 ViewControllers 跳转时的生命周期
 
**Push / Present** 
 
 当我们点击 push 的时候首先会加载下一个界面然后才会调用界面的消失方法。
 - init：ViewController2
 - loadView：ViewController2
 - viewDidLoad：ViewController2
 - viewWillDisappear：ViewController1 将要消失
 - viewWillAppear：ViewController2 将要出现
 - viewWillLayoutSubviews ViewController2
 - viewDidLayoutSubviews ViewController2
 - viewWillLayoutSubviews:ViewController1
 - viewDidLayoutSubviews:ViewController1
 - viewDidDisappear:ViewController1 完全消失
 - viewDidAppear:ViewController2 完全出现
 
 当在一个控制器内 Push / Present 新的控制器，原先的控制器并不会销毁，但会消失，因此调用了 viewWillDisappear 和 viewDidDisappear 方法。
 
 
 **Pop / Dismiss**
 
 如果控制器 A 被展示在另一个控制器 B 的 popover 中，那么控制器 B 不会调用 viewWillAppear 方法，直到控制器 A 清除。这时，控制器 B 会再一次出现，因此调用了其中的 viewWillAppear 和 viewDidAppear 方法
 
  
 
 **参考**

[iOS开发笔记（九）：UIViewController的生命周期](https://juejin.im/post/5a706cf05188257323357286)


[iOS程序执行顺序和UIViewController 的生命周期(整理)](https://www.jianshu.com/p/d60b388b19f5)

[UIViewController的生命周期](https://bestswifter.com/uiviewlifetime/)
