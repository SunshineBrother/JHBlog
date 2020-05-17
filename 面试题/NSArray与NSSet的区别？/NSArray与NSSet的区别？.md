## NSArray与NSSet的区别？


NSArray内存中存储地址连续，而NSSet不连续
NSSet效率高，内部使用hash查找；NSArray查找需要遍历
NSSet通过anyObject访问元素，NSArray通过下标访问
