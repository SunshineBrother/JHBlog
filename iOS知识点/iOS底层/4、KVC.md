 ## KVC

KVC（Key-value coding）键值编码，指iOS的开发中，可以允许开发者通过Key名直接访问对象的属性，或者给对象的属性赋值而不需要调用明确的存取方法。


### 1、KVC中常见方法

我们随便点击进入`setValue:forKey`方法，我们可以发现里面的方法基本上都是基于`NSObject`的`NSKeyValueCoding`分类写的，所以对于所有继承了NSObject的类型，也就是几乎所有的Objective-C对象都能使用KVC(一些纯Swift类和结构体是不支持KVC的)，下面是KVC最为重要的四个方法
 ![KVC1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVC1.png)

```
- (nullable id)valueForKey:(NSString *)key;                          //直接通过Key来取值
- (void)setValue:(nullable id)value forKey:(NSString *)key;          //通过Key来设值
- (nullable id)valueForKeyPath:(NSString *)keyPath;                  //通过KeyPath来取值
- (void)setValue:(nullable id)value forKeyPath:(NSString *)keyPath;  //通过KeyPath来设值

```
`NSKeyValueCoding`类别中还有其他的一些方法，这些方法在碰到特殊情况或者有特殊需求还是会用到的
```
+ (BOOL)accessInstanceVariablesDirectly;
//默认返回YES，表示如果没有找到Set<Key>方法的话，会按照_key，_iskey，key，iskey的顺序搜索成员，设置成NO就不这样搜索

- (BOOL)validateValue:(inout id __nullable * __nonnull)ioValue forKey:(NSString *)inKey error:(out NSError **)outError;
//KVC提供属性值正确性�验证的API，它可以用来检查set的值是否正确、为不正确的值做一个替换值或者拒绝设置新值并返回错误原因。

- (NSMutableArray *)mutableArrayValueForKey:(NSString *)key;
//这是集合操作的API，里面还有一系列这样的API，如果属性是一个NSMutableArray，那么可以用这个方法来返回。

- (nullable id)valueForUndefinedKey:(NSString *)key;
//如果Key不存在，且没有KVC无法搜索到任何和Key有关的字段或者属性，则会调用这个方法，默认是抛出异常。

- (void)setValue:(nullable id)value forUndefinedKey:(NSString *)key;
//和上一个方法一样，但这个方法是设值。

- (void)setNilValueForKey:(NSString *)key;
//如果你在SetValue方法时面给Value传nil，则会调用这个方法

- (NSDictionary<NSString *, id> *)dictionaryWithValuesForKeys:(NSArray<NSString *> *)keys;
//输入一组key,返回该组key对应的Value，再转成字典返回，用于将Model转到字典。

```


### 2、KVC的内部实现机制

#### KVO的`setValue:forKey`原理

我们先来一张图片可以直接明了的看清楚实现原理
 ![KVC2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVC2.png)

- 1、按照`setKey`，`_setKey`的顺序查找`成员方法`，如果找到方法，传递参数，调用方法
- 2、如果没有找到，查看`accessInstanceVariablesDirectly`的返回值（`accessInstanceVariablesDirectly`的返回值默认是`YES`），
    - 返回值为YES，按照`_Key,_isKey,Key,isKey`的顺序查找`成员变量`，如果找到，直接赋值，如果没有找到，调用`setValue:forUndefinedKey:`，抛出异常
    - 返回NO，直接调用`setValue:forUndefinedKey:`，抛出异常


#### KVO的`ValueforKey`原理
 ![KVC3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVC3.png)
 - 1、按照`getKey,key,isKey,_key`的顺序查找`成员方法`，如果找到直接调用`取值`
 - 2、如果没有找到，查看`accessInstanceVariablesDirectly`的返回值
 - 返回值为YES，按照`_Key,_isKey,Key,isKey`的顺序查找`成员变量`，如果找到，直接`取值`，如果没有找到，调用`setValue:forUndefinedKey:`，抛出异常
 - 返回NO，直接调用`setValue:forUndefinedKey:`，抛出异常
 

