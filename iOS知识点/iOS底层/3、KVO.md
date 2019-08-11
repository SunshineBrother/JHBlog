## KVO实现原理

`KVO(key value observing)`键值监听是我们在开发中常使用的用于监听特定对象属性值变化的方法，常用于监听数据模型的变化 

KVO是为了监听一个对象的某个属性值是否发生变化。在属性值发生变化的时候，肯定会调用其setter方法。所以`KVO的本质就是监听对象有没有调用被监听属性对应的setter方法`

在学习实现原理之前我们首先先了解一下`KVO`常用的有哪些方法

### KVO常用方法
```
/*
注册监听器
监听器对象为observer，被监听对象为消息的发送者即方法的调用者在回调函数中会被回传
监听的属性路径为keyPath支持点语法的嵌套
监听类型为options支持按位或来监听多个事件类型
监听上下文context主要用于在多个监听器对象监听相同keyPath时进行区分
添加监听器只会保留监听器对象的地址，不会增加引用，也不会在对象释放后置空，因此需要自己持有监听对象的强引用，该参数也会在回调函数中回传
*/
- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;

/*
删除监听器
监听器对象为observer，被监听对象为消息的发送者即方法的调用者，应与addObserver方法匹配
监听的属性路径为keyPath，应与addObserver方法的keyPath匹配
监听上下文context，应与addObserver方法的context匹配
*/
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/*
与上一个方法相同，只是少了context参数
推荐使用上一个方法，该方法由于没有传递context可能会产生异常结果
*/
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;

/*
监听器对象的监听回调方法
keyPath即为监听的属性路径
object为被监听的对象
change保存被监听的值产生的变化
context为监听上下文，由add方法回传
*/
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context;

```
### KVO简单实现
我们创建一个`person`对象，然后在里面添加一个`age`属性，我们就来观察一下`age`属性
**person对象**

```
#import <Foundation/Foundation.h>

@interface Person : NSObject
@property (nonatomic,assign) NSInteger age;
@end

```
**简单实现**
```
#import "ViewController.h"
#import "Person.h"
@interface ViewController ()

@property (nonatomic,strong) Person *p1;
@property (nonatomic,strong) Person *p2;

@end

@implementation ViewController

- (void)viewDidLoad {
	[super viewDidLoad];

	self.p1 = [[Person alloc]init];
	self.p2 = [[Person alloc]init];
	self.p1.age = 10;
	self.p2.age = 20;

	// 给person1对象添加KVO监听
	NSKeyValueObservingOptions options = NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld;
	[self.p1 addObserver:self forKeyPath:@"age" options:options context:@"123"];

}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
	self.p1.age = arc4random()%100;
	self.p2.age = arc4random()%100;
}

- (void)dealloc {
	[self.p1 removeObserver:self forKeyPath:@"age"];

}
// 当监听对象的属性值发生改变时，就会调用
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context
{
	NSLog(@"监听到%@的%@属性值改变了 - %@ - %@", object, keyPath, change, context);
}

```
以上代码就是一个`KVO`的简单实现，但是我们有没有想过他的内部到底是怎样实现的呢，今天我们就来探究一下`KVO`的内部实现原理

### KVO的内部实现
探究一个对象底层实现最简单的办法就行打印一些对象信息，看看有什么改变

我们在给`person1`添加监听之前分别打印`p1,p2`的类信息
代码实现
```
NSLog(@"person1添加KVO监听之前 - %@ %@",
object_getClass(self.p1),
object_getClass(self.p2));
// 给person1对象添加KVO监听
NSKeyValueObservingOptions options = NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld;
[self.p1 addObserver:self forKeyPath:@"age" options:options context:@"123"];


NSLog(@"person1添加KVO监听之后 - %@ %@",
object_getClass(self.p1),
object_getClass(self.p2));
```

打印结果
![KVO1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVO1.png)

