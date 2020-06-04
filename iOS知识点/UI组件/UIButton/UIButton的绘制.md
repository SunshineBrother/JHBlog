## UIButton的绘制 

什么时候调用`imageRectForContentRect`,`titleRectForContentRect`,`contentRectForBounds`，也是调用时机。首先梳理清楚几个布局的规则：

- 1、改变view的size会触发layoutSubviews
- 2、改变view的x或y不会触发layoutSubviews
- 3、改变subview的size会触发superview的layoutSubviews
- 4、改变subview的x或y不会触发自己以及父视图的layoutSubviews



记住这几个布局时的调用顺序:
- 1、layoutSubviews
- 2、backgroundRectForBounds:
- 3、contentRectForBounds:
- 4、imageRectForContentRect:
- 5、titleRectForContentRect:


特别的：

在UIButton初始化阶段会依次调用contentRectForBounds:，imageRectForContentRect:。这是在布局之前完成的。
改变title，image,background image都会来到进行绿色文字顺序的布局。但不会触发父视图的布局，因为UIButton的尺寸未变。
绿色文字区域的调用并不是一次完成。而是复杂的多次调用完成的。它的顺序是：3 -> 4 -> 3 -> 5 -> 3 -> 4



### 渲染时给出imageView和titleLabel的frame

重写以下两个方法，返回需要的frame，使imageView和titleLabel分开渲染。

```
-(CGRect)titleRectForContentRect:(CGRect)contentRect;
-(CGRect)imageRectForContentRect:(CGRect)contentRect;
```


所以我们创建一个MyButton继承自UIButton，并定义两个属性

```
@interface MyButton : UIButton

@property (nonatomic, assign) CGRect imageRect;
@property (nonatomic, assign) CGRect titleRect;

@end
```

在.m中重写两个方法

```
- (CGRect)titleRectForContentRect:(CGRect)contentRect {
    
    if (!CGRectIsEmpty(self.titleRect) && !CGRectEqualToRect(self.titleRect, CGRectZero)) {
        return self.titleRect;
    } else {
        return [super titleRectForContentRect:contentRect];
    }
}

- (CGRect)imageRectForContentRect:(CGRect)contentRect {
    
    if (!CGRectIsEmpty(self.imageRect)&&!CGRectEqualToRect(self.imageRect, CGRectZero)) {
        return self.imageRect;
    } else {
        return [super imageRectForContentRect:contentRect];
    }
}
```


使用

```
MyButton *btn = [[MyButton alloc]initWithFrame:CGRectZero];
btn.backgroundColor = [UIColor redColor];
[btn addTarget:self action:@selector(test) forControlEvents:UIControlEventTouchUpInside];
[btn setTitle:@"title" forState:UIControlStateNormal];
[btn setImage:[UIImage imageNamed:@"icon"] forState:UIControlStateNormal];
btn.titleRect = CGRectMake(60.0 , 10.0, 100.0, 40.0);
btn.imageRect = CGRectMake(10.0, 10.0, 40.0, 40.0);
[self.view addSubview:btn];
```


在上述代码中，以CGRectZero初始化button，然后分别设置titleRect和imageRect属性，观察到虽然imageView和titleLabel正常绘制，但是button的frame依然是Zero





我们希望button能够根据titleRect和imageRect属性的值自动适配合适的frame。即：设置titleRect和imageRect便可以算出button的大小。 所以重写UIButton的layoutSubViews方法：

```
- (void)layoutSubviews {
    
    [super layoutSubviews];
    
    BOOL hasSetTitleRect = !(CGRectIsEmpty(self.titleRect) || CGRectEqualToRect(self.titleRect, CGRectZero));
    BOOL hasSetImageRect = !(CGRectIsEmpty(self.imageRect) || CGRectEqualToRect(self.imageRect, CGRectZero));
    
    if (hasSetImageRect || hasSetTitleRect) {
        CGRect rect = self.frame;
        CGRect curentRect =  CGRectUnion(hasSetImageRect ? self.imageRect : CGRectZero, hasSetTitleRect  ? self.titleRect : CGRectZero);
        rect.size.width = curentRect.size.width + curentRect.origin.x * 2;
        rect.size.height = curentRect.size.height + curentRect.origin.y * 2;
        self.frame = rect;
    }
    
}
```















































