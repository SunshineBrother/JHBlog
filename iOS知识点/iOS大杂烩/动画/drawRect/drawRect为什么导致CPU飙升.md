## drawRect为什么导致CPU飙升

### drawRect介绍

> `drawRect`是`UIView`类的一个方法，在`drawRect`中所调用的重绘功能是基于`Quartz 2D`实现的，`Quartz 2D`是一个二维图形绘制引擎，支持`iOS`环境和`Mac OS X`环境。利用`UIKit`框架提供的控件，我们能实现一些简单的UI界面，但是，有些UI界面比较复杂，用普通的UI控件无法实现，或者实现效果不佳，这时可以利用`Quartz 2D`技术将控件内部的结构画出来，自定义所需控件，这也是`Quartz 2D`框架在iOS开发中一个很重要的价值。

 **drawRect的使用过程**

在view的drawRect方法中，利用Quartz 2D提供的API绘制图形的步骤：
- 1、新建一个view，继承自UIView，并重写drawRect方法；
- 2、在drawRect方法中，获取图形上下文；
- 3、绘图操作；
- 4、渲染。


重绘操作仍然在`drawRect`方法中完成，但是苹果不建议直接调用`drawRect`方法，当然如果你强直直接调用此方法，当然是没有效果的。苹果要求我们调用UIView类中的`setNeedsDisplay`方法，则程序会自动调用`drawRect`方法进行重绘。（调用`setNeedsDisplay`会自动调用`drawRect`）。 

在UIView中,重写`drawRect: (CGRect) aRect`方法,可以自己定义想要画的图案.且此方法一般情况下只会画一次.也就是说这个`drawRect`方法一般情况下只会被掉用一次. 当某些情况下想要手动重画这个View,只需要掉用`[self setNeedsDisplay]`方法即可.
 
**drawRect调用场景**

- 视图第一次显示的时候会调用。这个是由系统自动调用的，主要是在`UIViewController`中`loadView`和`viewDidLoad`方法调用之后；
 - 如果在`UIView`初始化时没有设置`rect`大小，将直接导致`drawRect`不被自动调用
 - 该方法在调用`sizeThatFits`后被调用,所以可以先调用`sizeToFit`计算出`size`,然后系统自动调用`drawRect:`方法；
- 通过设置`contentMode`属性值为`UIViewContentModeRedraw`,那么将在每次设置或更改`frame`的时候自动调用`drawRect:`;
- 直接调用`setNeedsDisplay`，或者`setNeedsDisplayInRect:`触发`drawRect:`，但是有个前提条件是rect不能为0;


**drawRect使用注意事项**

- 如果子类直接继承自UIView,则在drawRect 方法中不需要调用super方法。若子类继承自其他View类则需要调用super方法以实现重绘
- 若使用UIView绘图，只能在`drawRect:`方法中获取绘制视图的`contextRef`。在其他方法中获取的`contextRef`都是不生效的；
- `drawRect:`方法不能手动调用，需要调用实例方法`setNeedsDisplay`或者`setNeedsDisplayInRect`,让系统自动调用该方法；
- 若使用`CALayer`绘图，只能在`drawInContext :`绘制，或者在`delegate`方法中进行绘制，然后调用`setNeedDisplay`方法实现最终的绘制；


**何为CGContext**

`Quartz 2D`是`CoreGraphics`框架的一部分，因此其中的相关类及方法都是以`CG`为前缀。在`drawRect`重绘过程中最常用的就是`CGContext`类。`CGContext`又叫图形上下文，相当于一块画板，以堆栈形式存放，只有在当前`context`上绘图才有效。iOS又分多种图形上下文，其中UIView自带提供的在drawRect方法中通过 `UIGraphicsGetCurrentContext`获取，还有专门为图片处理的`context`，还有`pdf`的`context`等等均有特定的获取方法

 
 #### drawRect导致的内存飙升
 

在 iOS 系统中所有显示的视图都是从基类UIView继承而来的，同时`UIView`负责接收用户交互。 但是实际上你所看到的视图内容，包括图形等，都是由`UIView`的一个实例图层属性来绘制和渲染的，那就是`CALayer`。

`CALayer`类的概念与`UIView`非常类似，它也具有树形的层级关系，并且可以包含图片文本、背景色等。它与`UIView`最大的不同在于它不能响应用户交互，可以说它根本就不知道响应链的存在，它的 API 虽然提供了 “某点是否在图层范围内的方法”，但是它并不具有响应的能力。

在每一个`UIView`实例当中，都有一个默认的支持图层，`UIView`负责创建并且管理这个图层。实际上这个`CALayer`图层才是真正用来在屏幕上显示的，`UIView`仅仅是对它的一层封装，实现了`CALayer`的`delegate`，提供了处理事件交互的具体功能，还有动画底层方法的高级 API。

可以说`CALayer`是`UIView`的内部实现细节。

