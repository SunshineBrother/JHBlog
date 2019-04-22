## 重构UIViewController

对UIViewController的重构主要分成两个方面
- 1、拆分UIViewController
- 2、合并各个小的模块

### 拆分UIViewController

写了那么多Controller，让你来说下一个Controller都细分为哪些更小的功能单位，你能随口说出来么？只有做过足够多的业务，才能慢慢对Controller的构成有自己的理解。

当然可以回答说MVC或者MVP，但这个答案粒度太粗，一个Controller内部会发生哪些事可以说的更细，我们看下VIPER的答案：


VIPER 可以是视图 (View)，交互器 (Interactor)，展示器 (Presenter)，实体 (Entity) 以及路由 (Routing) 的首字母缩写。简明架构将一个应用程序的逻辑结构划分为不同的责任层。这使得它更容易隔离依赖项 (如数据库)，也更容易测试各层间的边界处的交互：

- View视图：根据展示器的要求显示界面，并将用户输入反馈给展示器。可以分解成更多的子View，最后合成一个树形结构。
- Interactor交互器：包含由用例指定的业务逻辑。
- Presenter展示器：包含为显示（从交互器接受的内容）做的准备工作的相关视图逻辑，并对用户输入进行反馈（从交互器获取新数据）。
- Entity实体：包含交互器要使用的基本模型对象。自然是代表Model。
- Routing路由：包含用来描述屏幕显示和显示顺序的导航逻辑。


 ![VIPER](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/UIViewController/VIPER.png)


View不用多说，可以分解成更多的子View，最后合成一个树形结构。

Entity自然是代表Model。


MVC当中的C，MVP当中的P，被细分成了Interactor，Presenter，和Routing。这三个角色各自负责什么职责呢？


Routing比较清楚，处理页面之间的跳转。我见过的项目代码里，很少有把这一部分单独拎出来的，但其实很有意义，这部分代表的是不同Controller之间耦合依赖的方式，无论是从类关系描述的角度还是Debug的角度，都能帮助我们快速定位代码。

**Interactor**

Interactor和Presenter初看起来很类似，似乎都是在处理业务逻辑。但业务逻辑其实是个大的归类，可以描述任何一种业务场景和行为。Interactor当中有个很重要的术语：use case，这个术语很多技术文章中都会遇见，它代表的是一个完整的，独立的，细分过后的业务流程，比如我们App当中的登录模块，它是一个业务单位，但它其实可以进一步的细分为很多的use case：

use case 1: 验证邮箱长度

use case 2: 密码强度检验

use case 3: 从Server查询user name是否可用

…

user case N

`VIPER当中interactor的说法是强化大家写单独的use case的意识，打开interactor.m，看到一个函数代表一个use case，同一类的use case再用#pragma mark 归在一块，别人看你代码时能不赏心悦目吗`

**Presenter**

Presenter可以看做是上面一个个use case的使用者和响应者。使用者将各个use case串联起来描述一个完整详细的业务流程，比如我们的登录模块，每次用户点击按钮注册的时候，会触发一系列的use case，从检验用户输入合法性，设备网络状态，服务器资源是否可用，到最后处理结果并展示，这就是一个完整的业务流程，这个流程由Presenter来描述。响应者表示Presenter在接收到服务器反馈之后进一步改变本地的状态，比如view的展示，新的数据修改等，甚至会调用Routing发生页面跳转。


说到这里就比较明了了，interactor和routing都是服务的提供方，presenter是服务的使用和集成方。VIPER说白了不过是对传统的MVC当中的C做了进一步细分。


**代码结构**


在说控制器瘦身之前，首先要做的的是保证代码结构的清晰化。良好的代码结构有利于代码的传承、可读性以及可维护性。通常笔者都是这样控制代码结构的：

```
#pragra mark - life cycle 

#pragra mark - notification 

#pragra mark - action 

#pragra mark - UITableViewDelegate
.....总之这里是各种代理就对了

#pragra mark - UI

#pragra mark - setter & getter
不要在除了getter之外的结构中设置view基本坐标、属性等。 getter方法中不要添加比较重要重要的业务逻辑，重要的业务逻辑应该单独拿出来，放在对应的pragra mark 下，否则对于代码的阅读者来说，比较难以定位逻辑的入口位置。实际开发中遇到过多次这样的情况，焦头烂额的寻找关键逻辑入口处，纵里寻她千百度，结果它却躺在 getter方法中


#pragra mark - Interactor的case
在case比较多的情况下，我们可以专门创建一个`interactor.m`类来管理相关case

#pragra mark - Routing 跳转任务

```

#### ViewController 瘦身

- 1、将 UITableView 的 Data Source 分离到另外一个类中
- 2、将数据获取和转换的逻辑分别到另外一个类中，也就是网络层，可以单独创建一个`dataController`来处理网络请求数据
- 3、将拼装控件的逻辑，分离到另外一个类中。就是复杂的视图，构造专门的 UIView 的子类，来负责这些控件的拼装。这是最彻底和优雅的方式，不过稍微麻烦一些的是，你需要把这些控件的事件回调先接管，再都一一暴露回 Controller。
- 4、专门构造存储类，数据的存储也应该由专门的对象来做，用UserAgent 的类专门来处理本地数据的存取。数据存取放在专门的类中，就可以针对存取做额外的事情了。比如：
    - 对一些热点数据增加缓存
    - 处理数据迁移相关的逻辑
































[使用 VIPER 构建 iOS 应用](https://objccn.io/issue-13-5/)

[深度重构UIViewController](http://mrpeak.cn/blog/controller/)

[iOS应用层架构之CDD](http://www.mrpeak.cn/blog/cdd/)

[被误解的 MVC 和被神化的 MVVM](https://mp.weixin.qq.com/s?__biz=MjM5NTIyNTUyMQ==&mid=407454565&idx=1&sn=f2c207e30f700219d5811371b34b8cf9&scene=21#wechat_redirect)
 
 [猿题库 iOS 客户端架构设计](https://mp.weixin.qq.com/s?__biz=MjM5NTIyNTUyMQ==&mid=444322139&idx=1&sn=c7bef4d439f46ee539aa76d612023d43&scene=0#wechat_redirect)

[UIViewController的瘦身计划（iOS架构思想篇）](https://www.jianshu.com/p/98fa80eebc52)

[继承和面向接口（iOS架构思想篇）](https://www.jianshu.com/p/39e6a8409476)








 
 
 
