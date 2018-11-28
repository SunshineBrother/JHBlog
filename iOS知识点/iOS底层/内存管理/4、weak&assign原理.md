## weak&assign实现原理

### Weak实现原理

`weak`其实就是一个hash表，key是所指`对象的地址`，value是`weak指针的地址数组`


**weak 实现原理的概括**

Runtime维护了一个weak表，用于存储指向某个对象的所有weak指针。weak表其实是一个hash（哈希）表，Key是所指对象的地址，Value是weak指针的地址（这个地址的值是所指对象的地址）数组

weak 的实现原理可以概括一下三步：

- 1、初始化时：runtime会调用objc_initWeak函数，初始化一个新的weak指针指向对象的地址。

- 2、添加引用时：objc_initWeak函数会调用 objc_storeWeak() 函数， objc_storeWeak() 的作用是更新指针指向，创建对应的弱引用表。

- 3、释放时，调用clearDeallocating函数。clearDeallocating函数首先根据对象地址获取所有weak指针地址的数组，然后遍历这个数组把其中的数据设为nil，最后把这个entry从weak表中删除，最后清理对象的记录。


#### 1、初始化


我们下载源码，很多Fundation框架下的东西都是能够在`NSObject.mm`文件中找到的，我们关于weak的也是从这里查找的。我们发现有一个`objc_initWeak`方法，这个就是weak初始化函数

```
objc_initWeak(id *location, id newObj)
{
if (!newObj) {//无效对象直接导致指针释放
*location = nil;
return nil;
}

return storeWeak<DontHaveOld, DoHaveNew, DoCrashIfDeallocating>
(location, (objc_object*)newObj);
}
```

### 2、更新指针指向，创建对应的弱引用表

我们`storeWeak`表面意思是`weak商店`,其实weak应该就是在`storeWeak`函数里面进行了进一步的处理。点击进入

```
//我们看传参
//1、location地址
//2、newObj新的对象
static id 
storeWeak(id *location, objc_object *newObj)
{
assert(haveOld  ||  haveNew);
if (!haveNew) assert(newObj == nil);

Class previouslyInitializedClass = nil;
id oldObj;

//声明新旧两个SideTable散列表
SideTable *oldTable;
SideTable *newTable;

 
retry:
if (haveOld) {
// 更改指针，获得以 oldObj 为索引所存储的值地址
oldObj = *location;
oldTable = &SideTables()[oldObj];
} else {
oldTable = nil;
}
if (haveNew) {
// 更改新值指针，获得以 newObj 为索引所存储的值地址
newTable = &SideTables()[newObj];
} else {
newTable = nil;
}

// 加锁操作，防止多线程中竞争冲突
SideTable::lockTwo<haveOld, haveNew>(oldTable, newTable);
// 避免线程冲突重处理
// location 应该与 oldObj 保持一致，如果不同，说明当前的 location 已经处理过 oldObj 可是又被其他线程所修改
if (haveOld  &&  *location != oldObj) {
SideTable::unlockTwo<haveOld, haveNew>(oldTable, newTable);
goto retry;
}

 
if (haveNew  &&  newObj) {
Class cls = newObj->getIsa();
if (cls != previouslyInitializedClass  &&  
!((objc_class *)cls)->isInitialized()) 
{
// 解锁
SideTable::unlockTwo<haveOld, haveNew>(oldTable, newTable);
// 对其 isa 指针进行初始化
_class_initialize(_class_getNonMetaClass(cls, (id)newObj));
// 如果该类已经完成执行 +initialize 方法是最理想情况
// 如果该类 +initialize 在线程中
// 例如 +initialize 正在调用 storeWeak 方法
// 需要手动对其增加保护策略，并设置 previouslyInitializedClass 指针进行标记
previouslyInitializedClass = cls;

goto retry;
}
}
//  清除旧值
if (haveOld) {
weak_unregister_no_lock(&oldTable->weak_table, oldObj, location);
}

//  分配新值 
if (haveNew) {
newObj = (objc_object *)
weak_register_no_lock(&newTable->weak_table, (id)newObj, location, 
crashIfDeallocating);
  
if (newObj  &&  !newObj->isTaggedPointer()) {
newObj->setWeaklyReferenced_nolock();
}

 
*location = (id)newObj;
}
else {
 
}

SideTable::unlockTwo<haveOld, haveNew>(oldTable, newTable);


return (id)newObj;
}
```