脑补了这么多，它与今天的主题`drawRect`有何关系呢？别着急，我们既然已经确定`CALayer`才是最终显示到屏幕上的，只要顺藤摸瓜，即可分析清楚。`CALayer`其实也只是 iOS 当中一个普通的类，它也并不能直接渲染到屏幕上，因为屏幕上你所看到的东西，其实都是一张张图片。而为什么我们能看到`CALayer`的内容呢，是因为`CALayer`内部有一个`contents`属性。`contents`默认可以传一个id类型的对象，但是只有你传`CGImage`的时候，它才能够正常显示在屏幕上。 所以最终我们的图形渲染落点落在`contents`身上如图。

`contents`也被称为寄宿图，除了给它赋值`CGImage`之外，我们也可以直接对它进行绘制，绘制的方法正是这次问题的关键，通过继承`UIView`并实现`-drawRect:`方法即可自定义绘制。`-drawRect: `方法没有默认的实现，因为对`UIView`来说，寄宿图并不是必须的，`UIView`不关心绘制的内容。如果`UIView`检测到`-drawRect:`方法被调用了，它就会为视图分配一个寄宿图，这个寄宿图的像素尺寸等于视图大小乘以`contentsScale`(这个属性与屏幕分辨率有关，我们的画板程序在不同模拟器下呈现的内存用量不同也是因为它) 的值。

那么回到我们的画板程序，当画板从屏幕上出现的时候，因为重写了-`drawRect:`方法，`-drawRect :`方法就会自动调用。 生成一张寄宿图后，方法里面的代码利用Core Graphics去绘制 n 条黑色的线，然后内容就会缓存起来，等待下次你调用`-setNeedsDisplay`时再进行更新。

画板视图的`-drawRect:`方法的背后实际上都是底层的CALayer进行了重绘和保存中间产生的图片，`CALayer的delegate`属性默认实现了`CALayerDelegate`协议，当它需要内容信息的时候会调用协议中的方法来拿。当画板视图重绘时，因为它的支持图层CALayer的代理就是画板视图本身，所以支持图层会请求画板视图给它一个寄宿图来显示，它此刻会调用：

```
 - (void)displayLayer:(CALayer *)layer;
```

如果画板视图实现了这个方法，就可以拿到layer来直接设置contents寄宿图，如果这个方法没有实现，支持图层CALayer会尝试调用：
```
 - (void)drawLayer:(CALayer *)layer inContext:(CGContextRef)ctx;
```

这个方法调用之前，`CALayer`创建了一个合适尺寸的空寄宿图（尺寸由bounds和contentsScale决定）和一个`Core Graphics`的绘制上下文环境，为绘制寄宿图做准备，它作为`ctx`参数传入。在这一步生成的空寄宿图内存是相当巨大的，它就是本次内存问题的关键，一旦你实现了`CALayerDelegate`协议中的`-drawLayer:inContext:`方法或者UIView中的`-drawRect:`方法（其实就是前者的包装方法），图层就创建了一个绘制上下文，这个上下文需要的内存可从这个公式得出：图层宽*图层高*4 字节，宽高的单位均为像素。而我们的画板程序因为要支持像猿题库一样两指挪动的效果，我们开辟的画板大小为：

```
_myDrawer = [[BHBMyDrawer alloc] initWithFrame:
CGRectMake(0, 0, SCREEN_SIZE.width*5, SCREEN_SIZE.height*2)];

```

我们的画板程序的画板视图它在iPhone6s plus机器上的上下文内存量就是 1920*2*1080*5*4 字节， 相当于79MB内存，图层每次重绘的时候都需要重新抹掉内存然后重新分配。它就是我们画板程序内存暴增的真正原因。

最终我们将内存暴增的原因找出来了，那么我们有没有合理的解决方案呢？

我认为最合理的办法处理类似于画板这样画线条的需求直接用专有图层CAShapeLayer。让我们看看它是什么：

CAShapeLayer是一个通过矢量图形而不是bitmap来绘制的图层子类。用CGPath来定义想要绘制的图形，CAShapeLayer会自动渲染。它可以完美替代我们的直接使用Core Graphics绘制layer，对比之下使用CAShapeLayer有以下优点：

渲染快速。CAShapeLayer 使用了硬件加速，绘制同一图形会比用 Core Graphics 快很多。

高效使用内存。一个 CAShapeLayer 不需要像普通 CALayer 一样创建一个寄宿图形，所以无论有多大，都不会占用太多的内存。

不会被图层边界剪裁掉。

不会出现像素化。

所以最终我们的画板程序使用CAShapeLayer来实现线条的绘制，性能非常稳定



[转载：内存恶鬼drawRect - 谈画图功能的内存优化](http://mp.weixin.qq.com/s?__biz=MjM5NTIyNTUyMQ==&mid=447105405&idx=1&sn=054dc54289a98e8a39f2b9386f4f620e&scene=23&srcid=0108RhyzhXk9wUwQvnW3cmZT#rd)





















































