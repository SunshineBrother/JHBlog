 
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















































































