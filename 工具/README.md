 
 <div class="ui segment article-content">
 
 <div class="extra-padding" style="padding-bottom:4px">
 
 <h1 style="margin-bottom: 15px;">
 
 <div class="pull-left" style="width: 76%;">
 
 <span class="hide-on-mobile"><a href="https://ioscaff.com/c/translations" class="ui popover rm-link-color" data-content="分类：外文翻译">
 <i class="icon translate"></i>
 </a>
 </span>
 
 <span style="line-height: 34px;"> 官方 Swift 风格指南 </span>
 
 
 <div class="ui labeled button" tabindex="0">
 <div class="ui icon basic button  login_required" style="border-top-right-radius: 0.28571429rem;border-bottom-right-radius: 0.28571429rem;">
 <i class="heart icon"></i>
 </div>
 </div>
 </div>
 <div class="clearfix"></div>
 </h1>                    <p class="book-article-meta" style="margin-bottom: 10px;">
  
 
 <div class="ui divider"></div>
 
 <div class="ui readme markdown-body content-body">
 
 <p>一定要阅读 <a href="https://swift.org/documentation/api-design-guidelines/">Apple 的 API 设计规范</a>。</p>
 <p>具体的规范细节和附加说明如下。</p>
 <p>本指南已于 2018 年 2 月 14 日针对 Swift 4.0 进行了更新。</p>
 <div name="767fa4" data-unique="767fa4"></div><h2>目录</h2>
 <ul><li><a href="#swift-style-guide">Swift 风格指南</a>
 <ul><li><a href="#1-code-formatting">1. 代码格式</a></li>
 <li><a href="#2-naming">2. 命名</a></li>
 <li><a href="#3-coding-style">3. 编码风格</a>
 <ul><li><a href="#31-general">3.1 通用</a></li>
 <li><a href="#32-access-modifiers">3.2 访问修饰符</a></li>
 <li><a href="#33-custom-operators">3.3 自定义操作符</a></li>
 <li><a href="#34-switch-statements-and-enums">3.4 Switch 语句和枚举</a></li>
 <li><a href="#35-optionals">3.5 可选类型</a></li>
 <li><a href="#36-protocols">3.6 协议</a></li>
 <li><a href="#37-properties">3.7 属性</a></li>
 <li><a href="#38-closures">3.8 闭包</a></li>
 <li><a href="#39-arrays">3.9 数组</a></li>
 <li><a href="#310-error-handling">3.10 错误处理</a></li>
 <li><a href="#311-using-guard-statements">3.11 使用 guard 语句</a></li>
 </ul></li>
 <li><a href="#4-documentationcomments">4. 文档 / 注释</a>
 <ul><li><a href="#41-documentation">4.1 文档</a></li>
 <li><a href="#42-other-commenting-guidelines">4.2 其他注释规范</a></li>
 </ul></li>
 </ul></li>
 </ul>
 
 <p><a name="1-code-formatting"></a></p>
 <div name="025bc7" data-unique="025bc7"></div><h2>1. 代码格式</h2>
 <ul><li><strong>1.1</strong> 使用 4 个空格代替 1 个 <code>tabs</code> 。</li>
 <li><strong>1.2</strong> 单行过长会引起阅读不适，每行代码尽量限制在 160 字符内 （ Xcode -&gt; Preferences -&gt; Text Editing -&gt; Page guide at column 设置为160 将会很有帮助）</li>
 <li><strong>1.3</strong> 确保每个文件末尾都有一个新行。</li>
 <li><strong>1.4</strong> 确保任何地方都没有尾随的空格（ Xcode -&gt; Preferences -&gt; Text Editing -&gt; Automatically trim trailing whitespace 加上 Including whitespace-only lines ）。</li>
 <li><strong>1.5</strong> 不要把左大括号放在新行 — 我们使用 <a href="https://en.m.wikipedia.org/wiki/Indentation_style#1TBS">1TBS 风格</a>。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">class</span> <span class="token class-name">SomeClass</span> <span class="token punctuation">{</span>
 <span class="token keyword">func</span> <span class="token function">someMethod</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">if</span> x <span class="token operator">==</span> y <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span> <span class="token keyword">else</span> <span class="token keyword">if</span> x <span class="token operator">==</span> z <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span> <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>1.6</strong> 当为属性、常量、变量、字典的键、函数参数、协议实现或父类书写类型时，不要在冒号 <code>:</code> 前面加上空格。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 指明类型</span>
 <span class="token keyword">let</span> pirateViewController<span class="token punctuation">:</span> <span class="token builtin">PirateViewController</span>
 
 <span class="token comment" spellcheck="true">// 字典语法（注意我们左对齐而不是对齐冒号）</span>
 <span class="token keyword">let</span> ninjaDictionary<span class="token punctuation">:</span> <span class="token punctuation">[</span><span class="token builtin">String</span><span class="token punctuation">:</span> <span class="token builtin">AnyObject</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token punctuation">[</span>
 <span class="token string">"fightLikeDairyFarmer"</span><span class="token punctuation">:</span> <span class="token boolean">false</span><span class="token punctuation">,</span>
 <span class="token string">"disgusting"</span><span class="token punctuation">:</span> <span class="token boolean">true</span>
 <span class="token punctuation">]</span>
 
 <span class="token comment" spellcheck="true">// 声明函数</span>
 <span class="token keyword">func</span> myFunction<span class="token operator">&lt;</span>T<span class="token punctuation">,</span> U<span class="token punctuation">:</span> <span class="token builtin">SomeProtocol</span><span class="token operator">&gt;</span><span class="token punctuation">(</span>firstArgument<span class="token punctuation">:</span> U<span class="token punctuation">,</span> secondArgument<span class="token punctuation">:</span> T<span class="token punctuation">)</span> <span class="token keyword">where</span> T<span class="token punctuation">.</span><span class="token builtin">RelatedType</span> <span class="token operator">==</span> U <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 调用函数</span>
 <span class="token function">someFunction</span><span class="token punctuation">(</span>someArgument<span class="token punctuation">:</span> <span class="token string">"Kitten"</span><span class="token punctuation">)</span>
 
 <span class="token comment" spellcheck="true">// 父类</span>
 <span class="token keyword">class</span> <span class="token class-name">PirateViewController</span><span class="token punctuation">:</span> <span class="token builtin">UIViewController</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 协议</span>
 <span class="token keyword">extension</span> <span class="token builtin">PirateViewController</span><span class="token punctuation">:</span> <span class="token builtin">UITableViewDataSource</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>1.7</strong> 通常， <code>,</code> 逗号后面应该有一个空格。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">let</span> myArray <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">,</span> <span class="token number">4</span><span class="token punctuation">,</span> <span class="token number">5</span><span class="token punctuation">]</span></code></pre>
 <ul><li><strong>1.8</strong> 二元运算符前后都应该有一个空格，比如 <code>+</code> 、 <code>==</code> 或 <code>-&gt;</code>。当然， <code>(</code> 后面和 <code>)</code> 前面就不要有空格了。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">let</span> myValue <span class="token operator">=</span> <span class="token number">20</span> <span class="token operator">+</span> <span class="token punctuation">(</span><span class="token number">30</span> <span class="token operator">/</span> <span class="token number">2</span><span class="token punctuation">)</span> <span class="token operator">*</span> <span class="token number">3</span>
 <span class="token keyword">if</span> <span class="token number">1</span> <span class="token operator">+</span> <span class="token number">1</span> <span class="token operator">==</span> <span class="token number">3</span> <span class="token punctuation">{</span>
 <span class="token function">fatalError</span><span class="token punctuation">(</span><span class="token string">"The universe is broken."</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 <span class="token keyword">func</span> <span class="token function">pancake</span><span class="token punctuation">(</span>with syrup<span class="token punctuation">:</span> <span class="token builtin">Syrup</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">Pancake</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>1.9</strong> 我们遵循 Xcode 推荐的缩进风格（即按住 CTRL-I 时，代码不再发生变化）。当声明的函数跨越多行时，推荐使用 Xcode 7.3 默认的语法风格。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 针对跨行函数声明，Xcode 添加了缩进</span>
 <span class="token keyword">func</span> <span class="token function">myFunctionWithManyParameters</span><span class="token punctuation">(</span>parameterOne<span class="token punctuation">:</span> <span class="token builtin">String</span><span class="token punctuation">,</span>
 parameterTwo<span class="token punctuation">:</span> <span class="token builtin">String</span><span class="token punctuation">,</span>
 parameterThree<span class="token punctuation">:</span> <span class="token builtin">String</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 对于这种语句，Xcode 缩进到这</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"<span class="token interpolation"><span class="token delimiter variable">\(</span>parameterOne<span class="token delimiter variable">)</span></span> <span class="token interpolation"><span class="token delimiter variable">\(</span>parameterTwo<span class="token delimiter variable">)</span></span> <span class="token interpolation"><span class="token delimiter variable">\(</span>parameterThree<span class="token delimiter variable">)</span></span>"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 针对多行的 `if` 语句增加换行缩进</span>
 <span class="token keyword">if</span> myFirstValue <span class="token operator">&gt;</span> <span class="token punctuation">(</span>mySecondValue <span class="token operator">+</span> myThirdValue<span class="token punctuation">)</span>
 <span class="token operator">&amp;&amp;</span> myFourthValue <span class="token operator">==</span> <span class="token punctuation">.</span>someEnumValue <span class="token punctuation">{</span>
 
 <span class="token comment" spellcheck="true">// 这行语句缩进到这</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Hello, World!"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>1.10</strong> 当调用一个多参数函数时，将每个参数放置有额外缩进的单独行中。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token function">someFunctionWithManyArguments</span><span class="token punctuation">(</span>
 firstArgument<span class="token punctuation">:</span> <span class="token string">"Hello, I am a string"</span><span class="token punctuation">,</span>
 secondArgument<span class="token punctuation">:</span> <span class="token function">resultFromSomeFunction</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">,</span>
 thirdArgument<span class="token punctuation">:</span> someOtherLocalProperty<span class="token punctuation">)</span></code></pre>
 <ul><li><strong>1.11</strong> 处理大到足以分成多行的隐式数组或字典时，按照方法、<code>if</code> 语句等语法中大括号的风格使用 <code>[</code> 和 <code>]</code> 。方法中的闭包也应该用类似的风格处理。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token function">someFunctionWithABunchOfArguments</span><span class="token punctuation">(</span>
 someStringArgument<span class="token punctuation">:</span> <span class="token string">"hello I am a string"</span><span class="token punctuation">,</span>
 someArrayArgument<span class="token punctuation">:</span> <span class="token punctuation">[</span>
 <span class="token string">"dadada daaaa daaaa dadada daaaa daaaa dadada daaaa daaaa"</span><span class="token punctuation">,</span>
 <span class="token string">"string one is crazy - what is it thinking?"</span>
 <span class="token punctuation">]</span><span class="token punctuation">,</span>
 someDictionaryArgument<span class="token punctuation">:</span> <span class="token punctuation">[</span>
 <span class="token string">"dictionary key 1"</span><span class="token punctuation">:</span> <span class="token string">"some value 1, but also some more text here"</span><span class="token punctuation">,</span>
 <span class="token string">"dictionary key 2"</span><span class="token punctuation">:</span> <span class="token string">"some value 2"</span>
 <span class="token punctuation">]</span><span class="token punctuation">,</span>
 someClosure<span class="token punctuation">:</span> <span class="token punctuation">{</span> parameter1 <span class="token keyword">in</span>
 <span class="token function">print</span><span class="token punctuation">(</span>parameter1<span class="token punctuation">)</span>
 <span class="token punctuation">}</span><span class="token punctuation">)</span></code></pre>
 <ul><li><strong>1.12</strong> 尽可能避免多行语句，推荐使用局部常量或其他方法。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">let</span> firstCondition <span class="token operator">=</span> x <span class="token operator">==</span> <span class="token function">firstReallyReallyLongPredicateFunction</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token keyword">let</span> secondCondition <span class="token operator">=</span> y <span class="token operator">==</span> <span class="token function">secondReallyReallyLongPredicateFunction</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token keyword">let</span> thirdCondition <span class="token operator">=</span> z <span class="token operator">==</span> <span class="token function">thirdReallyReallyLongPredicateFunction</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token keyword">if</span> firstCondition <span class="token operator">&amp;&amp;</span> secondCondition <span class="token operator">&amp;&amp;</span> thirdCondition <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 做某事</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">if</span> x <span class="token operator">==</span> <span class="token function">firstReallyReallyLongPredicateFunction</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token operator">&amp;&amp;</span> y <span class="token operator">==</span> <span class="token function">secondReallyReallyLongPredicateFunction</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token operator">&amp;&amp;</span> z <span class="token operator">==</span> <span class="token function">thirdReallyReallyLongPredicateFunction</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 做某事</span>
 <span class="token punctuation">}</span></code></pre>
 <p><a name="2-naming"></a></p>
 <div name="96dc9f" data-unique="96dc9f"></div><h2>2. 命名</h2>
 <ul><li>
 <p><strong>2.1</strong> 在 Swift 中不需要 Objective-C 风格的前缀（比如用 <code>GuybrushThreepwood</code> 代替 <code>LIGuybrushThreepwood</code>）。</p>
 </li>
 <li>
 <p><strong>2.2</strong> 使用 <code>PascalCase</code> 为类型命名（比如 <code>struct</code> 、 <code>enum</code> 、 <code>class</code> 、 <code>typedef</code> 、 <code>associatedtype</code> 等等）。</p>
 </li>
 <li>
 <p><strong>2.3</strong> 对于函数、方法、属性、常量、变量、参数名称、枚举选项，使用 <code>camelCase</code> （首字母小写）。</p>
 </li>
 <li><strong>2.4</strong> 实际上，当处理通常全部大写的缩写或其他名称时，代码里用到的任何名称都使用大写。例外情况是，如果这个单词位于以需要用小写开头的名称的开头——在这种情况下，请使用全部小写字母作为首字母缩写词。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 「HTML」是常量名称的开头，所以我们使用小写「html」 </span>
 <span class="token keyword">let</span> htmlBodyContent<span class="token punctuation">:</span> <span class="token builtin">String</span> <span class="token operator">=</span> <span class="token string">"&lt;p&gt;Hello, World!&lt;/p&gt;"</span>
 <span class="token comment" spellcheck="true">// 推荐使用 ID 而不是 Id</span>
 <span class="token keyword">let</span> profileID<span class="token punctuation">:</span> <span class="token builtin">Int</span> <span class="token operator">=</span> <span class="token number">1</span>
 <span class="token comment" spellcheck="true">// 推荐 URLFinder 而不是 UrlFinder</span>
 <span class="token keyword">class</span> <span class="token class-name">URLFinder</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>2.5</strong> 所有与实例无关的常量都应该用 <code>static</code> 修饰。所有这些 <code>static</code> 常量都应该放置在他们的 <code>class</code> 、 <code>struct</code> 或 <code>enum</code> 标记过的部分中。 对于有很多常量的类，你应该将拥有类似或相同前缀、后缀 和 / 或者使用情况的常量进行分组。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐    </span>
 <span class="token keyword">class</span> <span class="token class-name">MyClassName</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// MARK: - 常量</span>
 <span class="token keyword">static</span> <span class="token keyword">let</span> buttonPadding<span class="token punctuation">:</span> <span class="token builtin">CGFloat</span> <span class="token operator">=</span> <span class="token number">20.0</span>
 <span class="token keyword">static</span> <span class="token keyword">let</span> indianaPi <span class="token operator">=</span> <span class="token number">3</span>
 <span class="token keyword">static</span> <span class="token keyword">let</span> shared <span class="token operator">=</span> <span class="token function">MyClassName</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">class</span> <span class="token class-name">MyClassName</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 不要使用 `k` 前缀</span>
 <span class="token keyword">static</span> <span class="token keyword">let</span> <span class="token constant">kButtonPadding</span><span class="token punctuation">:</span> <span class="token builtin">CGFloat</span> <span class="token operator">=</span> <span class="token number">20.0</span>
 
 <span class="token comment" spellcheck="true">// 不用为常量使用命名空间</span>
 <span class="token keyword">enum</span> <span class="token builtin">Constant</span> <span class="token punctuation">{</span>
 <span class="token keyword">static</span> <span class="token keyword">let</span> indianaPi <span class="token operator">=</span> <span class="token number">3</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>2.6</strong> 对于泛型和关联类型，使用 <code>PascalCase</code> 描述泛型。如果这个单词和它遵循的协议或者它继承的父类冲突，你可以在关联类型或泛型名称后面追加 <code>Type</code> 后缀。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">class</span> <span class="token class-name">SomeClass</span><span class="token operator">&lt;</span><span class="token builtin">Model</span><span class="token operator">&gt;</span> <span class="token punctuation">{</span> <span class="token comment" spellcheck="true">/* ... */</span> <span class="token punctuation">}</span>
 protocol <span class="token builtin">Modelable</span> <span class="token punctuation">{</span>
 associatedtype <span class="token builtin">Model</span>
 <span class="token punctuation">}</span>
 protocol <span class="token builtin">Sequence</span> <span class="token punctuation">{</span>
 associatedtype <span class="token builtin">IteratorType</span><span class="token punctuation">:</span> <span class="token builtin">Iterator</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>2.7</strong> 名称应具有描述性的和明确性。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">class</span> <span class="token class-name">RoundAnimatingButton</span><span class="token punctuation">:</span> <span class="token builtin">UIButton</span> <span class="token punctuation">{</span> <span class="token comment" spellcheck="true">/* ... */</span> <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">class</span> <span class="token class-name">CustomButton</span><span class="token punctuation">:</span> <span class="token builtin">UIButton</span> <span class="token punctuation">{</span> <span class="token comment" spellcheck="true">/* ... */</span> <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>2.8</strong> 不要缩写、使用缩写名称或单字母名称</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">class</span> <span class="token class-name">RoundAnimatingButton</span><span class="token punctuation">:</span> <span class="token builtin">UIButton</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> animationDuration<span class="token punctuation">:</span> <span class="token builtin">NSTimeInterval</span>
 
 <span class="token keyword">func</span> <span class="token function">startAnimating</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> firstSubview <span class="token operator">=</span> subviews<span class="token punctuation">.</span><span class="token builtin">first</span>
 <span class="token punctuation">}</span>
 
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">class</span> <span class="token class-name">RoundAnimating</span><span class="token punctuation">:</span> <span class="token builtin">UIButton</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> aniDur<span class="token punctuation">:</span> <span class="token builtin">NSTimeInterval</span>
 
 <span class="token keyword">func</span> <span class="token function">srtAnmating</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> v <span class="token operator">=</span> subviews<span class="token punctuation">.</span><span class="token builtin">first</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>2.9</strong> 如果不明显，请在常量或变量名称中包含类型信息。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">class</span> <span class="token class-name">ConnectionTableViewCell</span><span class="token punctuation">:</span> <span class="token builtin">UITableViewCell</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> personImageView<span class="token punctuation">:</span> <span class="token builtin">UIImageView</span>
 
 <span class="token keyword">let</span> animationDuration<span class="token punctuation">:</span> <span class="token builtin">TimeInterval</span>
 
 <span class="token comment" spellcheck="true">// 由于属性名称明显可以看出它是字符串，在实例变量名称中就可以不包含字符串了。</span>
 <span class="token keyword">let</span> firstName<span class="token punctuation">:</span> <span class="token builtin">String</span>
 
 <span class="token comment" spellcheck="true">// 虽然不推荐，但使用 `Controller` 代替 `ViewController` 也是可以的。</span>
 <span class="token keyword">let</span> popupController<span class="token punctuation">:</span> <span class="token builtin">UIViewController</span>
 <span class="token keyword">let</span> popupViewController<span class="token punctuation">:</span> <span class="token builtin">UIViewController</span>
 
 <span class="token comment" spellcheck="true">// 当使用 `UIViewController` 的子类时，例如 table view controller、    </span>
 <span class="token comment" spellcheck="true">// collection view controller 、 split view controller 等，</span>
 <span class="token comment" spellcheck="true">// 在名称中完整表明其类型</span>
 <span class="token keyword">let</span> popupTableViewController<span class="token punctuation">:</span> <span class="token builtin">UITableViewController</span>
 
 <span class="token comment" spellcheck="true">// 当使用 outlet 时，确保在属性名称中指明 outlet 的类型。</span>
 <span class="token atrule">@IBOutlet</span> <span class="token keyword">weak</span> <span class="token keyword">var</span> submitButton<span class="token punctuation">:</span> <span class="token builtin">UIButton</span><span class="token operator">!</span>
 <span class="token atrule">@IBOutlet</span> <span class="token keyword">weak</span> <span class="token keyword">var</span> emailTextField<span class="token punctuation">:</span> <span class="token builtin">UITextField</span><span class="token operator">!</span>
 <span class="token atrule">@IBOutlet</span> <span class="token keyword">weak</span> <span class="token keyword">var</span> nameLabel<span class="token punctuation">:</span> <span class="token builtin">UILabel</span><span class="token operator">!</span>
 
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">class</span> <span class="token class-name">ConnectionTableViewCell</span><span class="token punctuation">:</span> <span class="token builtin">UITableViewCell</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 这不是 `UIImage` 所以不应该被叫做 image 而应该使用 </span>
 <span class="token comment" spellcheck="true">// personImageView</span>
 <span class="token keyword">let</span> personImage<span class="token punctuation">:</span> <span class="token builtin">UIImageView</span>
 
 <span class="token comment" spellcheck="true">// 这不是 `String`，所以它应该叫做 `textLabel`</span>
 <span class="token keyword">let</span> text<span class="token punctuation">:</span> <span class="token builtin">UILabel</span>
 
 <span class="token comment" spellcheck="true">// `animation` 没有很清晰地表明是时间间隔</span>
 <span class="token comment" spellcheck="true">// 使用 `animationDuration` 或 `animationTimeInterval` 代替它</span>
 <span class="token keyword">let</span> animation<span class="token punctuation">:</span> <span class="token builtin">TimeInterval</span>
 
 <span class="token comment" spellcheck="true">// `transition` 没有很明显地表明是 `String`</span>
 <span class="token comment" spellcheck="true">// 使用 `transitionText` 或 `transitionString` 代替它</span>
 <span class="token keyword">let</span> transition<span class="token punctuation">:</span> <span class="token builtin">String</span>
 
 <span class="token comment" spellcheck="true">// 这是 view controller — 而不是 view</span>
 <span class="token keyword">let</span> popupView<span class="token punctuation">:</span> <span class="token builtin">UIViewController</span>
 
 <span class="token comment" spellcheck="true">// 如前所述，我们不想使用缩写，所以不要用 `VC` 代替 `ViewController`</span>
 <span class="token keyword">let</span> popupVC<span class="token punctuation">:</span> <span class="token builtin">UIViewController</span>
 
 <span class="token comment" spellcheck="true">// 虽然在技术上这仍然是 `UIViewController`，但这个属性应该表明我们正在使用 *Table* View Controller</span>
 <span class="token keyword">let</span> popupViewController<span class="token punctuation">:</span> <span class="token builtin">UITableViewController</span>
 
 <span class="token comment" spellcheck="true">// 为了一致性，你应该把类型名称放在属性名称的结尾而不是开头。</span>
 <span class="token atrule">@IBOutlet</span> <span class="token keyword">weak</span> <span class="token keyword">var</span> btnSubmit<span class="token punctuation">:</span> <span class="token builtin">UIButton</span><span class="token operator">!</span>
 <span class="token atrule">@IBOutlet</span> <span class="token keyword">weak</span> <span class="token keyword">var</span> buttonSubmit<span class="token punctuation">:</span> <span class="token builtin">UIButton</span><span class="token operator">!</span>
 
 <span class="token comment" spellcheck="true">// 当处理 outlet 时，我们应该总是在属性名称中含有类型。</span>
 <span class="token comment" spellcheck="true">// 例如，我们应该用 `firstNameLabel` 代替。</span>
 <span class="token atrule">@IBOutlet</span> <span class="token keyword">weak</span> <span class="token keyword">var</span> firstName<span class="token punctuation">:</span> <span class="token builtin">UILabel</span><span class="token operator">!</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li>
 <p><strong>2.10</strong> 命名函数参数时，请确保函数可以被轻易地阅读并理解每个参数的目的。</p>
 </li>
 <li><strong>2.11</strong> 按照 <a href="https://swift.org/documentation/api-design-guidelines/">Apple 的 API 设计规范</a>，如果<code>protocol</code> 描述「某事物在做什么」，那么应被命名为名词（比如 <code>Collection</code> ）。 如果 <code>protocol</code> 描述「一种能力」，使用后缀 <code>able</code> 、 <code>ible</code> 或 <code>ing</code>（比如 <code>Equatable</code> 、<code>ProgressReporting</code> ）。如果两种选项都不适用你的用例，你也可以在协议名称后加一个 <code>Protocol</code> 后缀。一些  <code>protocol</code> 的例子如下。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 这里的名称是描述「协议在做什么」的名词。</span>
 protocol <span class="token builtin">TableViewSectionProvider</span> <span class="token punctuation">{</span>
 <span class="token keyword">func</span> <span class="token function">rowHeight</span><span class="token punctuation">(</span>at row<span class="token punctuation">:</span> <span class="token builtin">Int</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">CGFloat</span>
 <span class="token keyword">var</span> numberOfRows<span class="token punctuation">:</span> <span class="token builtin">Int</span> <span class="token punctuation">{</span> <span class="token keyword">get</span> <span class="token punctuation">}</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 这里的协议是一种能力，我们恰当地命名它。</span>
 protocol <span class="token builtin">Loggable</span> <span class="token punctuation">{</span>
 <span class="token keyword">func</span> <span class="token function">logCurrentState</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 假设有个 `InputTextView` 类，但我们也想让协议概括一些能力—使用 `Protocol` 后缀非常恰当。</span>
 protocol <span class="token builtin">InputTextViewProtocol</span> <span class="token punctuation">{</span>
 <span class="token keyword">func</span> <span class="token function">sendTrackingEvent</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token keyword">func</span> <span class="token function">inputText</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">String</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <p><a name="3-coding-style"></a></p>
 <div name="cb697b" data-unique="cb697b"></div><h2>3. 编码风格</h2>
 <p><a name="31-general"></a></p>
 <div name="f84846" data-unique="f84846"></div><h3>3.1 通用</h3>
 <ul><li>
 <p><strong>3.1.1</strong> 尽可能选择 <code>let</code> 而非 <code>var</code> .</p>
 </li>
 <li><strong>3.1.2</strong> 当从一个集合转换到另一个集合时，建议首选 <code>map</code> ， <code>filter</code> ， <code>reduce</code> 等高阶函数。在使用这些方法时，请确保使用的闭包没有任何副作用。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">let</span> stringOfInts <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">]</span><span class="token punctuation">.</span>flatMap <span class="token punctuation">{</span> <span class="token function">String</span><span class="token punctuation">(</span>$<span class="token number">0</span><span class="token punctuation">)</span> <span class="token punctuation">}</span>
 <span class="token comment" spellcheck="true">// ["1", "2", "3"]</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">var</span> stringOfInts<span class="token punctuation">:</span> <span class="token punctuation">[</span><span class="token builtin">String</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token punctuation">]</span>
 <span class="token keyword">for</span> integer <span class="token keyword">in</span> <span class="token punctuation">[</span><span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">]</span> <span class="token punctuation">{</span>
 stringOfInts<span class="token punctuation">.</span><span class="token function">append</span><span class="token punctuation">(</span><span class="token function">String</span><span class="token punctuation">(</span>integer<span class="token punctuation">)</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">let</span> evenNumbers <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token number">4</span><span class="token punctuation">,</span> <span class="token number">8</span><span class="token punctuation">,</span> <span class="token number">15</span><span class="token punctuation">,</span> <span class="token number">16</span><span class="token punctuation">,</span> <span class="token number">23</span><span class="token punctuation">,</span> <span class="token number">42</span><span class="token punctuation">]</span><span class="token punctuation">.</span><span class="token builtin">filter</span> <span class="token punctuation">{</span> $<span class="token number">0</span> <span class="token operator">%</span> <span class="token number">2</span> <span class="token operator">==</span> <span class="token number">0</span> <span class="token punctuation">}</span>
 <span class="token comment" spellcheck="true">// [4, 8, 16, 42]</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">var</span> evenNumbers<span class="token punctuation">:</span> <span class="token punctuation">[</span><span class="token builtin">Int</span><span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token punctuation">[</span><span class="token punctuation">]</span>
 <span class="token keyword">for</span> integer <span class="token keyword">in</span> <span class="token punctuation">[</span><span class="token number">4</span><span class="token punctuation">,</span> <span class="token number">8</span><span class="token punctuation">,</span> <span class="token number">15</span><span class="token punctuation">,</span> <span class="token number">16</span><span class="token punctuation">,</span> <span class="token number">23</span><span class="token punctuation">,</span> <span class="token number">42</span><span class="token punctuation">]</span> <span class="token punctuation">{</span>
 <span class="token keyword">if</span> integer <span class="token operator">%</span> <span class="token number">2</span> <span class="token operator">==</span> <span class="token number">0</span> <span class="token punctuation">{</span>
 evenNumbers<span class="token punctuation">.</span><span class="token function">append</span><span class="token punctuation">(</span>integer<span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li>
 <p><strong>3.1.3</strong> 如果常量或变量的类型可以被推导，则不去主动声明它的类型。</p>
 </li>
 <li><strong>3.1.4</strong> 如果一个方法返回多个值，那么推荐使用 <code>inout</code> 修饰的元组类型作为返回值类型 （如果类型不够一目了然，最好使用命名元组来表明你要返回的内容） 。 如果你会多次使用到某个特定的元组，那么可以考虑使用 <code>typealias</code> 。 如果你的元组里返回了 3 个及以上的元素，那么使用 <code>struct</code> 或者 <code>class</code> 可能比元组更合适。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">func</span> <span class="token function">pirateName</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token punctuation">(</span>firstName<span class="token punctuation">:</span> <span class="token builtin">String</span><span class="token punctuation">,</span> lastName<span class="token punctuation">:</span> <span class="token builtin">String</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span> <span class="token punctuation">(</span><span class="token string">"Guybrush"</span><span class="token punctuation">,</span> <span class="token string">"Threepwood"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">let</span> name <span class="token operator">=</span> <span class="token function">pirateName</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token keyword">let</span> firstName <span class="token operator">=</span> name<span class="token punctuation">.</span>firstName
 <span class="token keyword">let</span> lastName <span class="token operator">=</span> name<span class="token punctuation">.</span>lastName</code></pre>
 <ul><li>
 <p><strong>3.1.5</strong> 在为类声明代理或者协议的时候，要注意循环引用，通常这些属性在声明时要用 <code>weak</code> 修饰。</p>
 </li>
 <li><strong>3.1.6</strong> 在逃逸闭包中直接调用 self 的时候，要注意是否会引起循环引用。  - 当可能发生循环引用时尝试使用 <a href="https://developer.apple.com/library/ios/documentation/swift/conceptual/Swift_Programming_Language/Closures.html#//apple_ref/doc/uid/TP40014097-CH11-XID_163">capture list</a> :</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token function">myFunctionWithEscapingClosure</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span> <span class="token punctuation">[</span><span class="token keyword">weak</span> <span class="token keyword">self</span><span class="token punctuation">]</span> <span class="token punctuation">(</span>error<span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">Void</span> <span class="token keyword">in</span>
 <span class="token comment" spellcheck="true">// 你可以这么做</span>
 
 <span class="token keyword">self</span><span class="token operator">?</span><span class="token punctuation">.</span><span class="token function">doSomething</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 
 <span class="token comment" spellcheck="true">// 你也可以这么做</span>
 
 <span class="token keyword">guard</span> <span class="token keyword">let</span> strongSelf <span class="token operator">=</span> <span class="token keyword">self</span> <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 
 strongSelf<span class="token punctuation">.</span><span class="token function">doSomething</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li>
 <p><strong>3.1.7</strong> 不要使用labeled breaks.</p>
 </li>
 <li><strong>3.1.8</strong> 流程控制语句的条件语句不需要加括弧。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">if</span> x <span class="token operator">==</span> y <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">if</span> <span class="token punctuation">(</span>x <span class="token operator">==</span> y<span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.1.9</strong> 可以使用点语法直接写出枚举值，前面不需要写出枚举类型</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 imageView<span class="token punctuation">.</span><span class="token function">setImageWithURL</span><span class="token punctuation">(</span>url<span class="token punctuation">,</span> type<span class="token punctuation">:</span> <span class="token punctuation">.</span>person<span class="token punctuation">)</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 imageView<span class="token punctuation">.</span><span class="token function">setImageWithURL</span><span class="token punctuation">(</span>url<span class="token punctuation">,</span> type<span class="token punctuation">:</span> <span class="token builtin">AsyncImageView</span><span class="token punctuation">.</span><span class="token keyword">Type</span><span class="token punctuation">.</span>person<span class="token punctuation">)</span></code></pre>
 <ul><li><strong>3.1.10</strong> 在声明类方法的时候不要使用缩写，因为和 <code>enum</code> 相比，推导类的上下文会更难。 </li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 imageView<span class="token punctuation">.</span>backgroundColor <span class="token operator">=</span> <span class="token builtin">UIColor</span><span class="token punctuation">.</span>white
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 imageView<span class="token punctuation">.</span>backgroundColor <span class="token operator">=</span> <span class="token punctuation">.</span>white</code></pre>
 <ul><li>
 <p><strong>3.1.11</strong> 除非必要，否则尽量不使用 <code>self.</code> 。</p>
 </li>
 <li>
 <p><strong>3.1.12</strong> 写方法时，要考虑这个方法是否会被重载。如果不会，标记为 <code>final</code>，但请记住，这是为了防止以测试为目的而重载方法。通常， <code>final</code> 方法会将编译时间缩短，所以适时使用它是非常棒的。 但是，在库中应用 <code>final</code> 关键词要非常小心。因为相对于在本地项目中将某些内容改为非 <code>final</code> ，在库中将某些内容改为非 <code>final</code> 可不是小事。</p>
 </li>
 <li><strong>3.1.13</strong> 使用诸如 <code>else</code> 、 <code>catch</code> 等后面跟随代码块的语句，将关键字 和代码块放在同一行。强调一下，我们遵循 <a href="https://en.m.wikipedia.org/wiki/Indentation_style#1TBS">1TBS 风格</a> 。<code>if</code> / <code>else</code> 和 <code>do</code> / <code>catch</code> 的示例如下。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">if</span> someBoolean <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 做某些事</span>
 <span class="token punctuation">}</span> <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 做另一些事</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">do</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> fileContents <span class="token operator">=</span> <span class="token keyword">try</span> <span class="token function">readFile</span><span class="token punctuation">(</span><span class="token string">"filename.txt"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span> <span class="token keyword">catch</span> <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span>error<span class="token punctuation">)</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li>
 <p><strong>3.1.14</strong> 在定义与类相关的函数或属性而不是定义类的实例变量时时，推荐 <code>static</code> ，而不是 <code>class</code>。如果你特别需要在子类中重载这个函数的功能时，请使用 <code>class</code> 。但是，你应该考虑使用 <code>protocol</code> 来达到这个目的。</p>
 </li>
 <li><strong>3.1.15</strong> 如果有一个函数是无参数的、无副作用的而且返回某个对象或值，更推荐使用计算属性来代替它。</li>
 </ul>
 
 <p><a name="32-access-modifiers"></a></p>
 <div name="0cb2f9" data-unique="0cb2f9"></div><h3>3.2 访问修饰符</h3>
 <ul><li><strong>3.2.1</strong> 如果需要写访问修饰符关键字的话，请将它写在开头。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">private</span> <span class="token keyword">static</span> <span class="token keyword">let</span> myPrivateNumber<span class="token punctuation">:</span> <span class="token builtin">Int</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">static</span> <span class="token keyword">private</span> <span class="token keyword">let</span> myPrivateNumber<span class="token punctuation">:</span> <span class="token builtin">Int</span></code></pre>
 <ul><li><strong>3.2.2</strong> 访问修饰符关键字不应该独占一行，而是将它和其描述的东西放在一行。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 open <span class="token keyword">class</span> <span class="token class-name">Pirate</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 open
 <span class="token keyword">class</span> <span class="token class-name">Pirate</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li>
 <p><strong>3.2.3</strong> 通常情况下，访问修饰符关键字默认是 <code>internal</code> ，所以不用写出来。</p>
 </li>
 <li><strong>3.2.4</strong> 如果属性需要被单元测试访问，则需要将它标记为 <code>internal</code> ，以便于使用 <code>@testable import ModuleName</code> 。如果属性 <em>应该</em> 是私有的，但是出于单元测试的目的将它声明为 <code>internal</code>，一定要添加适当的文档注释来解释这一点。 为了更加简明，你可以使用 <code>- warning:</code> 标记语法，如下所示。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">/**
 这个属性定义海盗的名字。
 - warning: 不要为 `@testable` 添加 `private` 访问修饰符 
 */</span>
 <span class="token keyword">let</span> pirateName <span class="token operator">=</span> <span class="token string">"LeChuck"</span></code></pre>
 <ul><li>
 <p><strong>3.2.5</strong> 尽可能使用 <code>private</code> 而不是 <code>fileprivate</code> 。</p>
 </li>
 <li><strong>3.2.6</strong> 当在 <code>public</code> 和 <code>open</code> 两者之间选择一个时，如果你打算让某些内容在模块外也可以被继承，推荐使用 <code>open</code> ，否则请使用 <code>public</code>。注意，任何 <code>internal</code> 或更高访问权限的内容，都可以通过使用 <code>@testable import</code> 在测试中被继承。所以这不应该成为使用 <code>open</code> 的理由。通常，在涉及到库的时候，更倾向于自由地使用 <code>open</code> 。但是， <code>open</code> 可以轻易地同时改变应用程序中多个模块的内容。当涉及到这类代码库中的模块时，更倾向于保守地使用 <code>open</code> 。</li>
 </ul>
 
 <p><a name="33-custom-operators"></a></p>
 <div name="6a8c09" data-unique="6a8c09"></div><h3>3.3 自定义运算符</h3>
 <p>推荐创建自定义运算符。</p>
 <p>如果要引入自定义运算符，确保你有一个很好的理由，为什么你想把一个新的运算符引入全局范围，而不是使用其他现有的运算符。</p>
 <p>可以重写现有的运算符以支持新类型(特别是 <code>==</code> )。然而，你新定义的必须保存运算符的语义。例如， <code>==</code> 必须是检测是否相等并返回检测结果的布尔值。</p>
 <p><a name="34-switch-statements-and-enums"></a></p>
 <div name="0c699b" data-unique="0c699b"></div><h3>3.4 Switch 语句和枚举</h3>
 <ul><li>
 <p><strong>3.4.1</strong> 当使用具有有限可能性的 switch 语句( <code>enum</code> )，不包括 <code>default</code> 的其他情况。将未处理的情况放置在 <code>default</code> 里，并使用 <code>break</code> 来结束执行。</p>
 </li>
 <li>
 <p><strong>3.4.2</strong> 在 Swift 中由于 <code>switch</code> 的各种情况中默认有 <code>break</code> ，如果不需要，可以省略 <code>break</code> 关键字。 </p>
 </li>
 <li>
 <p><strong>3.4.3</strong> <code>case</code> 和 <code>switch</code> 的声明要按照 Swift 的规范独占一行。</p>
 </li>
 <li><strong>3.4.4</strong> 当定义具有关联值的情况时，确保这个值被适当的标记，例如：<code>case hunger(hungerLevel: Int)</code> 而不是 <code>case hunger(Int)</code> 。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">enum</span> <span class="token builtin">Problem</span> <span class="token punctuation">{</span>
 <span class="token keyword">case</span> attitude
 <span class="token keyword">case</span> hair
 <span class="token keyword">case</span> <span class="token function">hunger</span><span class="token punctuation">(</span>hungerLevel<span class="token punctuation">:</span> <span class="token builtin">Int</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">func</span> <span class="token function">handleProblem</span><span class="token punctuation">(</span>problem<span class="token punctuation">:</span> <span class="token builtin">Problem</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">switch</span> problem <span class="token punctuation">{</span>
 <span class="token keyword">case</span> <span class="token punctuation">.</span>attitude<span class="token punctuation">:</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"At least I don't have a hair problem."</span><span class="token punctuation">)</span>
 <span class="token keyword">case</span> <span class="token punctuation">.</span>hair<span class="token punctuation">:</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Your barber didn't know when to stop."</span><span class="token punctuation">)</span>
 <span class="token keyword">case</span> <span class="token punctuation">.</span><span class="token function">hunger</span><span class="token punctuation">(</span><span class="token keyword">let</span> hungerLevel<span class="token punctuation">)</span><span class="token punctuation">:</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"The hunger level is <span class="token interpolation"><span class="token delimiter variable">\(</span>hungerLevel<span class="token delimiter variable">)</span></span>."</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span>
 </code></pre>
 <ul><li>
 <p><strong>3.4.5</strong> 更推荐使用 <code>fallthrough</code> 关键字来处理一系列的 cases （例如:  <code>case 1, 2, 3:</code> ）。</p>
 </li>
 <li><strong>3.4.6</strong> 如果您有一个不应该达到的默认情况，最好抛出一个错误（或处理其他类似的方法，如断言）。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">func</span> <span class="token function">handleDigit</span><span class="token punctuation">(</span><span class="token number">_</span> digit<span class="token punctuation">:</span> <span class="token builtin">Int</span><span class="token punctuation">)</span> <span class="token keyword">throws</span> <span class="token punctuation">{</span>
 <span class="token keyword">switch</span> digit <span class="token punctuation">{</span>
 <span class="token keyword">case</span> <span class="token number">0</span><span class="token punctuation">,</span> <span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">,</span> <span class="token number">4</span><span class="token punctuation">,</span> <span class="token number">5</span><span class="token punctuation">,</span> <span class="token number">6</span><span class="token punctuation">,</span> <span class="token number">7</span><span class="token punctuation">,</span> <span class="token number">8</span><span class="token punctuation">,</span> <span class="token number">9</span><span class="token punctuation">:</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Yes, <span class="token interpolation"><span class="token delimiter variable">\(</span>digit<span class="token delimiter variable">)</span></span> is a digit!"</span><span class="token punctuation">)</span>
 <span class="token keyword">default</span><span class="token punctuation">:</span>
 <span class="token keyword">throw</span> <span class="token function">Error</span><span class="token punctuation">(</span>message<span class="token punctuation">:</span> <span class="token string">"The given number was not a digit."</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span>
 </code></pre>
 <p><a name="35-optionals"></a></p>
 <div name="48d3bc" data-unique="48d3bc"></div><h3>3.5 可选类型</h3>
 <ul><li>
 <p><strong>3.5.1</strong> 使用隐式解包可选类型的唯一机会是使用 <code>@IBOutlet</code> 的时候。在其他情况下，使用非可选或常规可选的属性会更好。是的，有某些情况下，你可以「保证」使用时属性不会为 <code>nil</code> ，但是安全和一致会更好。同样，不要使用强制解包。</p>
 </li>
 <li>
 <p><strong>3.5.2</strong> 不要使用 <code>as!</code> 或 <code>try!</code>.</p>
 </li>
 <li><strong>3.5.3</strong> 如果你不打算真正地使用存在可选类型中的值，但需要判断这个值是否为 <code>nil</code> ，显式地检查这个值是不是 <code>nil</code> ，而不是使用 <code>if let</code> 语法。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">if</span> someOptional <span class="token operator">!=</span> <span class="token constant">nil</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 做某件事</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">if</span> <span class="token keyword">let</span> <span class="token number">_</span> <span class="token operator">=</span> someOptional <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 做某件事</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.5.4</strong> 不要使用 <code>unowned</code> 。你可以将 <code>unowned</code> 视为被隐式解包的 <code>weak</code> 属性的等价物（虽然 <code>unowned</code> 因为完全忽略引用计数而略有性能上的提升）。因为我们不想有隐式解包，所以我们同样也不想要 <code>unowned</code> 属性。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">weak</span> <span class="token keyword">var</span> parentViewController<span class="token punctuation">:</span> <span class="token builtin">UIViewController</span><span class="token operator">?</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">weak</span> <span class="token keyword">var</span> parentViewController<span class="token punctuation">:</span> <span class="token builtin">UIViewController</span><span class="token operator">!</span>
 <span class="token keyword">unowned</span> <span class="token keyword">var</span> parentViewController<span class="token punctuation">:</span> <span class="token builtin">UIViewController</span></code></pre>
 <ul><li><strong>3.5.5</strong> 在解包可选类型时，在恰当的地方使用相同名称来命名解包的常量或变量。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">guard</span> <span class="token keyword">let</span> myValue <span class="token operator">=</span> myValue <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span></code></pre>
 <p><a name="36-protocols"></a></p>
 <div name="b4bcf8" data-unique="b4bcf8"></div><h3>3.6 协议</h3>
 <p>在实现协议时，有两种方式组织代码：</p>
 <ol><li>使用 <code>// MARK:</code> 注释将协议实现和其他部分的代码隔开。</li>
 <li>在同一资源文件中 <code>class</code>/<code>struct</code> 实现代码以外的地方，使用扩展。</li>
 </ol>
 
 <p>记住使用扩展时，无论怎样，扩展中的方法不要被子类重载，这会使测试变麻烦。如果这是一个通用的使用场景，为了一致性使用方法 #1 可能会更好。否则，#2 可以使关系的拆分更清楚。 </p>
 <p>即使使用方法 #2 ，也要添加 <code>// MARK:</code> 语句，以便在 Xcode 的方法 / 属性 / 类等的列表 UI 中更加易读。</p>
 <p><a name="37-properties"></a></p>
 <div name="8b7ac2" data-unique="8b7ac2"></div><h3>3.7 属性</h3>
 <ul><li><strong>3.7.1</strong> 如果创建只读的计算属性，提供不带  <code>get {}</code> 的获取方法。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">var</span> computedProperty<span class="token punctuation">:</span> <span class="token builtin">String</span> <span class="token punctuation">{</span>
 <span class="token keyword">if</span> someBool <span class="token punctuation">{</span>
 <span class="token keyword">return</span> <span class="token string">"I'm a mighty pirate!"</span>
 <span class="token punctuation">}</span>
 <span class="token keyword">return</span> <span class="token string">"I'm selling these fine leather jackets."</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.7.2</strong> 使用 <code>get {}</code> 、 <code>set {}</code> 、 <code>willSet</code> 和 <code>didSet</code> 时，缩进这些块。</li>
 <li><strong>3.7.3</strong> 虽然你可以为 <code>willSet</code>/<code>didSet</code> 和 <code>set</code> 自定义新值或旧值的名称，但请使用默认提供的标准标识符 <code>newValue</code> / <code>oldValue</code> 。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">var</span> storedProperty<span class="token punctuation">:</span> <span class="token builtin">String</span> <span class="token operator">=</span> <span class="token string">"I'm selling these fine leather jackets."</span> <span class="token punctuation">{</span>
 <span class="token keyword">willSet</span> <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"will set to <span class="token interpolation"><span class="token delimiter variable">\(</span>newValue<span class="token delimiter variable">)</span></span>"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 <span class="token keyword">didSet</span> <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"did set from <span class="token interpolation"><span class="token delimiter variable">\(</span>oldValue<span class="token delimiter variable">)</span></span> to <span class="token interpolation"><span class="token delimiter variable">\(</span>storedProperty<span class="token delimiter variable">)</span></span>"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">var</span> computedProperty<span class="token punctuation">:</span> <span class="token builtin">String</span>  <span class="token punctuation">{</span>
 <span class="token keyword">get</span> <span class="token punctuation">{</span>
 <span class="token keyword">if</span> someBool <span class="token punctuation">{</span>
 <span class="token keyword">return</span> <span class="token string">"I'm a mighty pirate!"</span>
 <span class="token punctuation">}</span>
 <span class="token keyword">return</span> storedProperty
 <span class="token punctuation">}</span>
 <span class="token keyword">set</span> <span class="token punctuation">{</span>
 storedProperty <span class="token operator">=</span> newValue
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.7.4</strong> 你可以按如下方式声明一个单例属性：</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">class</span> <span class="token class-name">PirateManager</span> <span class="token punctuation">{</span>
 <span class="token keyword">static</span> <span class="token keyword">let</span> shared <span class="token operator">=</span> <span class="token function">PirateManager</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <p><a name="38-closures"></a></p>
 <div name="34db41" data-unique="34db41"></div><h3>3.8 闭包</h3>
 <ul><li><strong>3.8.1</strong> 如果可以明确参数类型，即可以省略参数类型也可以显示参数类型。你可以根据场景决定是否添加一些说明来提高代码的可读性，或者是省略一些无关紧要的部分。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 省略参数类型</span>
 <span class="token function">doSomethingWithClosure</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span> response <span class="token keyword">in</span>
 <span class="token function">print</span><span class="token punctuation">(</span>response<span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 明确参数类型</span>
 <span class="token function">doSomethingWithClosure</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span> response<span class="token punctuation">:</span> <span class="token builtin">NSURLResponse</span> <span class="token keyword">in</span>
 <span class="token function">print</span><span class="token punctuation">(</span>response<span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 参数名缩写</span>
 <span class="token punctuation">[</span><span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">]</span><span class="token punctuation">.</span>flatMap <span class="token punctuation">{</span> <span class="token function">String</span><span class="token punctuation">(</span>$<span class="token number">0</span><span class="token punctuation">)</span> <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.8.2</strong> 声明了一个闭包，不需要用括号括起来，除非需要（例如，闭包类型是可选的，或者这个闭包在另一个闭包内）。闭包的参数都是是放在圆括号里，如果用 <code>()</code> 就表示没有参数，用 <code>Void</code> 表示无返回值。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">let</span> completionBlock<span class="token punctuation">:</span> <span class="token punctuation">(</span><span class="token builtin">Bool</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">Void</span> <span class="token operator">=</span> <span class="token punctuation">{</span> <span class="token punctuation">(</span>success<span class="token punctuation">)</span> <span class="token keyword">in</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Success? <span class="token interpolation"><span class="token delimiter variable">\(</span>success<span class="token delimiter variable">)</span></span>"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">let</span> completionBlock<span class="token punctuation">:</span> <span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">Void</span> <span class="token operator">=</span> <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Completed!"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">let</span> completionBlock<span class="token punctuation">:</span> <span class="token punctuation">(</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">Void</span><span class="token punctuation">)</span><span class="token operator">?</span> <span class="token operator">=</span> <span class="token constant">nil</span></code></pre>
 <ul><li>
 <p><strong>3.8.3</strong> 在闭包中尽可能的让参数保持在同一行，避免过多换行。（确保每行小于160个字符）。</p>
 </li>
 <li><strong>3.8.4</strong> 如果闭包的含义不太明确可以使用尾随闭包（如果一个方法同时含有成功和失败的两个闭包就不建议使用尾随闭包）。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 尾随闭包</span>
 <span class="token function">doSomething</span><span class="token punctuation">(</span><span class="token number">1.0</span><span class="token punctuation">)</span> <span class="token punctuation">{</span> <span class="token punctuation">(</span>parameter1<span class="token punctuation">)</span> <span class="token keyword">in</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Parameter 1 is <span class="token interpolation"><span class="token delimiter variable">\(</span>parameter1<span class="token delimiter variable">)</span></span>"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 无尾随闭包</span>
 <span class="token function">doSomething</span><span class="token punctuation">(</span><span class="token number">1.0</span><span class="token punctuation">,</span> success<span class="token punctuation">:</span> <span class="token punctuation">{</span> <span class="token punctuation">(</span>parameter1<span class="token punctuation">)</span> <span class="token keyword">in</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Success with <span class="token interpolation"><span class="token delimiter variable">\(</span>parameter1<span class="token delimiter variable">)</span></span>"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span><span class="token punctuation">,</span> failure<span class="token punctuation">:</span> <span class="token punctuation">{</span> <span class="token punctuation">(</span>parameter1<span class="token punctuation">)</span> <span class="token keyword">in</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Failure with <span class="token interpolation"><span class="token delimiter variable">\(</span>parameter1<span class="token delimiter variable">)</span></span>"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span><span class="token punctuation">)</span></code></pre>
 <p><a name="39-arrays"></a></p>
 <div name="3386ab" data-unique="3386ab"></div><h3>3.9 数组</h3>
 <ul><li>
 <p><strong>3.9.1</strong> 通常要避免直接用下标的方式访问数组。尽可能使用访问器，比如 <code>.first</code> 或 <code>.last</code>。它们是可选类型并且不会导致崩溃。推荐尽可能地使用 <code>for item in items</code> 语法而不是类似与 <code>for i in 0 ..&lt; items.count</code> 的语法。如果你需要直接用下标访问数组，一定要做适当的边界检查。你可以使用 <code>for (index, value) in items.enumerated()</code> 来一并得到索引和值。</p>
 </li>
 <li><strong>3.9.2</strong> 不要使用 <code>+=</code> 或 <code>+</code> 操作符来追加或串联到数组。而是使用 <code>.append()</code> 或 <code>.append(contentsOf:)</code>，因为在 Swift 当前的状况下它们（至少在编译方面）拥有更高的性能。如果基于其他数组声明数组而且想让它保持不变，使用 <code>let myNewArray = [arr1, arr2].joined()</code>，而不是 <code>let myNewArray = arr1 + arr2</code>。</li>
 </ul>
 
 <p><a name="310-error-handling"></a></p>
 <div name="9aa59c" data-unique="9aa59c"></div><h3>3.10 错误处理</h3>
 <p>假设函数 <code>myFunction</code> 应该返回 <code>String</code>，但是，某些时候它会运行错误。在出错时返回nil的情况下，通用的处理方式是让函数返回可选类型 <code>String?</code>。</p>
 <p>例如：</p>
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">func</span> <span class="token function">readFile</span><span class="token punctuation">(</span>named filename<span class="token punctuation">:</span> <span class="token builtin">String</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">String</span><span class="token operator">?</span> <span class="token punctuation">{</span>
 <span class="token keyword">guard</span> <span class="token keyword">let</span> file <span class="token operator">=</span> <span class="token function">openFile</span><span class="token punctuation">(</span>named<span class="token punctuation">:</span> filename<span class="token punctuation">)</span> <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span> <span class="token constant">nil</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">let</span> fileContents <span class="token operator">=</span> file<span class="token punctuation">.</span><span class="token function">read</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 file<span class="token punctuation">.</span><span class="token function">close</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token keyword">return</span> fileContents
 <span class="token punctuation">}</span>
 
 <span class="token keyword">func</span> <span class="token function">printSomeFile</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> filename <span class="token operator">=</span> <span class="token string">"somefile.txt"</span>
 <span class="token keyword">guard</span> <span class="token keyword">let</span> fileContents <span class="token operator">=</span> <span class="token function">readFile</span><span class="token punctuation">(</span>named<span class="token punctuation">:</span> filename<span class="token punctuation">)</span> <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Unable to open file <span class="token interpolation"><span class="token delimiter variable">\(</span>filename<span class="token delimiter variable">)</span></span>."</span><span class="token punctuation">)</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 <span class="token function">print</span><span class="token punctuation">(</span>fileContents<span class="token punctuation">)</span>
 <span class="token punctuation">}</span></code></pre>
 <p>相反，在适当的时候，我们应该使用 Swift 的 <code>try</code>/<code>catch</code> 操作来了解失败原因。</p>
 <p>你可以使用 <code>struct</code>，如下所示：</p>
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">struct</span> <span class="token builtin">Error</span><span class="token punctuation">:</span> <span class="token builtin">Swift</span><span class="token punctuation">.</span><span class="token builtin">Error</span> <span class="token punctuation">{</span>
 <span class="token keyword">public</span> <span class="token keyword">let</span> file<span class="token punctuation">:</span> <span class="token builtin">StaticString</span>
 <span class="token keyword">public</span> <span class="token keyword">let</span> function<span class="token punctuation">:</span> <span class="token builtin">StaticString</span>
 <span class="token keyword">public</span> <span class="token keyword">let</span> line<span class="token punctuation">:</span> <span class="token builtin">UInt</span>
 <span class="token keyword">public</span> <span class="token keyword">let</span> message<span class="token punctuation">:</span> <span class="token builtin">String</span>
 
 <span class="token keyword">public</span> <span class="token keyword">init</span><span class="token punctuation">(</span>message<span class="token punctuation">:</span> <span class="token builtin">String</span><span class="token punctuation">,</span> file<span class="token punctuation">:</span> <span class="token builtin">StaticString</span> <span class="token operator">=</span> #file<span class="token punctuation">,</span> function<span class="token punctuation">:</span> <span class="token builtin">StaticString</span> <span class="token operator">=</span> #function<span class="token punctuation">,</span> line<span class="token punctuation">:</span> <span class="token builtin">UInt</span> <span class="token operator">=</span> #line<span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">self</span><span class="token punctuation">.</span>file <span class="token operator">=</span> file
 <span class="token keyword">self</span><span class="token punctuation">.</span>function <span class="token operator">=</span> function
 <span class="token keyword">self</span><span class="token punctuation">.</span>line <span class="token operator">=</span> line
 <span class="token keyword">self</span><span class="token punctuation">.</span>message <span class="token operator">=</span> message
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span></code></pre>
 <p>用法示例：</p>
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">func</span> <span class="token function">readFile</span><span class="token punctuation">(</span>named filename<span class="token punctuation">:</span> <span class="token builtin">String</span><span class="token punctuation">)</span> <span class="token keyword">throws</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">String</span> <span class="token punctuation">{</span>
 <span class="token keyword">guard</span> <span class="token keyword">let</span> file <span class="token operator">=</span> <span class="token function">openFile</span><span class="token punctuation">(</span>named<span class="token punctuation">:</span> filename<span class="token punctuation">)</span> <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">throw</span> <span class="token function">Error</span><span class="token punctuation">(</span>message<span class="token punctuation">:</span> <span class="token string">"Unable to open file named <span class="token interpolation"><span class="token delimiter variable">\(</span>filename<span class="token delimiter variable">)</span></span>."</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">let</span> fileContents <span class="token operator">=</span> file<span class="token punctuation">.</span><span class="token function">read</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 file<span class="token punctuation">.</span><span class="token function">close</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token keyword">return</span> fileContents
 <span class="token punctuation">}</span>
 
 <span class="token keyword">func</span> <span class="token function">printSomeFile</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">do</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> fileContents <span class="token operator">=</span> <span class="token keyword">try</span> <span class="token function">readFile</span><span class="token punctuation">(</span>named<span class="token punctuation">:</span> filename<span class="token punctuation">)</span>
 <span class="token function">print</span><span class="token punctuation">(</span>fileContents<span class="token punctuation">)</span>
 <span class="token punctuation">}</span> <span class="token keyword">catch</span> <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span>error<span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span></code></pre>
 <p>有一些例外情况，使用可选类型比使用错误处理更有意义。当返回结果<em>语义</em>上可能是  <code>nil</code>，而不是取回结果时的错误值时，返回可选类型比使用错误处理更有意义。</p>
 <p>通常，如果方法可能「失败」，并且返回值为可选类型，失败的原因就不是很明显了，那么方法抛出错误可能会更有意义。</p>
 <p><a name="311-using-guard-statements"></a></p>
 <div name="e33812" data-unique="e33812"></div><h3>3.11 使用 <code>guard</code> 语句</h3>
 <ul><li><strong>3.11.1</strong> 一般情况下，我们推荐在适用的地方使用「尽早返回」的策略 而不是在 <code>if</code> 语句里嵌套代码。在这种使用场景下，使用 <code>guard</code> 语句通常很有用，而且可以提升代码的可读性。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">func</span> <span class="token function">eatDoughnut</span><span class="token punctuation">(</span>at index<span class="token punctuation">:</span> <span class="token builtin">Int</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">guard</span> index <span class="token operator">&gt;=</span> <span class="token number">0</span> <span class="token operator">&amp;&amp;</span> index <span class="token operator">&lt;</span> doughnuts<span class="token punctuation">.</span><span class="token builtin">count</span> <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// 尽早返回因为索引越界了</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">let</span> doughnut <span class="token operator">=</span> doughnuts<span class="token punctuation">[</span>index<span class="token punctuation">]</span>
 <span class="token function">eat</span><span class="token punctuation">(</span>doughnut<span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">func</span> <span class="token function">eatDoughnut</span><span class="token punctuation">(</span>at index<span class="token punctuation">:</span> <span class="token builtin">Int</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token keyword">if</span> index <span class="token operator">&gt;=</span> <span class="token number">0</span> <span class="token operator">&amp;&amp;</span> index <span class="token operator">&lt;</span> doughnuts<span class="token punctuation">.</span><span class="token builtin">count</span> <span class="token punctuation">{</span>
 <span class="token keyword">let</span> doughnut <span class="token operator">=</span> doughnuts<span class="token punctuation">[</span>index<span class="token punctuation">]</span>
 <span class="token function">eat</span><span class="token punctuation">(</span>doughnut<span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.11.2</strong> 当解包可选类型时，推荐 <code>guard</code> 语句而不是 <code>if</code> 语句来减少代码中嵌套缩进的数量。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">guard</span> <span class="token keyword">let</span> monkeyIsland <span class="token operator">=</span> monkeyIsland <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 <span class="token function">bookVacation</span><span class="token punctuation">(</span>on<span class="token punctuation">:</span> monkeyIsland<span class="token punctuation">)</span>
 <span class="token function">bragAboutVacation</span><span class="token punctuation">(</span>at<span class="token punctuation">:</span> monkeyIsland<span class="token punctuation">)</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">if</span> <span class="token keyword">let</span> monkeyIsland <span class="token operator">=</span> monkeyIsland <span class="token punctuation">{</span>
 <span class="token function">bookVacation</span><span class="token punctuation">(</span>on<span class="token punctuation">:</span> monkeyIsland<span class="token punctuation">)</span>
 <span class="token function">bragAboutVacation</span><span class="token punctuation">(</span>at<span class="token punctuation">:</span> monkeyIsland<span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 甚至更不推荐</span>
 <span class="token keyword">if</span> monkeyIsland <span class="token operator">==</span> <span class="token constant">nil</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 <span class="token function">bookVacation</span><span class="token punctuation">(</span>on<span class="token punctuation">:</span> monkeyIsland<span class="token operator">!</span><span class="token punctuation">)</span>
 <span class="token function">bragAboutVacation</span><span class="token punctuation">(</span>at<span class="token punctuation">:</span> monkeyIsland<span class="token operator">!</span><span class="token punctuation">)</span></code></pre>
 <ul><li><strong>3.11.3</strong> 在解包类型<em>不</em>复杂，需要在使用 <code>if</code> 还是 <code>guard</code> 之间做抉择时，要记住最重要的是代码的可读性。会有很多可能的情况，例如依赖于两个不同的布尔值、复杂逻辑语句涉及到多个判断等，所以通常使用您的最佳的判断来写出可读且一致的代码。如果你不确定 <code>guard</code> 或 <code>if</code> 哪个更具可读性或者它们看起来同样可读，推荐使用 <code>guard</code>。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 这里 `if` 语句的可读性很高</span>
 <span class="token keyword">if</span> operationFailed <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 这里 `guard` 语句的可读性很高</span>
 <span class="token keyword">guard</span> isSuccessful <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 像这种双重否定逻辑很难读懂—即不要这样做</span>
 <span class="token keyword">guard</span> <span class="token operator">!</span>operationFailed <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.11.4</strong> 如果在两种语句之间做选择，使用 <code>if</code> 语句比使用 <code>guard</code> 语句更有意义。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">if</span> isFriendly <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Hello, nice to meet you!"</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span> <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"You have the manners of a beggar."</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">guard</span> isFriendly <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"You have the manners of a beggar."</span><span class="token punctuation">)</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 
 <span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"Hello, nice to meet you!"</span><span class="token punctuation">)</span></code></pre>
 <ul><li><strong>3.11.5</strong> 只有在失败会导致退出当前上下文的情况下，才应该使用 <code>guard</code>。 下面是一个例子，在其中使用两个 <code>if</code> 语句而不是使用两个 <code>guard</code> 语句更有意义—有两个不相互阻塞的无关条件。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">if</span> <span class="token keyword">let</span> monkeyIsland <span class="token operator">=</span> monkeyIsland <span class="token punctuation">{</span>
 <span class="token function">bookVacation</span><span class="token punctuation">(</span>onIsland<span class="token punctuation">:</span> monkeyIsland<span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">if</span> <span class="token keyword">let</span> woodchuck <span class="token operator">=</span> woodchuck<span class="token punctuation">,</span> <span class="token function">canChuckWood</span><span class="token punctuation">(</span>woodchuck<span class="token punctuation">)</span> <span class="token punctuation">{</span>
 woodchuck<span class="token punctuation">.</span><span class="token function">chuckWood</span><span class="token punctuation">(</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.11.6</strong> 通常，我们可能遇到需要使用 <code>guard</code> 语句解包多个可选类型的情况。一般情况下，如果处理每个解包的失败是相同的（例如，<code>return</code>、<code>break</code>、<code>continue</code>、<code>throw</code> 或一些其他的 <code>@noescape</code>），将解包合入一个 <code>guard</code> 语句。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 因为只是返回，所以合并为一个。</span>
 <span class="token keyword">guard</span> <span class="token keyword">let</span> thingOne <span class="token operator">=</span> thingOne<span class="token punctuation">,</span>
 <span class="token keyword">let</span> thingTwo <span class="token operator">=</span> thingTwo<span class="token punctuation">,</span>
 <span class="token keyword">let</span> thingThree <span class="token operator">=</span> thingThree <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 因为在每种情况下处理特定的错误，所以拆分成单独的语句。</span>
 <span class="token keyword">guard</span> <span class="token keyword">let</span> thingOne <span class="token operator">=</span> thingOne <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">throw</span> <span class="token function">Error</span><span class="token punctuation">(</span>message<span class="token punctuation">:</span> <span class="token string">"Unwrapping thingOne failed."</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">guard</span> <span class="token keyword">let</span> thingTwo <span class="token operator">=</span> thingTwo <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">throw</span> <span class="token function">Error</span><span class="token punctuation">(</span>message<span class="token punctuation">:</span> <span class="token string">"Unwrapping thingTwo failed."</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span>
 
 <span class="token keyword">guard</span> <span class="token keyword">let</span> thingThree <span class="token operator">=</span> thingThree <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">throw</span> <span class="token function">Error</span><span class="token punctuation">(</span>message<span class="token punctuation">:</span> <span class="token string">"Unwrapping thingThree failed."</span><span class="token punctuation">)</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>3.11.7</strong> 不要将 <code>guard</code> 语句写成只有一行。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">// 推荐</span>
 <span class="token keyword">guard</span> <span class="token keyword">let</span> thingOne <span class="token operator">=</span> thingOne <span class="token keyword">else</span> <span class="token punctuation">{</span>
 <span class="token keyword">return</span>
 <span class="token punctuation">}</span>
 
 <span class="token comment" spellcheck="true">// 不推荐</span>
 <span class="token keyword">guard</span> <span class="token keyword">let</span> thingOne <span class="token operator">=</span> thingOne <span class="token keyword">else</span> <span class="token punctuation">{</span> <span class="token keyword">return</span> <span class="token punctuation">}</span></code></pre>
 <p><a name="4-documentationcomments"></a></p>
 <div name="b975fa" data-unique="b975fa"></div><h2>4. 文档 / 注释</h2>
 <p><a name="41-documentation"></a></p>
 <div name="965a15" data-unique="965a15"></div><h3>4.1 文档</h3>
 <p>如果函数比简单的 O(1) 操作负责，通常应该考虑为函数加个文档。因为方法签名的一些信息可能不是那么明显。如果实现方式有任何怪癖，无论在技术上有趣、棘手、不明显等等，都应该被文档化。应该为复杂的类 / 结构体 / 枚举 / 协议和属性添加文档。所有的 <code>public</code> 函数 / 类 / 属性 / 常量 / 结构体 / 枚举 / 协议等也应该被文档化。（如果，他们的签名 / 名称不能使他们含义 / 功能很明显）。</p>
 <p>写完文档注释之后，你应该按住 option 键并单击函数 / 属性 / 类等等来确认文档注释被正确地格式化了。</p>
 <p>务必查看 Swift 注释标记中提供的全套功能，详见 <a href="https://developer.apple.com/library/tvos/documentation/Xcode/Reference/xcode_markup_formatting_ref/Attention.html#//apple_ref/doc/uid/TP40016497-CH29-SW1">Apple 的文档</a>。</p>
 <p>原则:</p>
 <ul><li>
 <p><strong>4.1.1</strong> 160个字符列的限制（和代码的部分一样）。</p>
 </li>
 <li>
 <p><strong>4.1.2</strong> 如果文档注释在一行内，使用（ <code>/** */</code> ）。</p>
 </li>
 <li>
 <p><strong>4.1.3</strong> 不要在每一个附加行前面加 <code>*</code>。</p>
 </li>
 <li><strong>4.1.4</strong> 使用新的 <code>- parameter</code> 语法而不是旧的 <code>:param:</code> 语法（务必使用小写的 <code>parameter</code> 而并不是 <code>Parameter</code> ）。 按住 Option 键并单击你写的方法以确保快速帮助看起来是正确的。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">class</span> <span class="token class-name">Human</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/**
 这个方法向某人喂某种事物。
 
 - parameter food: 你想被他吃的食物
 - parameter person: 应该吃食物的人
 - returns: 如果食物被那个人吃了，为 True；否则为 false。 
 */</span>
 <span class="token keyword">func</span> <span class="token function">feed</span><span class="token punctuation">(</span><span class="token number">_</span> food<span class="token punctuation">:</span> <span class="token builtin">Food</span><span class="token punctuation">,</span> to person<span class="token punctuation">:</span> <span class="token builtin">Human</span><span class="token punctuation">)</span> <span class="token operator">-</span><span class="token operator">&gt;</span> <span class="token builtin">Bool</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">// ...</span>
 <span class="token punctuation">}</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li>
 <p><strong>4.1.5</strong> 如果你要给方法的参数 / 返回值 / 抛出的异常写文档，即使某些文档最终会有重复，也请将它们都写入文档（这比文档看起来不完整更可取）。有时，如果仅有一个参数需要写文档，在描述中提及它更好一些。</p>
 </li>
 <li><strong>4.1.6</strong> 对于复杂的类，请使用一些看起来合适的示例来描述类的用法。记住在 Swift 注释文档中可以使用 markdown 语法。因此，换行符、列表等等都是适用的。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">/**
 ## 功能支持
 
 这个类做了一些很棒的事情。它支持：
 
 - 功能 1
 - 功能 2
 - 功能 3
 
 ## 示例
 
 这有一个用例，由于它表示一个代码块，所以使用四个空格缩进：
 
 let myAwesomeThing = MyAwesomeClass()
 myAwesomeThing.makeMoney()
 
 ## 警告
 
 有一些你需要注意的事项：
 
 1. 事项一
 2. 事项二
 3. 事项三
 */</span>
 <span class="token keyword">class</span> <span class="token class-name">MyAwesomeClass</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>4.1.7</strong> 提及代码时，请使用代码提示 - `</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token comment" spellcheck="true">/**
 或许这里使用 `UIViewController` 做了某事
 - warning: 在运行这个函数之前，请确保 `someValue` 为 `true`。
 */</span>
 <span class="token keyword">func</span> <span class="token function">myFunction</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span></code></pre>
 <ul><li><strong>4.1.8</strong> 写文档注释时，尽可能保持简洁。</li>
 </ul>
 
 <p><a name="42-other-commenting-guidelines"></a></p>
 <div name="27880b" data-unique="27880b"></div><h3>4.2 其他注释原则</h3>
 <ul><li><strong>4.2.1</strong> 始终在 <code>//</code> 后面加个空格。</li>
 <li><strong>4.2.2</strong> 始终在自己的行中写注释。</li>
 <li><strong>4.2.3</strong> 使用 <code>// MARK: - 无论是什么</code> 时，在注释后加个空行。</li>
 </ul>
 
 <pre class=" language-swift"><code class=" language-swift"><span class="token keyword">class</span> <span class="token class-name">Pirate</span> <span class="token punctuation">{</span>
 
 <span class="token comment" spellcheck="true">// MARK: - 实例属性</span>
 
 <span class="token keyword">private</span> <span class="token keyword">let</span> pirateName<span class="token punctuation">:</span> <span class="token builtin">String</span>
 
 <span class="token comment" spellcheck="true">// MARK: - 构造函数</span>
 
 <span class="token keyword">init</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
 <span class="token comment" spellcheck="true">/* ... */</span>
 <span class="token punctuation">}</span>
 
 <span class="token punctuation">}</span></code></pre>
 
 
 <div>
 <a class="ui popover " data-content="作者署名，你可以在『个人资料』里设置" target="_blank" style="display: block;width: 30px;color: #ccc;margin: 22px 0 8px;"><i class="icon paw" aria-hidden="true"></i></a>
 <span class="rm-link-color">
 <p><a href="https://github.com/aufree">Aufree</a></p>
 </span>
 </div>
 
 
 <blockquote style="font-size: 0.9em;background: #ebf0f7;border: 1px dashed #dce0e4;border-radius: 5px;padding: 13px 25px;">
 <p style="margin-bottom: 0px;">原文地址：<a href="https://github.com/linkedin/swift-style-guide/">https://github.com/linkedin/swift-style-...</a></p>
 <p>译文地址：<a href="https://ioscaff.com/topics/91/linkedin-official-swift-style-guide">https://ioscaff.com/topics/91/linkedin-o...</a></p>
 </blockquote>
 
 
 <div class="ribbon-container" style="mgangargin-bottom: 20px;">
 </div>
 </div>
 
 
 <div class="admin-operation" style="line-height: 32px;">
 </div>
 
 <div class="ui horizontal list topic-operations" style="margin-bottom: 0px;margin-top:10px">
 
 
 
 
 
 
 </div>
 </div>
 </div>
