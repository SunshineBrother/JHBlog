## Auto Layout 是怎么进行自动布局的 


Auto Layout ，是苹果公司提供的一个基于约束布局，动态计算视图大小和位置的库，并且已经集成到了 Xcode 开发环境里

**Auto Layout 的来历**
- 1、一个是 1997 年，Auto Layout 用到的布局算法 `Cassowary` 被发明了出来；
- 2、另一个是 2011 年，苹果公司将 `Cassowary` 算法运用到了自家的布局引擎 Auto Layout 中。



`Cassowary`能够有效解析`线性等式系统`和`线性不等式系统`，用来表示用户界面中那些相等关系和不等关系。基于此，`Cassowary` 开发了一种规则系统，通过约束来描述视图间的关系。约束就是规则，这个规则能够表示出一个视图相对于另一个视图的位置


由于`Cassowary`算法让视图位置可以按照一种简单的布局思路来写，这些简单的相对位置描述可以在运行时动态地计算出视图具体的位置。视图位置的写法简化了，界面相关代码也就更易于维护。




### Auto Layout 的生命周期



Auto Layout 不只有布局算法 Cassowary，还包含了布局在运行时的生命周期等一整套布局引擎系统，用来统一管理布局的创建、更新和销毁。这一整套布局引擎系统叫作 `Layout Engine` ，是 Auto Layout 的核心，主导着整个界面布局



每个视图在得到自己的布局之前，`Layout Engine` 会将视图、约束、优先级、固定大小通过计算转换成最终的大小和位置。在 `Layout Engine `里，每当约束发生变化，就会触发 `Deffered Layout Pass`，完成后进入监听约束变化的状态。当再次监听到约束变化，即进入下一轮循环中


![界面布局过程](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS进阶/Auto%20Layout%20是怎么进行自动布局的/界面布局过程.png)


`Constraints Change` 表示的就是约束变化，添加、删除视图时会触发约束变化。`Activating 或 Deactivating`，设置 `Constant 或 Priority `时也会触发约束变化。`Layout Engine`在碰到约束变化后会重新计算布局，获取到布局后调用 `superview.setNeedLayout()`，然后进入 `Deferred Layout Pass`




`Deferred Layout Pass `的主要作用是做容错处理。如果有些视图在更新约束时没有确定或缺失布局声明的话，会先在这里做容错处理。接下来，`Layout Engine` 会**从上到下**调用 `layoutSubviews() `，通过 Cassowary 算法计算各个子视图的位置，算出来后将子视图的 frame 从 Layout Engine 里拷贝出来。

**总结**
 
Auto Layout拥有一套Layout Engine引擎，由它来主导页面的布局。App启动后，主线程的Run Loop会一直处于监听状态，当约束发生变化后会触发Deffered Layout Pass（延迟布局传递），在里面做容错处理（约束丢失等情况）并把view标识为dirty状态，然后Run Loop再次进入监听阶段。当下一次刷新屏幕动作来临（或者是调用layoutIfNeeded）时，Layout Engine 会从上到下调用 layoutSubviews() ，通过 Cassowary算法计算各个子视图的位置，算出来后将子视图的frame从Layout Engine拷贝出来，接下来的过程就跟手写frame是一样的了
































































































