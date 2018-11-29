## atomic 一定是线程安全的吗 

```
@property (nonatomic,copy) NSString *name;
```

**nonatomic内部实现**

```
//mrc 环境
//implementation
@synthesize name = _name;

//set
-(void)setName:(NSString *)name
{
if(_name != name)
{
[_name release];
_name = [name retain];
}
}
//get
-(NSString *)name
{
return _name;
}
 
```

**atomic内部实现**

系统生成的getter/setter方法会进行加锁操作,注意:这个锁仅仅保证了getter和setter存取方法的线程安全.

```
//mrc 环境
//implementation
@synthesize name = _name;

//set
-(void)setName:(NSString *)name
{
//同步代码块
@synchronized (self) {

if(_name != name)
{
[_name release];
_name = [name retain];
}
}
}
//get
-(NSString *)name
{
NSString *name = nil;
//同步代码块
@synchronized (self) {

name = [[_name retain] autorelease];
}
return name;
}
 
```



很多文章谈到atomic和nonatomic的区别时,都说atomic是线程安全,其实这个说法是不准确的.
atomic只是对属性的getter/setter方法进行了加锁操作,这种安全仅仅是set/get 的读写安全,并非真正意义上的线程安全,因为线程安全还有读写之外的其他操作(比如:如果当一个线程正在get或set时,又有另一个线程同时在进行release操作,可能会直接crash)

 









