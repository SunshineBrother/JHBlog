## Load和Initialize实现原理 


### +Load实现原理

> +load方法会在`runtime`加载`类`、`分类`时调用

> 每个类、分类的+load，在程序运行过程中`只调用一次`

> +load方法是根据方法`地址`直接调用，并不是经过objc_msgSend函数调用

**调用顺序**

- 1、先调用类的+load
    - 按照编译先后顺序调用（先编译，先调用）
    - 调用子类的+load之前会先调用父类的+load
- 2、再调用分类的+load
    - 按照编译先后顺序调用（先编译，先调用）


**objc4源码解读过程**
objc-os.mm 文件
- _objc_init
- load_images
- prepare_load_methods
    - schedule_class_load
    - add_class_to_loadable_list
    - add_category_to_loadable_list
- call_load_methods
    - call_class_loads
    - call_category_loads


`_objc_init`方法是RunTime运行的入口
```
void _objc_init(void)
{
    static bool initialized = false;
    if (initialized) return;
    initialized = true;

    // fixme defer initialization until an objc-using image is found?
    environ_init();
    tls_init();
    static_init();
    lock_init();
    exception_init();

    _dyld_objc_notify_register(&map_images, load_images, unmap_image);
}
```
>小知识：`images`是镜像的意思

我们在`_objc_init`方法中找到`load_images`，`load_images`是Load加载镜像的意思，所有我们可以猜测这个里面应该有我们load的加载方法的相关实现


我们点击进入`load_images`方法
```
load_images(const char *path __unused, const struct mach_header *mh)
{
    // Return without taking locks if there are no +load methods here.
    if (!hasLoadMethods((const headerType *)mh)) return;

    recursive_mutex_locker_t lock(loadMethodLock);

    // Discover load methods
    {
        rwlock_writer_t lock2(runtimeLock);
        prepare_load_methods((const headerType *)mh);
    }

    // Call +load methods (without runtimeLock - re-entrant)
    call_load_methods();
}
```
里面有两个需要我们注意的
- 1、`prepare_load_methods((const headerType *)mh)`准备加载Load方法，我们也可以看到上面的官方文档解释也是这个意思
- 2、`call_load_methods()` 加载load方法

我们点击进入`prepare_load_methods((const headerType *)mh)`准备加载Load方法

```
void prepare_load_methods(const headerType *mhdr)
{
    size_t count, i;

    runtimeLock.assertWriting();

    classref_t *classlist = 
    _getObjc2NonlazyClassList(mhdr, &count);
    for (i = 0; i < count; i++) {
        schedule_class_load(remapClass(classlist[i]));
    }

    category_t **categorylist = _getObjc2NonlazyCategoryList(mhdr, &count);
    for (i = 0; i < count; i++) {
    category_t *cat = categorylist[i];
    Class cls = remapClass(cat->cls);
    if (!cls) continue;  // category for ignored weak-linked class
        realizeClass(cls);
        assert(cls->ISA()->isRealized());
        add_category_to_loadable_list(cat);
    }
}
```

我们可以看到执行顺序
- 1、`schedule_class_load(remapClass(classlist[i]));`,这个是把类中的`Load`方法添加到数组中
- 2、`add_category_to_loadable_list(cat);`这个是把分类中的`load`方法添加到数组中

**查看类的load方法**

我们查看`schedule_class_load(remapClass(classlist[i]));`方法里面还有哪些实现

```
static void schedule_class_load(Class cls)
{
    if (!cls) return;
    assert(cls->isRealized());  // _read_images should realize

    if (cls->data()->flags & RW_LOADED) return;

    // Ensure superclass-first ordering
    schedule_class_load(cls->superclass);

    add_class_to_loadable_list(cls);
    cls->setInfo(RW_LOADED); 
}
```
- 1、`schedule_class_load(cls->superclass);` 把父类load先添加到数组中
- 2、`add_class_to_loadable_list(cls);`把自己的load方法添加到数组中