### 3、KVC的使用
#### KVC基础使用
假设我们有一个`Person`类，里面有一个`age`属性，我们给`age`赋值和取值

```
Person *p = [[Person alloc]init];
//赋值
[p setValue:@10 forKey:@"age"];
//取值
[p valueForKey:@"age"]
```
这也是最简单的使用方法了，也是我们平时项目中最常使用的方法了
#### KVC中使用keyPath
但是当`Person`类里面有一个`student`类，里面有一个`height`属性，我们怎么赋值`height`属性呢，
```
@interface Person : NSObject

@property (nonatomic,assign) int age;

@property (nonatomic,strong) Student *stu;

@end
```
我们能否这样写呢
```
Person *p = [[Person alloc]init];
//赋值
[p setValue:@10 forKey:@"stu.height"];
//取值
[p valueForKey:@"stu.height"]
```
我们运行程序打印结果
 ![KVC4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVC4.png)

打印结果是`this class is not key value coding-compliant for the key stu.height.`,所以这个方法是不可以的，但是iOS为我们提供了另一个方法`KeyPath`
```
Person *p = [[Person alloc]init];
p.stu = [[Student alloc]init];
[p setValue:@180 forKeyPath:@"stu.height"];
NSLog(@"valueForKey:%@",[p valueForKeyPath:@"stu.height"]);
NSLog(@"stu.height:%f",p.stu.height);
```
打印结果
 ![KVC5](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/images/KVC5.png)


`keyPath`除了对当前对象的属性进行赋值外，还可以对其更“深层”的对象进行赋值。KVC进行多级访问时，直接类似于属性调用一样用点语法进行访问即可。

#### KVC之集合属性
如果我们想要修改集合类型，我们该怎么办呢，不要着急，系统还是很友好的给我们提供了一些方法
```
- (NSMutableArray *)mutableArrayValueForKey:(NSString *)key;
- (NSMutableArray *)mutableArrayValueForKeyPath:(NSString *)keyPath

- (NSMutableSet *)mutableSetValueForKey:(NSString *)key
- (NSMutableSet *)mutableSetValueForKeyPath:(NSString *)keyPath

- (NSMutableOrderedSet *)mutableOrderedSetValueForKey:(NSString *)key 
- (NSMutableOrderedSet *)mutableOrderedSetValueForKeyPath:(NSString *)keyPath
```


简单使用
```
Person *p = [[Person alloc]init];
[[p mutableArrayValueForKey:@"list"] addObject:@"test"];
NSLog(@"mutableArrayValueForKey:%@",[p valueForKeyPath:@"list"]);
NSLog(@"%@",p.list);
```

关于`mutableArrayValueForKey:`的适用场景，网上一般说是在`KVO`中，因为`KVO的本质是系统监测到某个属性的内存地址或常量改变`时会添加上`- (void)willChangeValueForKey:(NSString *)key`和`- (void)didChangeValueForKey:(NSString *)key`方法来发送通知，但是如果直接改数组的话，内存地址并没有改变。

```
- (void)viewDidLoad {
	[super viewDidLoad];
	NSKeyValueObservingOptions options = NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld;
	_p = [[Person alloc]init];
	[_p addObserver:self forKeyPath:@"list" options:options context:nil];

}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
//    [_p.list addObject:@(arc4random()%255)];
//    NSLog(@"打印内存地址：%x",self.p.list);
//    NSLog(@"打印内容:%@",self.p.list);

	[[self.p mutableArrayValueForKey:@"list"] addObject:@(arc4random()%255)];
	NSLog(@"打印内存地址：%x",self.p.list);
	NSLog(@"打印内容:%@",self.p.list);

}
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSString *,id> *)change context:(void *)context{
	NSLog(@"%@",change);
}

-(void)dealloc{
	[_p removeObserver:self forKeyPath:@"list"]; //一定要在dealloc里面移除观察
}

```
我们分别用` [_p.list addObject:@(arc4random()%255)];`和`[[self.p mutableArrayValueForKey:@"list"] addObject:@(arc4random()%255)];`两个方法修改`list`内容，我们打印可知` [_p.list addObject:@(arc4random()%255)];`方法并没有改变`list`的内存地址，而使用`[[self.p mutableArrayValueForKey:@"list"] addObject:@(arc4random()%255)];`  ， `list`的内存地址改变了。

