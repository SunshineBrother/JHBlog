 
## UIButton的imageEdgeInsets和titleEdgeInsets原理



### UIEdgeInsets

UIButton共有3个与UIEdgeInsets相关的属性：

- imageEdgeInsets调整image的上下左右边缘离开原来位置的距离，该调整并不会改变UIButton原来的大小，image为了适应调整，可能会变形或者跑出UIButton的外面。

- titleEdgeInsets调整title的上下左右边缘离开原来位置的距离，该调整并不会改变UIButton原来的大小，title为了适应调整，文字可能显示不全或者跑出UIButton的外面。

- contentEdgeInsets调整UIButton本身的上下左右边缘离开原来位置的距离，该调整会改变UIButton的大小。

**这个3个属性的默认值都是.zero**

UIEdgeInsets由top、left、  bottom、right构成，对于imageEdgeInsets和titleEdgeInsets来说：

- top为正值时，控件会相对原来所在的位置下移相应值，控件的顶部边缘会在原来位置的下方相应值。top为负值时，控件会相对原来的位置上移相应值，控件的顶部边缘会在原来位置的上方相应值。

- left为正值时，控件会相对原来所在的位置右移相应值，控件的左侧边缘会在原来位置的右方相应值。left为负值时，控件会相对原来的位置左移相应值，控件的左侧边缘会在原来位置的左方相应值。

- bottom为正值时，控件会相对原来所在的位置上移相应值，控件的底部边缘会在原来位置的上方相应值。bottom为负值时，控件会相对原来的位置下移相应值，控件的底部边缘会在原来位置的下方相应值。

- right为正值时，控件会相对原来所在的位置左移相应值，控件的右侧边缘会在原来位置的左方相应值。right为负值时，控件会相对原来位置右移相应值，控件的右侧边缘会在原来位置的右方相应值。


### contentHorizontalAlignment和contentVerticalAlignment

这是两个枚举，即整个内容的`水平对齐方式`和`垂直对齐方式`
 
```
typedef NS_ENUM(NSInteger, UIControlContentHorizontalAlignment) {
    UIControlContentHorizontalAlignmentCenter = 0,
    UIControlContentHorizontalAlignmentLeft   = 1,
    UIControlContentHorizontalAlignmentRight  = 2,
    UIControlContentHorizontalAlignmentFill   = 3,
    UIControlContentHorizontalAlignmentLeading  API_AVAILABLE(ios(11.0), tvos(11.0)) = 4,
    UIControlContentHorizontalAlignmentTrailing API_AVAILABLE(ios(11.0), tvos(11.0)) = 5,
};

typedef NS_ENUM(NSInteger, UIControlContentVerticalAlignment) {
    UIControlContentVerticalAlignmentCenter  = 0,
    UIControlContentVerticalAlignmentTop     = 1,
    UIControlContentVerticalAlignmentBottom  = 2,
    UIControlContentVerticalAlignmentFill    = 3,
};

// 默认：
 button.contentHorizontalAlignment = UIControlContentHorizontalAlignmentCenter;
 button.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
```

其中UIControlContentHorizontalAlignmentLeading和UIControlContentHorizontalAlignmentTrailing为iOS11新增，在我们大中华地区，Leading就是Left，Trailing就是Right ，对于部分国家，他们的语言是从右往左写，这时Leading就是Right，Trailing就Left
 

**正文**


创建一个按钮，设置文字和图片，按钮的内容默认排布如图：为了便于理解，我给的`titleLabel`和`imageView`是等宽的

![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/1.jpg)


截图中：


- 1、黑色边框为按钮矩形区域，其bounds为：`(0，0，200，100)`，为了便于研究，contentEdgeInset默认UIEdgeInsetsZero，即按钮的内容区域就是按钮的bounds；
- 2、imageView的frame为`(50，25，50，50)`；
- 3、titleLabel的frame为`(100，37.5，50，50)`；

 
现在，我设置