走到这里我们大概是清楚了类中load方法的加载添加过程，就是先把`父类添加带数组中，然后再把自己添加到数组中`




**查看分类的load方法**


我们点击`add_category_to_loadable_list(cat)`进入查看方法实现
```
void add_category_to_loadable_list(Category cat)
{
    IMP method;

    loadMethodLock.assertLocked();

    method = _category_getLoadMethod(cat);

    // Don't bother if cat has no +load method
    if (!method) return;

    if (PrintLoading) {
        _objc_inform("LOAD: category '%s(%s)' scheduled for +load", 
        _category_getClassName(cat), _category_getName(cat));
    }

    if (loadable_categories_used == loadable_categories_allocated) {
        loadable_categories_allocated = loadable_categories_allocated*2 + 16;
        loadable_categories = (struct loadable_category *)
        realloc(loadable_categories,
        loadable_categories_allocated *
        sizeof(struct loadable_category));
    }

    loadable_categories[loadable_categories_used].cat = cat;
    loadable_categories[loadable_categories_used].method = method;
    loadable_categories_used++;
}
```
`loadable_categories_used++;`分类没有什么特殊的方法，应该就是按照编译顺序添加到数组的。


**实现**

我们刚才看到了类分类中的添加顺序，我们在来看看加载顺序
点击`call_load_methods();`进入相关实现
```
void call_load_methods(void)
{
    static bool loading = NO;
    bool more_categories;

    loadMethodLock.assertLocked();

    // Re-entrant calls do nothing; the outermost call will finish the job.
    if (loading) return;
    loading = YES;

    void *pool = objc_autoreleasePoolPush();

    do {
        // 1. Repeatedly call class +loads until there aren't any more
        while (loadable_classes_used > 0) {
        call_class_loads();
    }

    // 2. Call category +loads ONCE
    more_categories = call_category_loads();

    // 3. Run more +loads if there are classes OR more untried categories
    } while (loadable_classes_used > 0  ||  more_categories);

    objc_autoreleasePoolPop(pool);

    loading = NO;
}
```
上面直接有官方文档给我们的顺序
- 1、`call_class_loads();`加载类中load方法
- 2、`more_categories = call_category_loads()`加载分类中load方法



**Demo**
我们这里来一个测试demo
- 父类`Person`
    - 1、分类`Person+Run.h`
    - 2、分类`Person+Eat`
- 2、子类
    - 1、`Student`
    - 2、`Teacher`


编译顺序
![Load1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/分类/Load1.png)

  
打印顺序

![Load2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/分类/Load2.png)


- 1、先编译`Teacher`但是最先打印`Person`
- 2、分类`Person+Run`在子类`Student`之前编译，但是打印确实先打印`Student`

所有上面总结是十分准确的
- 1、先调用类的+load
    - 按照编译先后顺序调用（先编译，先调用）
    - 调用子类的+load之前会先调用父类的+load
- 2、再调用分类的+load
    - 按照编译先后顺序调用（先编译，先调用）


我们是否注意到了另一个问题，为什么在有分类的时候还加载类的`load`方法，不应该是分类覆盖类吗？

我们在查看`load`的源码实现的时候发现，+load方法是根据方法`地址`直接调用，并不是经过`objc_msgSend`函数调用，如果使用`objc_msgSend`会出现分类覆盖类，但是`load`直接是根据`指针`找方法的，所以不会覆盖。



### Initialize实现原理 

> +initialize方法会在类`第一次接收到消息`时调用


**调用顺序**
- 先调用父类的+initialize，再调用子类的+initialize(先初始化父类，再初始化子类，每个类只会初始化1次)
- +initialize和+load的很大区别是，+initialize是通过objc_msgSend进行调用的，所以有以下特点
    - 如果子类没有实现+initialize，会调用父类的+initialize（所以父类的+initialize可能会被调用多次）
    - 如果分类实现了+initialize，就覆盖类本身的+initialize调用

**objc4源码解读过程**

