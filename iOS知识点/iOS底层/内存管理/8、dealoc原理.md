## dealloc原理

我们还是直接从源码中查找，我们在`NSObject.mm`可以查找到`dealloc`函数
```
- (void)dealloc {
_objc_rootDealloc(self);
}
```

点击进入`_objc_rootDealloc`函数
```
_objc_rootDealloc(id obj)
{
assert(obj);

obj->rootDealloc();
}
```

里面还是没有我们想要的，点击`rootDealloc`

```
objc_object::rootDealloc()
{
if (isTaggedPointer()) return;
object_dispose((id)this);
}
```
这个里面有我们想要的信息
- 1、首先判断对象是不是`isTaggedPointer`，如果是`TaggedPointer`那么没有采用引用计数技术，所以直接return
- 2、不是`TaggedPointer`，就去销毁这个对象`object_dispose`


我们继续点击`object_dispose`
```
id 
object_dispose(id obj)
{
if (!obj) return nil;

objc_destructInstance(obj);    
free(obj);

return nil;
}
```

里面仅仅是简单的判断，我们还需要继续找我们需要的东西，点击`objc_destructInstance`函数

```
void *objc_destructInstance(id obj) 
{
if (obj) {
// Read all of the flags at once for performance.
bool cxx = obj->hasCxxDtor();
bool assoc = obj->hasAssociatedObjects();

// This order is important.
if (cxx) object_cxxDestruct(obj);
if (assoc) _object_remove_assocations(obj);//清除成员变量
obj->clearDeallocating(); //将指向当前对象的弱引用指针置为nil
}

return obj;
}
```


**主要步骤**
- 1、首先判断对象是不是`isTaggedPointer`，如果是`TaggedPointer`那么没有采用引用计数技术，所以直接return
- 2、不是`TaggedPointer`
    - 1、清除成员变量
    - 2、将指向当前对象的弱引用指针置为nil


























