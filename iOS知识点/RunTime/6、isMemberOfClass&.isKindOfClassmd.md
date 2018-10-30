## isKindOfClass和isMemberOfClass区别 

我们直接源码查找相关实现
```
+ (BOOL)isMemberOfClass:(Class)cls {
return object_getClass((id)self) == cls;
}

- (BOOL)isMemberOfClass:(Class)cls {
return [self class] == cls;
}

+ (BOOL)isKindOfClass:(Class)cls {
for (Class tcls = object_getClass((id)self); tcls; tcls = tcls->superclass) {
if (tcls == cls) return YES;
}
return NO;
}

- (BOOL)isKindOfClass:(Class)cls {
for (Class tcls = [self class]; tcls; tcls = tcls->superclass) {
if (tcls == cls) return YES;
}
return NO;
}
```

**- isMemberOfClass**

一个对象是否是指定类的实例对象
```
- (BOOL)isMemberOfClass:(Class)cls {
return [self class] == cls;
}
```