objc-runtime-new.mm
- class_getInstanceMethod
- lookUpImpOrNil
- lookUpImpOrForward
- _class_initialize
- callInitialize
- objc_msgSend(cls, SEL_initialize)

我们在`objc-runtime-new.mm`文件中找到`class_getInstanceMethod`，里面就有一个主要实现方法`lookUpImpOrNil`

```
Method class_getInstanceMethod(Class cls, SEL sel)
{
    if (!cls  ||  !sel) return nil;
    #warning fixme build and search caches
    lookUpImpOrNil(cls, sel, nil, 
    NO/*initialize*/, NO/*cache*/, YES/*resolver*/);
    #warning fixme build and search caches
    return _class_getMethod(cls, sel);
}
```
里面没有什么实现我们继续点击`lookUpImpOrNil`进入实现
```
IMP lookUpImpOrNil(Class cls, SEL sel, id inst, 
bool initialize, bool cache, bool resolver)
    {
    IMP imp = lookUpImpOrForward(cls, sel, inst, initialize, cache, resolver);
    if (imp == _objc_msgForward_impcache) return nil;
    else return imp;
}
```

里面好像还是没有我们想要的具体实现，继续点击`lookUpImpOrForward`查看实现
```
if (initialize  &&  !cls->isInitialized()) {
    runtimeLock.unlockRead();
    _class_initialize (_class_getNonMetaClass(cls, inst));
    runtimeLock.read();
}
```
这个里面有一个`if`判断里面有一些东西，就是在没有实现`isInitialized`的时候，调用`_class_initialize`方法，我们点击进入查看相关实现
```
if (supercls  &&  !supercls->isInitialized()) {
    _class_initialize(supercls);
}
```
```
callInitialize(cls);
```
里面有这两个主要的函数
- 1、第一个是判断是否存在父类，以及父类是否实现`initialize`方法，如果没有实现就去实现
- 2、去实现自己的`initialize`方法。



我们在点击`callInitialize`发现具体是通过`objc_msgSend`来实现的。
```
void callInitialize(Class cls)
{
((void(*)(Class, SEL))objc_msgSend)(cls, SEL_initialize);
asm("");
}
```

**Demo**
测试案例1
我们创建父类`Person`，然后创建子类`Student`&`Teacher`，子类不实现`initialize`方法，父类实现该方法
```
[Teacher alloc];
[Student alloc];
```

![initialize](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/分类/initialize.png)

结果打印三次`[Person initialize]`方法，打印一次我们是能够想到了，因为实现过程是先看看父类有没有已经实现，如果没有实现就先实现父类的。但是另外两次是怎么来的呢。

`[Student alloc]`的实现大概是这样的
```
objc_msgSend([Person class], @selector(initialize));
objc_msgSend([Student class], @selector(initialize));
```
- 1、第一步就是实现父类的`initialize`方法
- 2、第二步，Student先查找自己元类有没有`initialize`方法，如果自己元类没有实现，就向上查找父类元类有没有`initialize`方法，如果有就执行，没有继续向上查找 



测试案例2

我们创建父类`Person`，然后创建分类`Person+Eat`，都是实现`initialize`方法
```
[Person alloc];
```

![initialize2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS底层/分类/initialize2.png)

这句代码就是证明了`如果分类实现了+initialize，就覆盖类本身的+initialize调用`



### 总结


load、initialize方法的区别什么？
- 1.调用方式
 - 1> load是根据函数地址直接调用
- 2> initialize是通过objc_msgSend调用

-2.调用时刻
    - 1> load是runtime加载类、分类的时候调用（只会调用1次）
    - 2> initialize是类第一次接收到消息的时候调用，每一个类只会initialize一次（父类的initialize方法可能会被调用多次）

load、initialize的调用顺序？

1.load
- 1> 先调用类的load
    - a) 先编译的类，优先调用load
    - b) 调用子类的load之前，会先调用父类的load

- 2> 再调用分类的load
    - a) 先编译的分类，优先调用load

2.initialize
- 1> 先初始化父类
- 2> 再初始化子类（可能最终调用的是父类的initialize方法）