```
button.imageEdgeInsets = UIEdgeInsetsMake(0，50， 0，0);
```
经过上面的设置后，请大家猜想一下，图片的位置会在什么地方？
思考 1s、2s、3s、.......
大家心中差不多有想法了，图片的原x值为50，现在设置UIEdgeInsetsMake(0，50， 0，0)，相当于整个图片向右平移50，那么现在图片的x值应该为100，大家想象的结果是不是这样的，如图

![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/2.jpg)


我要告诉大家，上面的结果是错的，**正确的结果**如图：

![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/3.jpg)


实际上，图片只向右平移了50的一半，即25，这是为什么？


**网上错误结论：**


- 对于imageView：其`imageEdgeInsets`的`top，left，bottom`是相对`button`的`contentRect`而言，`right`是相对`titleLabel`而言；

- 对于titleLabel：其`titleEdgeInsets`的`top，right，bottom`是相对`button`的`contentRect`而言，`left`是相对`imageView`而言。
 

**正确结论**


`imageEdgeInsets`和`titleEdgeInsets`的`top，left，right， bottom`都是相对`button`的`contentRect`而言，当`contentEdgeInsets`为`UIEdgeInsetsZero`时，`button、imageView、titleLabel`的安全区域均为`button`的`bounds`。

 
根据这个正确结论，当设置了`button.imageEdgeInsets = UIEdgeInsetsMake(0，50， 0，0)`时，那么imageView的安全区域就是如下图中的红色区域

![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/4.jpg)


图片的区域我们知道了，根据水平排列方式默认为`UIControlContentHorizontalAlignmentCenter`，图片应当在红色区域的中间位置，然而，我们要深刻明白：


> 重要的话说3遍
UIControlContentHorizontalAlignmentCenter的指的是内容(图片+文字)整体居中
UIControlContentHorizontalAlignmentCenter的指的是内容(图片+文字)整体居中
UIControlContentHorizontalAlignmentCenter的指的是内容(图片+文字)整体居中
其余枚举值同理

 

因此，尽管titleLabel没有设置titleEdgeInsets，但是我们在对imageView进行某种对齐时，不应该只考虑imageView，应该将imageView+titleLabel这个整体作为考虑对象; 如图

![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/5.jpg)


**核心解释**


上图中，imageView和蓝色的titleLabel作为一个整体，在红色区域内居中了，绿色的titleLabel只参与计算，由于我们没有设置titleLabel的titleEdgeInsets，所以最终titleLabel的位置依然保持不变。蓝色的titleLabel实际上是虚拟的，我只是告诉大家，`系统进行对齐方式计算时，永远是把imageView+titleLabel这个整体作为计算对象`，我们来计算一下，图片向右偏移25是怎么来的：

- ①红色区域的宽度为：200 - 50 = 150；
- ②图片+蓝色label的总宽度：50 + 50 = 100；
- ③图片的x值：(① - ②) / 2.0 =（150 - 100）/ 2.0 = 25；(除以2是因为居中对齐，如果是其余对齐就不用除以2)

我不知道我上面的表达够不够清楚，如果不清楚，那么我们来一次强化训练

 

### 强化训练


我们不再按照水平中心对齐，我们来一次左对齐

```
button.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
```
 
设置后如图

![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/6.jpg)


再设置

```
button.imageEdgeInsets = UIEdgeInsetsMake(0, 0, 0, 50);
```

大家想想经过上面那行代码之后，结果是什么呢？图片会向左偏移50的距离吗？如果按照网上的结论，图片的right是相对titleLabel而言，那么设置right为50图片必会向左偏移50。我要告诉大家，上面那行代码设置之后，不会产生任何变化，为什么？

原因很简单：上面那行代码的意思是，图片的安全区域为：在contentRect的基础上，原区域右边往左内缩50距离，即下图中的红色区域

 
![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/7.jpg)


