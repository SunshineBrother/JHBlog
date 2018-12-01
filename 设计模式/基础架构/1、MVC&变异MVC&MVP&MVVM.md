## 浅谈MVC&变异MVC&MVP&MVVM 

稍微做过几年开发的一定都听过MVC、MVP、MVVM这些架构名称吧。其实不论我们用哪一种机构模式，总会有一个地方造成臃肿，我们需要根据我们的具体业务使用更加合适的架构模式。而不能迷信哪种架构模式比较先进什么的。。。


### MVC

![MVC](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/基础架构/MVC.png)

MVC的优点和缺点都是很明显
- 优点：View、Model都是可以重复利用的，可以独立使用
- 缺点：Controller的代码过于臃肿。


对于MVC，iOS中最为典型的就是`UITableview`的时候，`UITableview`几乎是对MVC架构用到了极致。我们平时创建`UITableview`、`UITableviewCell`、`Model`，这就是最为常见的MVC架构。

今天我们对一个`view`进行一些实现

![MVC1](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/基础架构/MVC1.png)

**APPView代码**
```
@class APPView;
@protocol MyAppViewDelegate <NSObject>
@optional
- (void)appViewDidClick:(APPView *)appView;
@end

@interface APPView : UIView

@property (nonatomic,strong) UIImageView *iconView;
@property (nonatomic,strong) UILabel *nameLabel;

@property (weak, nonatomic) id<MyAppViewDelegate> delegate;

@end



实现

- (instancetype)initWithFrame:(CGRect)frame
{
if (self = [super initWithFrame:frame]) {
UIImageView *iconView = [[UIImageView alloc] init];
iconView.frame = CGRectMake(0, 0, 100, 100);
[self addSubview:iconView];
_iconView = iconView;

UILabel *nameLabel = [[UILabel alloc] init];
nameLabel.frame = CGRectMake(0, 100, 100, 30);
nameLabel.textAlignment = NSTextAlignmentCenter;
[self addSubview:nameLabel];
_nameLabel = nameLabel;
}
return self;
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
if ([self.delegate respondsToSelector:@selector(appViewDidClick:)]) {
[self.delegate appViewDidClick:self];
}
}

```

**APPModel代码**

```
@interface APPModel : NSObject

@property (nonatomic,copy) NSString *name;
@property (nonatomic,copy) NSString *image;

@end
```

**Controller实现**
```
- (void)viewDidLoad {
[super viewDidLoad];


//创建view
APPView *app = [[APPView alloc]initWithFrame:CGRectMake(100, 100, 100, 150)];
app.delegate = self;
[self.view addSubview:app];

//创建model
APPModel *model = [[APPModel alloc]init];
model.name = @"我是一片云";
model.image = @"cloud";

//赋值
app.nameLabel.text = model.name;
app.iconView.image = [UIImage imageNamed:model.image];

}

#pragma mark -- view点击事件 --
- (void)appViewDidClick:(APPView *)appView{
NSLog(@"点击了view");
}

```

为了更加明白的看出来MVC，我这里有单独的实现了一个`APPModel`，我们查看代码可以看到，大量的业务逻辑需要再`Controller`里面处理。我们需要处理`View`的创建，赋值，实现点击事件，这些功能就造成了`Controller`的臃肿。但是好处也是有的，因为`View`和`Model`互相不知道对方是谁，我们可以重复利用他们。





### 变异MVC

![MVC2](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/基础架构/MVC2.png)

变异MVC其实就是View也持有Model，将View内部的细节封装起来了

- 优点：对Controller进行瘦身，将View内部的细节封装起来了，外界不知道View内部的具体实现
- 缺点：View依赖于Model


**APPView代码**
```
#import <UIKit/UIKit.h>
#import "APPModel.h"
NS_ASSUME_NONNULL_BEGIN

@class APPView;
@protocol MyAppViewDelegate <NSObject>
@optional
- (void)appViewDidClick:(APPView *)appView;
@end

@interface APPView : UIView

@property (nonatomic,strong) APPModel *model;
@property (weak, nonatomic) id<MyAppViewDelegate> delegate;

@end


//实现
#import "APPView.h"
@interface APPView ()
@property (nonatomic,strong) UIImageView *iconView;
@property (nonatomic,strong) UILabel *nameLabel;
@end
@implementation APPView

- (instancetype)initWithFrame:(CGRect)frame
{
if (self = [super initWithFrame:frame]) {
UIImageView *iconView = [[UIImageView alloc] init];
iconView.frame = CGRectMake(0, 0, 100, 100);
[self addSubview:iconView];
_iconView = iconView;

UILabel *nameLabel = [[UILabel alloc] init];
nameLabel.frame = CGRectMake(0, 100, 100, 30);
nameLabel.textAlignment = NSTextAlignmentCenter;
[self addSubview:nameLabel];
_nameLabel = nameLabel;
}
return self;
}


- (void)setModel:(APPModel *)model{
_model = model;
_iconView.image = [UIImage imageNamed:model.image];
_nameLabel.text = model.name;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
if ([self.delegate respondsToSelector:@selector(appViewDidClick:)]) {
[self.delegate appViewDidClick:self];
}
}

@end
```

代码变化是view持有了Model，然后把view的实现方法了匿名函数里面了。model的结构还是不变


**Controller实现**

