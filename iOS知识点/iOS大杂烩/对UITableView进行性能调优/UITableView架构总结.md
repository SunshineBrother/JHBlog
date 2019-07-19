## UITableView总结

UITableView是iOS开发者最常用的一个控件了，虽然我们都用了好多年，但是应该有相当一部分人对UITableView的使用并不是很理想，最近我整理了一些稍微高级一点的用法。

欢迎大家参考学习，这里面引用别人的文章，这里会注明出处的。


### 如何构建具有多种Cell类型的表视图

![多种Cell类型](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/对UITableView进行性能调优/多种Cell类型.png)

在具有静态 Cell 的表视图中，其 Cell 的数量和顺序是恒定的。要实现这样的表视图非常简单，与实现常规 UIView 没有太大的区别。

只包含一种内容类型的动态 Cell 的表视图：Cell 的数量和顺序是动态变化的，但所有 Cell 都有相同类型的内容。在这里你可以使用可复用 Cell 。这也是最常见的表视图样式

包含具有不同内容类型的动态 Cell 的表视图：数量，顺序和 Cel l类型是动态的。实现这种表视图是最有趣和最具挑战性的。

如上图所示，所有数据都来自后端，我们无法控制下一个请求将接收哪些数据：可能没有「about」的信息，或者「Friends」部分可能是空的。在这种情况下，我们根本不需要展示这些 Cell。最后，我们必须知道用户点击的 Cell 类型并做出相应的反应

首先，让我们来先确定问题。

我经常在不同项目中看到这样的方法：在 UITableView 中根据 index 配置 Cell。
```
override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {

if indexPath.row == 0 {
//configure cell type 1
} else if indexPath.row == 1 {
//configure cell type 2
}
....
}

```
同样在代理方法 didSelectRowAt 中几乎使用相同的代码：
```
override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {

if indexPath.row == 0 {
//configure action when tap cell 1
} else if indexPath.row == 1 {
//configure action when tap cell 1
}
....
}

 
```
直到你想要重新排序 Cell 或在表视图中删除或添加新的 Cell 的那一刻，代码都将如所预期的工作。如果你更改了一个 index，那么整个表视图的结构都将破坏，你需要手动更新 cellForRowAt 和 didSelectRowAt 方法中所有的 index。

 >这样的代码是十分的糟糕的，它无法重用，可读性差，也不遵循任何编程模式，因为它混合了视图和 Model。

这个时候我们可以使用MVVM模式来解决这个问题，如果想要更加方便理解，可以下载代码进行参考。


**Model部分**
 
我们需要创建一个 Model，它将保存我们从 JSON 读取的所有数据
```
class Profile {
var fullName: String?
var pictureUrl: String?
var email: String?
var about: String?
var friends = [Friend]()
var profileAttributes = [Attribute]()
}

class Friend {
var name: String?
var pictureUrl: String?
}

class Attribute {
var key: String?
var value: String?
}
 
```

**ViewModel部分**

我们的 Model 已准备就绪，所以我们需要创建 ViewModel。它将负责向我们的 TableView 提供数据。

我们将创建 5 个不同的 table sections：
- Full name and Profile Picture
- About
- Email
- Attributes
- Friends


前三个 section 各只有一个 Cell，最后两个 section 可以有多个 Cell，具体取决于我们的 JSON 文件的内容。

因为我们的数据是动态的，所以 Cell 的数量不是固定的，并且我们对每种类型的数据使用不同的 tableViewCell，因此我们需要使用正确的 ViewModel 结构。首先，我们必须区分数据类型，以便我们可以使用适当的 Cell。当你需要在 Swift 中使用多种类型并且可以轻松的切换时，最好的方法是使用枚举。那么让我们开始使用 ViewModelItemType 构建 ViewModel：

```
enum ProfileViewModelItemType {
case nameAndPicture
case about
case email
case friend
case attribute
}
```
每个 enum case 表示 TableViewCell 需要的不同的数据类型。但是，我由于们希望在同一个表视图中使用数据，所以需要有一个单独的 dataModelItem，它将决定所有属性。我们可以通过使用协议来实现这一点，该协议将为我们的 item 提供属性计算：
 ```
 protocol ProfileViewModelItem {
 var type: ProfileViewModelItemType { get }
 var sectionTitle: String { get }
 var rowCount: Int { get }
 }
 ```

每个 item 都需要遵守协议。但在我们开始之前，让我们再向简洁有序的项目迈出一步：为我们的协议提供一些默认值。在 swift 中，我们可以使用协议扩展为协议提供默认值，如果 rowCount 为 1，我们就不必为 item 的 rowCount 赋值了，它将为你节省一些冗余的代码。
```
extension ProfileViewModelItem {
var rowCount: Int {
return 1
}
}
```

我们分别为5中cell创建5中model

例如用户姓名头衔信息的`ProfileViewModelNamePictureItem`，每一个model都要遵循`ProfileViewModelItem`协议

