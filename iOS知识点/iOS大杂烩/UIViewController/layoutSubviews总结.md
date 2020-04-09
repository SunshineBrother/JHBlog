## layoutSubviews总结 

iOS layout机制相关方法


```
- (CGSize)sizeThatFits:(CGSize)size
- (void)sizeToFit
——————-

- (void)layoutSubviews
- (void)layoutIfNeeded
- (void)setNeedsLayout
——————–

- (void)setNeedsDisplay
- (void)drawRect
```


**layoutSubviews在以下情况下会被调用**


- 1、init初始化不会触发layoutSubviews
- 2、当view的fram的值为0的时候，addSubview不会调用layoutSubviews。
- 3、addSubview的时候。
- 4、当view的frame发生改变的时候，改变fram的大小会触发layoutSubviews，改变frame的x,y的值并不会触发
- 5、直接调用setNeedsLayout方法会调用。
- 6、滑动UIScrollView的时候。
- 7、旋转Screen会触发父UIView上的layoutSubviews事件。
- 8、改变一个UIView大小的时候也会触发父UIView上的layoutSubviews事件

layoutSubviews, 当我们在某个类的内部调整子视图位置时，需要调用。反过来的意思就是说：如果你想要在外部设置subviews的位置，就不要重写。

 

**刷新子对象布局**

- layoutSubviews方法：这个方法，默认没有做任何事情，需要子类进行重写
- setNeedsLayout方法： 标记为需要重新布局，异步调用layoutIfNeeded刷新布局，不立即刷新，但layoutSubviews一定会被调用
- layoutIfNeeded方法：如果，有需要刷新的标记，立即调用layoutSubviews进行布局（如果没有标记，不会调用layoutSubviews）


如果要立即刷新，要先调用[view setNeedsLayout]，把标记设为需要布局，然后马上调用[view layoutIfNeeded]，实现布局

在视图第一次显示之前，标记总是“需要刷新”的，可以直接调用[view layoutIfNeeded]

 

**重绘**

- drawRect:(CGRect)rect方法：重写此方法，执行重绘任务
- setNeedsDisplay方法：标记为需要重绘，异步掉用drawRect
- setNeedsDisplayInRect:(CGRect)invalidRect方法：标记为需要局部重绘
 

sizeToFit会自动调用sizeThatFits方法；
sizeToFit不应该在子类中被重写，应该重写sizeThatFits
sizeThatFits传入的参数是receiver当前的size，返回一个适合的size

sizeToFit可以被手动直接调用
sizeToFit和sizeThatFits方法都没有递归，对subviews也不负责，只负责自己

 





