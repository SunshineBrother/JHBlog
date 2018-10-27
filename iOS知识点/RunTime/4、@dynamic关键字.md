 ## @dynamic关键字
 Objective-C 2.0 提供了@dynamic关键字。这个关键字有两个作用：
 - 1 让编译器不要创建实现属性所用的实例变量；
 - 2 让编译器不要创建该属性的get和setter方法。
 
 @property(nonatomic, copy) NSString *string;
 默认情况下，编译器会为当前类自动生成一个NSString *_string的实例变量（如果想改变实例变量的名称可以用@synthesize关键字）。
 同时会生成两个名为
 ```
 /**getter 方法 */
 - (NSString *)string 
 /**setter 方法  */
 - (void)setString:(NSString *)String  
 ```
 但是
 
 @dynamic关键字
 
 就是让编译器编译的时候不要做这些事，同时在使用了存取方法时不用报错
 
 使得编辑认为存取方法会在运行时找到。
 
