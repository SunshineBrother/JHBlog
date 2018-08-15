## UILabel 
 
 RxSwift 是一个用于与 Swift 语言交互的框架，但它只是基础，并不能用来进行用户交互、网络请求等。
 
 而 RxCocoa 是让 Cocoa APIs 更容易使用响应式编程的一个框架。RxCocoa 能够让我们方便地进行响应式网络请求、响应式的用户交互、绑定数据模型到 UI 控件等等。而且大多数的 UIKit 控件都有响应式扩展，它们都是通过 rx 属性进行使用
 
 ```
 //创建一个计时器（每0.1秒发送一个索引数）
 let timer = Observable<Int>.interval(0.1, scheduler: MainScheduler.instance)
 
 timer.map{[weak self] _ in self?.transform()}
 .bind(to: label1.rx.text)
 .disposed(by: disposeBag)
 
 
 //将数据绑定到 attributedText 属性上（富文本）
 timer.map{[weak self] _ in self?.formatTimeInterval(text: (self?.transform())!)}
 .bind(to: label2.rx.attributedText)
 .disposed(by: disposeBag)
 
 
 
 
 
 func transform() -> String{
 let dateFormatter = DateFormatter()
 dateFormatter.dateFormat = "YYYY-MM-dd HH:mm:ss"
 return dateFormatter.string(from: Date())
 
 }
 
 //将数字转成对应的富文本
 func formatTimeInterval(text: String) -> NSMutableAttributedString {
 //富文本设置
 let attributeString = NSMutableAttributedString(string: text)
 //从文本0开始6个字符字体HelveticaNeue-Bold,16号
 attributeString.addAttribute(NSAttributedStringKey.font,
 value: UIFont(name: "HelveticaNeue-Bold", size: 16)!,
 range: NSMakeRange(0, 10))
 //设置字体颜色
 attributeString.addAttribute(NSAttributedStringKey.foregroundColor,
 value: UIColor.white, range: NSMakeRange(0, 10))
 //设置文字背景颜色
 attributeString.addAttribute(NSAttributedStringKey.backgroundColor,
 value: UIColor.orange, range: NSMakeRange(0, 10))
 return attributeString
 }
 ```
 

   ![label](https://github.com/SunshineBrother/JHBlog/blob/master/RxSwift学习/rxswift图片/label.png)



