我们根据结果看到，在添加KVO观察者之后`p1`的类对象由`Person`变成了`NSKVONotifying_Person`，虽然`p1`的类对象变成了`NSKVONotifying_Person`，但是我们在调用的时候感觉我们的`p1`的类对象还是`Person`，所以，我们可以猜测`KVO`会在运行时动态创建一个新类，将对象的`isa`指向新创建的类，`新类是原类的子类`，命名规则是`NSKVONotifying_xxx`的格式。KVO为了使其更像之前的类，还会将对象的`class实例方法重写`，使其更像原类


 **查看P1内部方法是否改变**

我们在发现`p1`的类对象由`Person`变成了`NSKVONotifying_Person`，那我们也随便打印一下`Person`和`NSKVONotifying_Person`内部方法都变成了什么

打印一下方法名
```
- (void)printMethodNamesOfClass:(Class)cls
{
	unsigned int count;
	// 获得方法数组
	Method *methodList = class_copyMethodList(cls, &count);

	// 存储方法名
	NSMutableString *methodNames = [NSMutableString string];

	// 遍历所有的方法
	for (int i = 0; i < count; i++) {
	// 获得方法
	Method method = methodList[i];
	// 获得方法名
	NSString *methodName = NSStringFromSelector(method_getName(method));
	// 拼接方法名
	[methodNames appendString:methodName];
	[methodNames appendString:@", "];
}

// 释放
free(methodList);

// 打印方法名
NSLog(@"%@ %@", cls, methodNames);
}
```

然后我们分别在KVO监听前后在分别打印一下`p1`的类对象
```
NSLog(@"person1添加KVO监听之前的内部方法===");
[self printMethodNamesOfClass:object_getClass(self.p1)];
// 给person1对象添加KVO监听
NSKeyValueObservingOptions options = NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld;
[self.p1 addObserver:self forKeyPath:@"age" options:options context:@"123"];
NSLog(@"person1添加KVO监听之后的内部方法===");
[self printMethodNamesOfClass:object_getClass(self.p1)];
```

打印结果

![KVO2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVO2.png)
 
我们在来打印一些KVO监听前后`setAge`方法发生了什么改变，因为值得改变肯定是因为`set`方法导致的，所以我们打印一下`setAge`方法。`methodForSelector`可以打印方法地址，我们分别在KVO监听前后打印

```
NSLog(@"person1添加KVO监听之前 - %p %p",
[self.p1 methodForSelector:@selector(setAge:)],
[self.p2 methodForSelector:@selector(setAge:)]);

// 给person1对象添加KVO监听
NSKeyValueObservingOptions options = NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld;
[self.p1 addObserver:self forKeyPath:@"age" options:options context:@"123"];
NSLog(@"person1添加KVO监听之后 - %p %p",
[self.p1 methodForSelector:@selector(setAge:)],
[self.p2 methodForSelector:@selector(setAge:)]);
```

打印结果
```
2018-09-04 10:41:05.823343+0800 KVO[21971:1023542] person1添加KVO监听之前 - 0x103f18540 0x103f18540
2018-09-04 10:41:05.823702+0800 KVO[21971:1023542] person1添加KVO监听之后 - 0x10425ebf4 0x103f18540

```
我们可以利用lldb分别看一下具体的方法实现：

![KVO5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVO5.png)


根据以上总结，我们大概猜到在使用KVO前后对象的改变了
**未使用KVO监听的对象**

![KVO3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVO3.png)

**使用KVO监听的对象**
![KVO4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVO4.png)


- 1、重写class方法是为了我们调用它的时候返回跟重写继承类之前同样的内容。KVO底层交换了 NSKVONotifying_Person 的 class 方法，让其返回 Person
- 2、重写setter方法:在新的类中会重写对应的set方法，是为了在set方法中增加另外两个方法的调用
```
- (void)willChangeValueForKey:(NSString *)key
- (void)didChangeValueForKey:(NSString *)key
```
在didChangeValueForKey:方法再调用
```
- (void)observeValueForKeyPath:(NSString *)keyPath
ofObject:(id)object
change:(NSDictionary *)change
context:(void *)context
```

- 3、重写dealloc方法，销毁新生成的NSKVONotifying_类。
- 4、重写_isKVOA方法，这个私有方法估计可能是用来标示该类是一个 KVO 机制声称的类。

### _NSSetLongLongValueAndNotify