```
- (void)viewDidLoad {
[super viewDidLoad];


//创建view
APPView *app = [[APPView alloc]initWithFrame:CGRectMake(100, 100, 100, 150)];
app.delegate = self;
[self.view addSubview:app];

//创建model
APPModel *model = [[APPModel alloc]init];
model.name = @"我是一片云";
model.image = @"cloud";

//赋值
app.model = model;
}

#pragma mark -- view点击事件 --
- (void)appViewDidClick:(APPView *)appView{
NSLog(@"点击了view");
}

```

在`controller`里面我们不在`controller`里面对`view`进行实现，需要把`Model`的值传给`View`



### MVP


![MVP](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/基础架构/MVP.png)

MVP是`controller`不在持有 `View和Model`，而是有一个`Presenter`类持有。


**Presenter实现**

```
@interface APPPresenter ()<MyAppViewDelegate>
@property (weak, nonatomic) UIViewController *controller;
@end

@implementation APPPresenter
- (instancetype)initWithController:(UIViewController *)controller{
if (self = [super init]) {
_controller = controller;
//创建view
APPView *app = [[APPView alloc]initWithFrame:CGRectMake(100, 100, 100, 150)];
app.delegate = self;
[controller.view addSubview:app];

//创建model
APPModel *model = [[APPModel alloc]init];
model.name = @"我是一片云";
model.image = @"cloud";

//赋值
app.model = model;
}

return self;
}

#pragma mark -- view点击事件 --
- (void)appViewDidClick:(APPView *)appView{
NSLog(@"点击了view");
}
```




**Controller实现**

```
- (void)viewDidLoad {
[super viewDidLoad];
// Do any additional setup after loading the view, typically from a nib.

self.presenter = [[APPPresenter alloc]initWithController:self];

}
```

【注意】：要把`APPPresenter`设置为全部变量，如果设置为局部变量的话，会在出函数以后`presenter`对象就会被销毁。

其实MVP就是我们在专门做一个`APPPresenter`类，把`controller`里面方法给方法`APPPresenter`类里面



### MVVM


使用MVVM最好的框架是`ReactiveCocoa`，但是这个框架是重量级的框架，学习成本还是比较大的，如果项目中主要使用的架构就是MVVM，那么用这个框架是非常好的，如果只是局部使用的话我们可以使用`KVOController`来简单的替代一下

![MVVM](https://github.com/SunshineBrother/JHBlog/blob/master/设计模式/基础架构/MVVM.png)

MVVM我感觉好像跟MVP有点类似，但是比MVP多了一个功能，就是在view改变时，model也能及时改变，在model改变时view也能及时改变

**APPView代码**

```
#import "APPView.h"
#import "NSObject+FBKVOController.h"
@interface APPView ()
@property (nonatomic,strong) UIImageView *iconView;
@property (nonatomic,strong) UILabel *nameLabel;
@end
@implementation APPView

- (instancetype)initWithFrame:(CGRect)frame
{
if (self = [super initWithFrame:frame]) {
UIImageView *iconView = [[UIImageView alloc] init];
iconView.frame = CGRectMake(0, 0, 100, 100);
[self addSubview:iconView];
_iconView = iconView;

UILabel *nameLabel = [[UILabel alloc] init];
nameLabel.frame = CGRectMake(0, 100, 100, 30);
nameLabel.textAlignment = NSTextAlignmentCenter;
[self addSubview:nameLabel];
_nameLabel = nameLabel;
}
return self;
}


- (void)setModel:(APPModel *)model{
_model = model;
_iconView.image = [UIImage imageNamed:model.image];
_nameLabel.text = model.name;


__weak typeof(self) waekSelf = self;
[self.KVOController observe:model keyPath:@"name" options:NSKeyValueObservingOptionNew block:^(id  _Nullable observer, id  _Nonnull object, NSDictionary<NSKeyValueChangeKey,id> * _Nonnull change) {
waekSelf.nameLabel.text = change[NSKeyValueChangeNewKey];
}];

[self.KVOController observe:model keyPath:@"image" options:NSKeyValueObservingOptionNew block:^(id  _Nullable observer, id  _Nonnull object, NSDictionary<NSKeyValueChangeKey,id> * _Nonnull change) {
waekSelf.iconView.image = [UIImage imageNamed:change[NSKeyValueChangeNewKey]];
}];

}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
if ([self.delegate respondsToSelector:@selector(appViewDidClick:)]) {
[self.delegate appViewDidClick:self];
}
}

```

在实现model的set方法时，要监听model值的变化。


**viewModel的实现**
```
- (instancetype)initWithController:(UIViewController *)controller{
if (self = [super init]) {

_controller = controller;
//创建view
APPView *app = [[APPView alloc]initWithFrame:CGRectMake(100, 100, 100, 150)];
app.delegate = self;
[controller.view addSubview:app];

//创建model
APPModel *model = [[APPModel alloc]init];
model.name = @"我是一片云";
model.image = @"cloud";

//赋值
app.model = model;
}

return self;
}

#pragma mark -- view点击事件 --
- (void)appViewDidClick:(APPView *)appView{
NSLog(@"点击了view");

appView.model.name = [NSString stringWithFormat:@"%d",arc4random()%100];

NSLog(@"%@",appView.model.name);
}
```

viewModel实现跟`Presenter`实现是类似的。




























