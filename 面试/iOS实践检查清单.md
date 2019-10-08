# iOS实践检查清单

**[原文地址：iOS-Practice-Checklist](https://github.com/Binlogo/iOS-Practice-Checklist#开始项目)**

> 回顾即开始

## 目录

1. [开始项目](#开始项目)
2. [实用公共库](#实用公共库)
3. [架构](#架构)
4. [数据储存](#数据储存)
5. [资源](#资源)
6. [编码规范](#编码规范)
7. [安全性](#安全性)
8. [诊断](#诊断)

## 开始项目

### Xcode

- [ ] [Apple 帮助 - Xcode](https://help.apple.com/xcode/mac)

### .gitignore

- [ ] Git 添加 `.gitignore`: [Swift](https://github.com/github/gitignore/blob/master/Swift.gitignore) or [Objective-C](https://github.com/github/gitignore/blob/master/Objective-C.gitignore)

### 依赖管理

- [ ] CocoaPods [文档](https://guides.cocoapods.org/syntax/podfile.html)

```shell
sudo gem install cocoapods # 安装
pod init # 初始化创建 Podfile
pod install/update # 安装/更新依赖
```

- [ ] Carthage (Swift) [文档](https://github.com/Carthage/Carthage#quick-start)

```shell
brew install carthage # 安装
carthage bootstrap/update # 安装或更新依赖
```

### 工程目录结构

- [ ] 熟悉并保持合理的目录结构

```
AwesomeProject
├─ Assets
│	├─ Info.Plist
│	├─ Localizable.strings
│	├─ R.generated.swift # 可选，R.swift 生成
│	├─ LaunchScreen.storyboard
│	├─ Assets.xcassets
│	├─ ProjectName.entitlements
│	├─ BuildConfigs
│	└─ ···
├─Sources
│	├─ Modules
│   ├─ MyModule
│   │   │   ├─ Models
│   │   │   ├─ Views
│   │   │   └─ Controllers (or ViewModels)
│   │	└─ ···
│   ├─ Stores
│   ├─ Helpers
│   ├─ Utilities
│   ├─ Extentsions
│   ├─ Mediator
│   ├─ Ventors
│   └─ ···
├─Tests
└─ ···
```

- [ ] 字符串本地化（Localization）
  - [ ] [WWDC 404 - New Localization Workflows in Xcode 10](https://developer.apple.com/videos/play/wwdc2018/404/)
  - [ ] [WWDC 401 - Localizing with Xcode 9](https://developer.apple.com/videos/play/wwdc2017/401)
  - [ ] [WWDC 201 - Internationalization Best Practices](https://developer.apple.com/videos/play/wwdc2016/201)
- [ ] 最小化常量作用域（Constants）

```swift
// 全局常量建议采用 Enum 定义
enum Constants {
    static let myConstant = "Just a constant"
}
enum Apprearance {
    enum Sizes {
        static let gutter: CGFloat = 15
        static let cardGutter: CGFloat = 8
        ···
    }
    enum Color {
        static let primaryColor = UIColor(red: 0.22, green: 0.58, blue: 0.29, alpha: 1.0)
    	static let secondaryColor = UIColor.lightGray
        static let background = UIColor.white

        enum Red {
           	// 可视化颜色
            static let medium = #colorLiteral(red: 0.22, green: 0.58, blue: 0.29, alpha: 1.0)
            static let light = #colorLiteral(red: 0.22, green: 0.58, blue: 0.29, alpha: 1.0)
        }
    }
}
```

- [ ] Git 分支模型 
  - [ ] [git-flow 的工作流 - Tower](https://www.git-tower.com/learn/git/ebook/cn/command-line/advanced-topics/git-flow)
  - [ ] [gitflow-avh 拓展](https://github.com/petervanderdoes/gitflow-avh)

## 实用公共库

- [ ] [Alamofire](https://github.com/Alamofire/Alamofire) 网络库
- [ ] [Moya](https://github.com/Moya/Moya) 基于Alamofire 封装的网络抽象层
- [ ] [Reachability.swift](https://github.com/ashleymills/Reachability.swift) 用于网络状况检查

- [ ] [R.swift](https://github.com/mac-cain13/R.swift) 自动将各种资源强类型化
- [ ] [SwiftDate](https://github.com/malcommac/SwiftDate)/[DateTool](https://github.com/MatthewYork/DateTools) 时间日期处理库
- [ ] [RxSwift](https://github.com/ReactiveX/RxSwift) 响应式编程框架 by [ReactiveX.io](http://reactivex.io/)
- [ ] [LayoutKit](https://github.com/linkedin/LayoutKit) 高性能视图布局库
- [ ] [Kingfisher](https://github.com/onevcat/Kingfisher) 轻量级图片下载缓存库
- [ ] [NSLogger](https://github.com/fpillet/NSLogger) 便捷日志工具
- [ ] [Willow](https://github.com/Nike-Inc/Willow) 轻量级日志工具 [教程](https://medium.com/joshtastic-blog/convenient-logging-in-swift-75e1adf6ba7c)
- [ ] [FLEX](https://github.com/Flipboard/FLEX)/[DoraemonKit](https://github.com/didi/DoraemonKit) 应用内 Debug 工具库

## 架构

- [ ] [Model-View-Controller (MVC) in iOS: A Modern Approach](https://www.raywenderlich.com/1073-model-view-controller-mvc-in-ios-a-modern-approach)
- [ ] [Introduction to MVVM](https://www.objc.io/issues/13-architecture/mvvm/)
- [ ] [MVVM with Coordinators and RxSwift](https://academy.realm.io/posts/mobilization-lukasz-mroz-mvvm-coordinators-rxswift/)
- [ ] [ReactiveCocoa and MVVM, an Introduction](http://www.sprynthesis.com/2014/12/06/reactivecocoa-mvvm-introduction/)

### Model

- [ ] 保持 Model 不可变性, `struct` + `Codable` [Apple 文档](https://developer.apple.com/documentation/foundation/archives_and_serialization/encoding_and_decoding_custom_types)
- [ ] [SwiftyJSON](https://github.com/SwiftyJSON/SwiftyJSON) / [Argo](https://github.com/thoughtbot/Argo)  [可选]

### Views

- [ ] 采用 AutoLayout 布局
  - [ ] [Apple 文档 - NSLayoutAnchor](https://developer.apple.com/documentation/uikit/nslayoutanchor)
  - [ ] [WWDC 220 - High Performance Auto Layout](https://developer.apple.com/videos/play/wwdc2018/220)
  - [ ] [WWDC 218 - Mysteries of Auto Layout, Part 1](https://developer.apple.com/videos/play/wwdc2015/218) 
  - [ ] [WWDC 219 - Mysteries of Auto Layout, Part 2](https://developer.apple.com/videos/play/wwdc2015/219)

### Controllers

- [ ] 避免控制器臃肿
  - [ ]  [8 Patterns to Help You Destroy Massive View Controller](http://khanlou.com/2014/09/8-patterns-to-help-you-destroy-massive-view-controller/)
- [ ] 尽量采用依赖注入而不是单例

```swift
let fooViewController = FooViewController(withViewModel: fooViewModel)
```

## 数据储存

- [ ] 避免“回调地狱”（callback hell）
- [ ] [RxSwift](https://github.com/ReactiveX/RxSwift) 异步响应式编程

```swift
func fetchGigs(for artist: Artist) -> Observable<[Gig]> {
    // ...
}
```

- [ ] CoreData 持久化
  - [ ] [Apple 文档 - Core Data](https://developer.apple.com/documentation/coredata)
  - [ ] [WWDC 224 - Core Data Best Practices](https://developer.apple.com/videos/play/wwdc2018/224/)

## 资源

- [ ] 采用 `.pdf` 矢量图
- [ ] [R.swift](https://github.com/mac-cain13/R.swift) 自动集中管理图片、xib、字符串等各项资源
- [ ] [ImageOptim](https://imageoptim.com/mac) 图片优化

## 编码规范

- [ ] [API Design Guidelines for Swift](https://swift.org/documentation/api-design-guidelines/)
- [ ] [LinkedIn's Official Swift Style Guide](https://github.com/linkedin/swift-style-guide)

- [ ] `//MARK:` + `Extension`分组结构化代码

```swift
import SomeExternalFramework

class FooViewController : UIViewController {

    let foo: Foo

    private let fooStringConstant = "FooConstant"
    private let floatConstant = 1234.5

    // MARK: Lifecycle

    // Custom initializers go here
	···
}

// MARK: View Lifecycle
extension FooViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // ...
    }
    
}

// MARK: Layout
extension FooViewController {
    
    private func makeViewConstraints() {
        // ...
    }
    
}

// MARK: User Interaction
extension FooViewController {
   	
    func foobarButtonTapped() {
        // ...
    }
    
}

// MARK: FoobarDelegate
extension FooViewController: FoobarDelegate {
    
    func foobar(foobar: Foobar, didSomethingWithFoo foo: Foo) {
        // ...
    }
    
}

// MARK: Helpers
extension FooViewController {
        
    private func displayNameForFoo(foo: Foo) {
        // ...
    }
    
}

```

## 安全性

- [ ] [Apple 文档 - iOS Security Guide](https://www.apple.com/business/site/docs/iOS_Security_Guide.pdf)

### 数据储存

- [ ] Token、用户名密码及部分隐私敏感数据避免采用 `UserDefault` 或 `CoreData` 等非加密持久化方式
- [ ] 采用 `KeyChain` 加密储存敏感数据
  - [ ] [Apple 文档 - Storing Keys in the Keychain](https://developer.apple.com/documentation/security/certificate_key_and_trust_services/keys/storing_keys_in_the_keychain)
  - [ ] [KeychainAccess](https://github.com/kishikawakatsumi/KeychainAccess)

### 网络

- [ ] 采用 `https` TLS 加密传输

### 日志采集

- [ ] 设置正确的日志输出等级
- [ ] 线上环境**一定**不要打印密码等敏感信息
- [ ] 记录基本代码控制流，以便调试

### 用户交互

- [ ] `UITextField` 用于密码等敏感信息输入时设置`secureTextEntry` 为 `true`
- [ ] 必要时清空剪贴板等可能存在的敏感数据
  - [ ] `applicationDidEnterBackground`

## 诊断

- [ ] 重视并尽量解决编译器警告
- [ ] 静态分析
  - [ ] *Product → Analyze*
- [ ] 调试
  - [ ] 开启 `Exception` 断点
  - [ ] [Reveal](http://revealapp.com/) 视图调试
- [ ] 性能剖析
  - [ ] [Apple 帮助 - Instruments](https://help.apple.com/instruments/mac)