在添加KVO监听方法以后`setAge`方法变成了`_NSSetLongLongValueAndNotify`,所以我们可以大概猜测动态监听方法主要就是在这里面实现的

我们可以在终端使用`nm -a /System/Library/Frameworks/Foundation.framework/Versions/C/Foundation | grep ValueAndNotify`命令来查看`NSSet*ValueAndNotify`的类型
![KVO6](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVO6.png)

我们可以在`Person`类中重写`willChangeValueForKey`和`didChangeValueForKey`,来猜测一下`_NSSetLongLongValueAndNotify`的内部实现

```
- (void)setAge:(NSInteger)age{
	_age = age;
	NSLog(@"调用set方法");
}


- (void)willChangeValueForKey:(NSString *)key{
	[super willChangeValueForKey:key];
	NSLog(@"willChangeValueForKey");
}

- (void)didChangeValueForKey:(NSString *)key{

	NSLog(@"didChangeValueForKey - begin");

	[super didChangeValueForKey:key];

	NSLog(@"didChangeValueForKey - end");
}

```

![KVO7](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVO7.png)

根据打印结果我们可以推断`_NSSetLongLongValueAndNotify`内部实现为
- 1、调用`willChangeValueForKey`方法
- 2、调用`setAge`方法
- 3、调用'didChangeValueForKey'方法
- 4、'didChangeValueForKey'方法内部调用`oberser`的`observeValueForKeyPath:ofObject:change:context:`方法
```
// 伪代码
void _NSSetIntValueAndNotify()
{
	[self willChangeValueForKey:@"age"];
	[super setAge:age];
	[self didChangeValueForKey:@"age"];
}

- (void)didChangeValueForKey:(NSString *)key
{
	// 通知监听器，某某属性值发生了改变
	[oberser observeValueForKeyPath:key ofObject:self change:nil context:nil];
}
```

### 面试题
讲了这些，我们来讨论面试题吧

**1、iOS用什么方式实现对一个对象的KVO？(KVO的本质是什么？)**
- 1、利用RuntimeAPI动态生成一个子类`NSKVONotifying_XXX`，并且让instance对象的isa指向这个全新的子类`NSKVONotifying_XXX`
- 2、当修改对象的属性时，会在子类`NSKVONotifying_XXX`调用Foundation的`_NSSetXXXValueAndNotify`函数
- 3、在`_NSSetXXXValueAndNotify`函数中依次调用
        - 1、willChangeValueForKey
        - 2、父类原来的setter
        - 3、didChangeValueForKey，didChangeValueForKey:内部会触发监听器（Oberser）的监听方法( observeValueForKeyPath:ofObject:change:context:）
 
 
**2、如何手动触发KVO方法**
手动调用`willChangeValueForKey`和`didChangeValueForKey`方法

键值观察通知依赖于 NSObject 的两个方法: `willChangeValueForKey:` 和 `didChangeValueForKey`。在一个被观察属性发生改变之前， `willChangeValueForKey:` 一定会被调用，这就
会记录旧的值。而当改变发生后， `didChangeValueForKey` 会被调用，继而 `observeValueForKey:ofObject:change:context: `也会被调用。如果可以手动实现这些调用，就可以实现“手动触发”了

 有人可能会问只调用`didChangeValueForKey`方法可以触发KVO方法，其实是不能的，因为`willChangeValueForKey:` 记录旧的值，如果不记录旧的值，那就没有改变一说了


**3、直接修改成员变量会触发KVO吗**
不会触发KVO，因为`KVO的本质就是监听对象有没有调用被监听属性对应的setter方法`，直接修改成员变量，是在内存中修改的，不走`set`方法




**4、不移除KVO监听，会发生什么**
- 不移除会造成内存泄漏
- 但是多次重复移除会崩溃。系统为了实现KVO，为NSObject添加了一个名为NSKeyValueObserverRegistration的Category，KVO的add和remove的实现都在里面。在移除的时候，系统会判断当前KVO的key是否已经被移除，如果已经被移除，则主动抛出一个NSException的异常



[参考demo](https://github.com/SunshineBrother/iOSDemo)