#### KVC之字典属性
KVC里面还有两个关于NSDictionary的方法
```
- (NSDictionary<NSString *, id> *)dictionaryWithValuesForKeys:(NSArray<NSString *> *)keys;
- (void)setValuesForKeysWithDictionary:(NSDictionary<NSString *, id> *)keyedValues;

```

`dictionaryWithValuesForKeys:`是指输入一组key，返回这组key对应的属性，再组成一个字典
`setValuesForKeysWithDictionary`是用来修改dic中对应key的属性

这个属性最常用到的地方就是字典转模型
例如我们有一个`Student`类，
```
@interface Student : NSObject
@property (nonatomic,assign) float height;
@property (nonatomic,assign) int age;
@property (nonatomic,strong) NSString *name;
@end
```
我们正常是怎么赋值呢
```
Student *stu = [[Student alloc]init];
stu.age = 10;
stu.name = @"jack";
stu.height = 180;
```
如果里面有100个属性呢，我们就需要写100遍
如果使用`setValuesForKeysWithDictionary`方法呢
```
Student *stu = [[Student alloc]init];
//在进行网络请求的时候dic不需要我们手写，是后台返回的
NSDictionary *dic = @{@"name":@"jack",@"height":@180,@"age":@10};
[stu setValuesForKeysWithDictionary:dic];
```
这样是不是简单了好多。


### 4、KVC异常处理


当根据KVC搜索规则，没有搜索到对应的key或者keyPath，则会调用对应的异常方法。异常方法的默认实现，在异常发生时会抛出一个`NSUndefinedKeyException`的异常，并且应用程序`Crash`。我们可以重写下面两个方法，根据业务需求合理的处理KVC导致的异常。
```
- (nullable id)valueForUndefinedKey:(NSString *)key;
- (void)setValue:(nullable id)value forUndefinedKey:(NSString *)key;
- (void)setNilValueForKey:(NSString *)key;
```

其中重写这两个方法，在`key`值不存在的时候，会走下面方法，而不会异常抛出
```
- (nullable id)valueForUndefinedKey:(NSString *)key;
- (void)setValue:(nullable id)value forUndefinedKey:(NSString *)key;
```
重写这个方法，当value值为nil的时候，会走下面方法，而不会异常抛出
```
- (void)setNilValueForKey:(NSString *)key;
```
 
 
 
 ###  5、KVC的正确性验证

在调用KVC时可以先进行验证，验证通过下面两个方法进行，支持key和keyPath两种方式。验证方法默认实现返回YES，可以通过重写对应的方法修改验证逻辑。

验证方法需要我们手动调用，并不会在进行KVC的过程中自动调用
```
- (BOOL)validateValue:(inout id _Nullable * _Nonnull)ioValue forKey:(NSString *)inKey error:(out NSError **)outError;
- (BOOL)validateValue:(inout id _Nullable * _Nonnull)ioValue forKeyPath:(NSString *)inKeyPath error:(out NSError **)outError;

```
 在validateValue方法的内部实现中，如果传入的value或key有问题，可以通过返回NO来表示错误，并设置NSError对象。
 
 因为还需要我们手动调用校验，感觉用处不太大。
 
 
 
 
 [参考demo](https://github.com/SunshineBrother/iOSDemo)
 
 