我们注意到在刚进入`storeWeak`函数的时候，就初始化了新旧两个`SideTable`，我们点击进入

```
struct SideTable {
spinlock_t slock;
RefcountMap refcnts;
weak_table_t weak_table;

}
```
我们发现`SideTable`是一个结构体
- 1、`spinlock_t slock;`  保证原子操作的自旋锁
- 2、`RefcountMap refcnts;`   引用计数的 hash 表
- 3、`weak_table_t weak_table;`  weak 引用全局 hash 表


我们是研究`weak`的，所以我们要研究一下`weak_table_t`这个hash表
```
struct weak_table_t {
weak_entry_t *weak_entries;
size_t    num_entries;
uintptr_t mask;
uintptr_t max_hash_displacement;
};
```
- 1、`weak_entry_t *weak_entries;`  保存了所有指向指定对象的 weak 指针
- 2、`size_t    num_entries;` 存储空间
- 3、`uintptr_t mask;` 参与判断引用计数辅助量
- 4、`uintptr_t max_hash_displacement;` hash key 最大偏移值

这是一个全局弱引用hash表。使用`对象的地址`作为key ，用 `weak_entry_t`类型结构体对象作为value



我们看字面意思`weak_entry_t`就是weak条目的意思，里面应该包含了weak的信息
```
struct weak_entry_t {
DisguisedPtr<objc_object> referent;
union {
struct {
weak_referrer_t *referrers;
uintptr_t        out_of_line_ness : 2;
uintptr_t        num_refs : PTR_MINUS_2;
uintptr_t        mask;
uintptr_t        max_hash_displacement;
};
struct {
// out_of_line_ness field is low bits of inline_referrers[1]
weak_referrer_t  inline_referrers[WEAK_INLINE_COUNT];
};
};
```

`weak_entry_t`是存储在弱引用表中的一个内部结构体，它负责维护和存储指向一个对象的所有弱引用hash表











[下面内容转载自：我就叫Sunny怎么了](https://weibo.com/u/1364395395?from=myfollow_all&is_all=1#_rnd1543404448122)

【从历年weak看iOS面试】
2013年
面试官：代理用weak还是strong?
我 ：weak 。 
面试官：明天来上班吧

2014年
面试官：代理为什么用weak不用strong?
我 ： 用strong会造成循环引用。
面试官：明天来上班吧

2015年
面试官：weak是怎么实现的？
我 ：weak其实是 系统通过一个hash表来实现对象的弱引用
面试官：明天来上班吧

2016年
面试官：weak是怎么实现的？
我 ：runtime维护了一个weak表，用于存储指向某个对象的所有weak指针。weak表其实是一个hash（哈希）表，key是所指对象的地址，Value是weak指针的地址（这个地址的值是所指对象指针的地址）数组。
面试官：明天来上班吧

2017年
面试官：weak是怎么实现的？
我 ：    1    初始化时：runtime会调用objc_initWeak函数，初始化一个新的weak指针指向对象的地址。
2       添加引用时：objc_initWeak函数会调用 storeWeak() 函数， storeWeak() 的作用是更新指针指向，创建对应的弱引用表。
3    释放时,调用clearDeallocating函数。clearDeallocating函数首先根据对象地址获取所有weak指针地址的数组，然后遍历这个数组把其中的数据设为nil，最后把这个entry从weak表中删除，最后清理对象的记录。
面试官：明天来上班吧

2018年
面试官：weak是怎么实现的？
我 ：跟2017年说的一样，还详细补充了objc_initWeak, storeWeak, clearDeallocating的实现细节。
面试官：小伙子基础不错。13k ,996干不干？干就明天来上班。。   下一个

2019年
面试官：weak是怎么实现的？
我 ：     别说了，拿纸来，我动手实现一个。
面试官：等写完后，面试官慢悠悠的说，小伙子不错，我考虑考虑，你先回去吧













