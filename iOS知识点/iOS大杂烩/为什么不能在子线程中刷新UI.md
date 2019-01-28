## 为什么不能在子线程中刷新UI 

在开发过程中，我们或多或少会不经意在后台线程中调用了UIKit框架的内容，可能是在网络回调时直接`imageView.image = anImage`，也有可能是不小心在后台线程中调用了`UIApplication.sharedApplication`。而这个时候编译器会报出一个`runtime`错误，我们也会迅速的对其进行修正。
但仔细去思考，究竟为什么一定要在主线程操作UI呢？如果在后台线程对UI进行操作会发生什么？在后台线程对UI进行操作不是可以更好的避免卡顿吗？这篇文章就是基于这样一些疑问而产生的。

> UIKit并不是一个 线程安全 的类，UI操作涉及到渲染访问各种View对象的属性，如果异步操作下会存在读写问题，而为其加锁则会耗费大量资源并拖慢运行速度。另一方面因为整个程序的起点UIApplication是在主线程进行初始化，所有的用户事件都是在主线程上进行传递（如点击、拖动），所以view只能在主线程上才能对事件进行响应。而在渲染方面由于图像的渲染需要以60帧的刷新率在屏幕上 同时 更新，在非主线程异步化的情况下无法确定这个处理过程能够实现同步更新。



### 从UIKit线程不安全说起

在UIKit中，很多类中大部分的属性都被修饰为`nonatomic`，这意味着它们不能在多线程的环境下工作，而对于UIKit这样一个庞大的框架，将其所有属性都设计为线程安全是不现实的，这可不仅仅是简单的将`nonatomic`改成`atomic`或者是加锁解锁的操作，还涉及到很多的方面

- 假设能够异步设置view的属性，那我们究竟是希望这些改动能够同时生效，还是按照各自runloop的进度去改变这个view的属性呢？
- 假设UITableView在其他线程去移除了一个cell，而在另一个线程却对这个cell所在的index进行一些操作，这时候可能就会引发crash。
- 如果在后台线程移除了一个view，这个时候runloop周期还没有完结，用户在主线程点击了这个“将要”消失的view，那么究竟该不该响应事件？在哪条线程进行响应？
 
 仔细思考，似乎能够多线程处理UI并没有给我们开发带来更多的便利，假如你代入了这些情景进行思考，你很容易得出一个结论： “我在一个串行队列对这些事件进行处理就可以了。” 苹果也是这样想的，所以UIKit的所有操作都要放到主线程串行执行。
 
 在[Thread-Safe Class Design](https://www.objc.io/issues/2-concurrency/thread-safe-class-design/)一文提到
 
 > It’s a conscious design decision from Apple’s side to not have UIKit be thread-safe. Making it thread-safe wouldn’t buy you much in terms of performance; it would in fact make many things slower. And the fact that UIKit is tied to the main thread makes it very easy to write concurrent programs and use UIKit. All you have to do is make sure that calls into UIKit are always made on the main thread.
 
 大意为把UIKit设计成线程安全并不会带来太多的便利，也不会提升太多的性能表现，甚至会因为加锁解锁而耗费大量的时间。事实上并发编程也没有因为UIKit是线程不安全而变得困难，我们所需要做的只是要确保UI操作在主线程进行就可以了。
 
 > 好吧，那假设我们用黑魔法祝福了UIKit，这个UIKit能够完美的解决我们上面提到的问题，并能够按照开发者的想法随意展现不同的形态。那这个时候我们可以在后台线程操作UI了嘛？
 
 **很可惜，还是不行。**
 
 ### Runloop 与绘图循环
 
 道理我们都懂，那这个究竟跟我们不能在后台线程操作UI有什么关系呢？
 
 `UIApplication`在主线程所初始化的Runloop我们称为`Main Runloop`，它负责处理app存活期间的大部分事件，如用户交互等，它一直处于不断处理事件和休眠的循环之中，以确保能尽快的将用户事件传递给GPU进行渲染，使用户行为能够得到响应，画面之所以能够得到不断刷新也是因为`Main Runloop`在驱动着
 
 而每一个view的变化的修改并不是立刻变化，相反的会在当前run loop的结束的时候统一进行重绘，这样设计的目的是为了能够在一个runloop里面处理好所有需要变化的view，包括resize、hide、reposition等等，所有view的改变都能在同一时间生效，这样能够更高效的处理绘制，这个机制被称为`绘图循环（View Drawing Cycle)。`
 
 
 假设这个时候我们应用了我们的魔法UIKit，并愉快的在一条后台线程操作UI，但当我们需要对设备进行旋转并重新布局的时候，问题来了，因为各个线程之间不同步，这时候各个view修改的请求时机是零碎的，所以所有的旋转变化并不能在`Main Runloop`的一个runloop里面处理完，这就导致设备旋转之后还有一些view迟迟没有旋转。
 
 另一方面，因为我们的魔法UIKit并不是在主线程，所以Main Runloop中的事件需要跨线程进行传输，这样会导致显示与用户事件并不同步。试想一下我们用我们的魔法UIKit写了一个游戏，用户如果在图片还没有加载出来的时候按下了按钮，他们就能胜利，于是我们写出了这样的代码：
 
 **game.m**
 
 ```
 - (void)didClickButton:(UIButton *)button
 {
 if (self.imageView.image != nil) {
 // User lose!
 } else {
 // User Win!
 }
 }
 
 - (void)loadImageInBackgroundThread
 {
 dispatch_async(dispatch_queue_create("BackgroundQueue", NULL), ^{
 self.imageView.image = [self downloadedImage];
 };
 }

 ```
 
 因为我们完美的魔法UIKit，在后台执行imageView.image = xxx并不会产生任何问题。游戏上线，在你还为后台处理UI而沾沾自喜的时候，用户投诉了他们明明没有看到图片显示，点击的时候还是告诉他们输了，于是你的产品就这样扑街了。
 
 这是因为点击等事件是由系统传递给UIApplication中，并在Main Runloop中进行处理与响应，但是由于UI在后台线程中进行处理，所以他跟事件响应并不同步。即使在UI所在的后台线程也自己维护了一个Runloop，在Runloop结束时候进行渲染，但可能用户已经进行了点击操作并开始辱骂你的游戏了。
 
 
 
 ### 理解iOS的渲染流程
 
 
 
 
 
 