在这个红色区域当中，将imageView+(虚拟)titleLabel这个整体进行左对齐，大家明显能看到，现在就是左对齐的，所以设置right为50是不会有任何变化的，那么如果我们修改一下，设置


```
 button.imageEdgeInsets = UIEdgeInsetsMake(0, 0, 0, 175);
```

上面那行代码的意思是，图片的安全区域为：在contentRect的基础上，原区域右边往左内缩175距离，即下图中的红色区域

![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/8.jpg)



在这个红色区域内，要把imageView+(虚拟)titleLabel这个整体进行左对齐，但是我们发现，红色区域的宽度容不下imageView+titleLabel这个整体，这个时候，系统先会把titleLabel的宽度压缩，如果压缩为0之后，发现连imageView都容不下，那么继续压缩imageView，直到宽度降为红色区域宽为止，titleLabel保持不动， 最终显示结果如图

 
![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/9.jpg)


### 再次训练

保持默认设置


```
button.contentHorizontalAlignment = UIControlContentHorizontalAlignmentCenter;
button.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
```

再设置

```
button.imageEdgeInsets = UIEdgeInsetsMake(50, 0, 0, 0);
```


上面那行代码的意思是，图片的安全区域为：在contentRect的基础上，原区域顶部向下内缩50距离，即下图中的红色区域：


![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/10.jpg)



在这个红色区域当中，要依然保证imageView+(虚拟)titleLabel这个整体进行垂直居中， 因此最终结果如图


![](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIButton/11.jpg)


从这里我们可以萌生一个思想

imageEdgeInsets和titleEdgeInsets不要去理解为将imageView和titleLabel进行平移，应该理解为将imageView和titleLabel的安全区域的各边进行偏移，偏移完成后，再联合contentHorizontalAlignment和contentVerticalAlignment属性进行整体对齐

 
 
 ### 提醒
 
 我想大家在实现按钮图片位置在上、下、左、右的需求时，有不少人是通过重写按钮的`imageRectForContentRect:`和`titleRectForContentRect:`的，我个人也很推荐这种做法，重写`layoutSubviews`也可以，但我并不推荐，可以说重写`layoutSubviews`可以实现你的需求，但是严重破坏了系统按钮，因为，系统按钮在`layoutSubviews`里面，当存在文字或者图片时，会先调用`imageRectForContentRect:`和`titleRectForContentRect:`这2个方法计算出`imageRect`和`titleRect`，然后将计算结果应用在`imageView`和`titleLabel`上，所以，如果你重写`layoutSubviews`，先`super `, 然后进行一系列自己的布局，这就会导致你使用`button`时，通过`imageRectForContentRect:`和`titleRectForContentRect:`这2个方法获取到的`rect`并非你在`layoutSubviews`里计算的结果，仍然是系统计算的结果，这就是破坏了原始按钮的方法

 
 **imageRectForContentRect:和titleRectForContentRect:的调用时机**
 
 - 1、在第一次调用titleLabel和imageView的getter方法(懒加载)时,alloc init之前会调用一次(无论有无图片文字都会直接调)，因此，在重写这2个方法时，在方法里面不要使用self.imageView和self.titleLabel，因为这2个控件是懒加载，如果在重写的这2个方法里是第一调用imageView和titleLabel的getter方法, 则会造成死循环

- 2、在layoutsSubviews中如果文字或图片不为空时会调用, 测试方式：在重写的这两个方法里调用setNeedsLayout(layutSubviews)，发现会造成死循环

- 3、按钮的frame发生改变，设置文字图片、改动文字和图片、设置对齐方式，设置内容区域等时会调用，其实这些，系统是调用了layoutSubviews从而间接的去调用imageRectForContentRect:和titleRectForContentRect:

 

 

[文章转载自：iOS button的imageEdgeInsets和titleEdgeInsets原理](https://www.jianshu.com/p/034e61768c1f)

























