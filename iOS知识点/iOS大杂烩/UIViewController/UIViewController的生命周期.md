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
 
 storyboard 加载的是控制器及控制器 view，而 xib 加载的仅仅只是控制器的 view。之所以这么说，我们结合控制器的 awakeFromNib 方法解释一下，顾名思义，当控制器从 nib 加载的时候就会调用这个方法，这个方法本身只是个信号、消息，是一个空方法 (即其默认实现为空)。
 
 storyboard 加载的是控制器及控制器 view，而 xib 加载的仅仅只是控制器的 view 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 **参考**

[iOS开发笔记（九）：UIViewController的生命周期](https://juejin.im/post/5a706cf05188257323357286)


[iOS程序执行顺序和UIViewController 的生命周期(整理)](https://www.jianshu.com/p/d60b388b19f5)

[UIViewController的生命周期](https://bestswifter.com/uiviewlifetime/)
