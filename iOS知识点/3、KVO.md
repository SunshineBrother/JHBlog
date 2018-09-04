## KVO实现原理

`KVO(key value observing)`键值监听是我们在开发中常使用的用于监听特定对象属性值变化的方法，常用于监听数据模型的变化 

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