```
class ProfileViewModelNamePictureItem: ProfileViewModelItem {
var type: ProfileViewModelItemType {
return .nameAndPicture
}

var sectionTitle: String {
return "Main Info"
}

var rowCount: Int {
return 1
}

var name: String
var pictureUrl: String

init(name: String, pictureUrl: String) {
self.name = name
self.pictureUrl = pictureUrl
}
}

```
其他几种model相似
```
class ProfileViewModelAboutItem: ProfileViewModelItem {
var type: ProfileViewModelItemType {
return .about
}

var sectionTitle: String {
return "About"
}

var rowCount: Int {
return 1
}

var about: String

init(about: String) {
self.about = about
}
}

class ProfileViewModelEmailItem: ProfileViewModelItem {
var type: ProfileViewModelItemType {
return .email
}

var sectionTitle: String {
return "Email"
}

var rowCount: Int {
return 1
}

var email: String

init(email: String) {
self.email = email
}
}

class ProfileViewModeAttributeItem: ProfileViewModelItem {
var type: ProfileViewModelItemType {
return .attribute
}

var sectionTitle: String {
return "Attributes"
}

var rowCount: Int {
return attributes.count
}

var attributes: [Attribute]

init(attributes: [Attribute]) {
self.attributes = attributes
}
}

class ProfileViewModeFriendsItem: ProfileViewModelItem {
var type: ProfileViewModelItemType {
return .friend
}

var sectionTitle: String {
return "Friends"
}

var rowCount: Int {
return friends.count
}

var friends: [Friend]

init(friends: [Friend]) {
self.friends = friends
}
}
```

然后我们初始化`ViewModel`，我们需要在`ProfileViewModel`中为各种model赋值
```
class ProfileViewModel: NSObject {
var items = [ProfileViewModelItem]()

override init() {
super.init()
guard let data = dataFromFile("ServerData"), let profile = Profile(data: data) else {
return
}

if let name = profile.fullName, let pictureUrl = profile.pictureUrl {
let nameAndPictureItem = ProfileViewModelNamePictureItem(name: name, pictureUrl: pictureUrl)
items.append(nameAndPictureItem)
}

if let about = profile.about {
let aboutItem = ProfileViewModelAboutItem(about: about)
items.append(aboutItem)
}

if let email = profile.email {
let dobItem = ProfileViewModelEmailItem(email: email)
items.append(dobItem)
}

let attributes = profile.profileAttributes
// we only need attributes item if attributes not empty
if !attributes.isEmpty {
let attributesItem = ProfileViewModeAttributeItem(attributes: attributes)
items.append(attributesItem)
}

let friends = profile.friends
// we only need friends item if friends not empty
if !profile.friends.isEmpty {
let friendsItem = ProfileViewModeFriendsItem(friends: friends)
items.append(friendsItem)
}
}
}
```

接下来，我们将 UITableViewDataSource 添加到 `ModelView`：
```
extension ViewModel: UITableViewDataSource {
func numberOfSections(in tableView: UITableView) -> Int {
return items.count
}

func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
return items[section].rowCount
}

func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {

// we will configure the cells here

}
}
```

**View部分**
我们创建5中不同的cell，然后赋值即可


**UIViewController**
我们在`UIViewController`里面仅仅写这么多代码就可以了
```
var tableView:UITableView!
let viewModel = ProfileViewModel()
override func viewDidLoad() {
super.viewDidLoad()
tableView = UITableView(frame: self.view.bounds)
self.view.addSubview(tableView)

tableView?.dataSource = viewModel

tableView?.estimatedRowHeight = 100
tableView?.rowHeight = UITableView.automaticDimension

tableView?.register(AboutCell.nib, forCellReuseIdentifier: AboutCell.identifier)
tableView?.register(NamePictureCell.nib, forCellReuseIdentifier: NamePictureCell.identifier)
tableView?.register(FriendCell.nib, forCellReuseIdentifier: FriendCell.identifier)
tableView?.register(AttributeCell.nib, forCellReuseIdentifier: AttributeCell.identifier)
tableView?.register(EmailCell.nib, forCellReuseIdentifier: EmailCell.identifier)
}
```

这时就是数据在怎么变化，我们都不需要怎么修改逻辑了。

[文章转载自：[译] iOS：如何构建具有多种 Cell 类型的表视图](https://juejin.im/post/5c89a917e51d457efe07f4f9)

[参考：优雅的开发TableView](https://blog.csdn.net/Hello_Hwc/article/details/73460077)

 















 
**参考**

[iOS资讯详情页实现—WebView和TableView混合使用](https://www.jianshu.com/p/3721d736cf68)

[UIWebView与UITableView的嵌套方案](https://www.jianshu.com/p/42858f95ab43)

[iOS 实现简单的列表预加载](https://juejin.im/post/5c5c32bb51882562002aee18)

[【译】如何合理地处理复杂TableView页面](https://juejin.im/post/5c4139a0f265da61120545a1)
  
[swift标配开源库：Reusable-让你放肆的dequeueReusableCell](https://www.jianshu.com/p/255e02337176)

[folding-cell](https://github.com/Ramotion/folding-cell)

[应付复杂的cell](https://github.com/Instagram/IGListKit)

 [如何在 iOS 中实现一个可展开的 Table View](https://swift.gg/2015/12/03/expandable-table-view/)

 [抛弃UITableView,让所有列表页不再难构建](https://juejin.im/post/5bfa5ad8e51d450cb4187ca0)


[iOS面向切面的TableView-AOPTableView](https://juejin.im/post/5cc183c7e51d456e3b7018c8)

















