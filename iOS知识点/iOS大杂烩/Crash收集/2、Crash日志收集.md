## Crash日志收集

[文章转载自：iOS crash官方文档](https://developer.apple.com/library/archive/technotes/tn2151/_index.html)

当应用程序崩溃时，会创建一个崩溃报告，这对于了解导致崩溃的原因非常有用。本文档包含有关如何表示，理解和解释崩溃报告的基本信息。

-1、介绍
- 2、获取崩溃和低内存报告
- 3、象征性的奔溃报告    
    - 1、位码（bitCode）
    - 2、确定奔溃报告是否符号化
    - 3、用Xcode标记iOS奔溃报告
    - 4、用atos表示崩溃报告
    - 5、符号故障排除
- 4、崩溃报告分析  
    - 1、头
    - 2、例外信息
    - 3、其他诊断信息
    - 4、回溯
    - 5、线程状态
    - 6、二进制图像
- 5、了解低内存报告


### 介绍
当应用程序崩溃时，会创建崩溃报告并将其存储在设备上。崩溃报告描述了应用程序终止的条件，在大多数情况下包括每个执行线程的完整回溯，并且通常对于调试应用程序中的问题非常有用。您应该查看这些崩溃报告，以了解您的应用程序崩溃了什么，然后尝试修复它们。

带有回溯的崩溃报告需要在进行分析之前进行符号化。符号化用人类可读的函数名称和行号替换内存地址。如果您通过Xcode的设备窗口从设备上获取崩溃日志，那么几秒钟后它们将自动被符号化。否则，您需要通过将.crash文件导入Xcode Devices窗口来自行符号化。有关详细信息，请参阅符号崩溃报告。

一个低内存报告不同之处在于有这类型的报告没有回溯其他的崩溃报告。当发生低内存崩溃时，您必须调查内存使用模式以及对低内存警告的响应。 

 
 #### 获取崩溃和低内存报告

调试已部署的iOS应用程序讨论了如何直接从iOS设备检索崩溃和低内存报告。

分析“ 应用程序分发指南”中的崩溃报告讨论了如何查看从TestFlight beta测试人员和从App Store下载应用程序的用户收集的聚合崩溃报告。


### 象征性的崩溃报告
符号化是将回溯地址解析为源代码方法或函数名称（称为符号）的过程。如果没有首先表示崩溃报告，则很难确定崩溃发生的位置。

```
注意：  低内存报告不需要进行符号化。
注意：  macOS的崩溃报告通常在生成时被符号化或部分符号化。本节重点介绍iOS，watchOS和tvOS的崩溃报告，但整个过程与macOS类似。
```


![Crash日志](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/Crash日志.png)


1、当编译器将源代码转换为机器代码时，它还会生成调试符号，这些符号将编译后的二进制文件中的每个机器指令映射回源自它的源代码行。根据Debug Information Format（DEBUG_INFORMATION_FORMAT）构建设置，这些调试符号存储在二进制文件或伴随的Debug Symbol（dSYM）文件中。默认情况下，应用程序的调试版本将调试符号存储在已编译的二进制文件中，而应用程序的发布版本将调试符号存储在配套dSYM文件中以减小二进制文件大小。
调试符号文件和应用程序二进制文件通过构建UUID在每个构建的基础上绑定在一起。为应用程序的每个构建生成一个新的UUID，并唯一标识该构建。即使从相同的源代码重建功能相同的可执行文件，使用相同的编译器设置，它也将具有不同的构建UUID。调试来自后续版本的符号文件，即使是来自相同的源文件，也不会与来自其他版本的二进制文件互操作。

- 2、归档应用程序以进行分发时，Xcode将收集应用程序二进制文件以及。dSYM将文件存储并保存在主文件夹内的某个位置

- 3、如果您通过App Store分发应用程序，或使用Test Flight进行beta测试，您可以选择dSYM在将存档上传到iTunes Connect时包含该文件。在提交对话框中，选中“为您的应用程序包含应用程序符号...”。上传dSYM文件对于接收从TestFlight用户和选择共享诊断数据的客户收集的崩溃报告是必要的

- 4、当您的应用程序崩溃时，会创建一个非符号化的崩溃报告并将其存储在设备上。

- 5、用户可以按照调试已部署的iOS应用程序中的步骤直接从其设备检索崩溃报告。如果您通过AdHoc或Enterprise分发分发了应用程序，则这是从用户获取崩溃报告的唯一方法。

- 6、从设备检索到的崩溃报告是非符号化的，需要使用Xcode进行符号化。Xcode使用dSYM与应用程序二进制文件关联的文件将回溯中的每个地址替换为源代码中的原始位置。结果是一个符号化的崩溃报告。

- 7、如果用户选择与Apple共享诊断数据，或者用户已通过TestFlight安装了应用程序的测试版，则崩溃报告将上载到App Store

- 8、App Store表示崩溃报告，并将其与类似的崩溃报告分组。这种类似崩溃报告的汇总称为崩溃点。

- 9、Xcode的Crashes组织者可以使用符号化的崩溃报告。



#### 位码

Bitcode是编译程序的中间表示。当您使用bitcode存档应用程序时，编译器会生成包含bitcode而不是机器代码的二进制文件。将二进制文件上传到App Store后，bitcode将编译为机器代码。App Store可能会在将来再次编译bitcode，以利用未来的编译器改进，而无需您采取任何操作



![Crash日志1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/Crash日志1.png)


由于二进制文件的最终编译发生在App Store上，因此Mac不会包含用于表示dSYM从App Review收到的崩溃报告或从其设备向您发送崩溃报告的用户所需的调试符号（）文件。虽然dSYM归档应用程序时会生成一个文件，但它是用于bitcode二进制文件，不能用于表示崩溃报告。App Store使dSYM您可以从Xcode或iTunes Connect网站下载bitcode编译期间生成的文件。您必须下载这些dSYM文件，以便表示从App Review或从其设备向您发送崩溃报告的用户收到的崩溃报告。通过崩溃报告服务收到的崩溃报告将自动进行符号化。

```
App Store编译的二进制文件将具有与最初提交的二进制文件不同的UUID。

```

**从Xcode下载dSYM文件**

- 1、在Archives管理器中，选择最初提交到App Store的存档
- 2、单击“下载dSYMs”按钮。
Xcode下载dSYM文件并将其插入选定的存档。

**从iTunes Connect网站下载dSYM文件**

- 1、打开“应用详情”页面。
- 2、单击活动。
- 3、从“所有构建”列表中，选择一个版本。
- 4、单击“ 下载dSYM”链接


#### 将“隐藏”符号名称翻译回原始名称

当您将带有bitcode的应用程序上传到App Store时，您可以选择不通过取消选中“上传您的应用程序的符号以从Apple接收符号化报告”框来发送应用程序的符号。如果您选择不将应用程序的符号信息发送给Apple，Xcode将替换您应用程序中的符号。dSYM在将应用程序发送到iTunes Connect之前，带有模糊符号的文件，例如“__hidden＃109_”。Xcode在原始符号和“隐藏”符号之间创建映射，并将此映射存储.bcsymbolmap在应用程序归档内的文件中。每个。dSYM文件将有一个相应的.bcsymbolmap文件。

在对崩溃报告进行符号化之前，您需要对符号中的符号进行去混淆。dSYM从iTunes Connect下载的文件。如果您使用Xcode中的下载dSYMs按钮，将自动执行此去混淆。但是，如果您使用iTunes Connect网站下载。dSYM文件，打开终端并使用以下命令对符号进行反模糊处理（用您自己的存档替换示例路径和从iTunes Connect下载的dSYMs文件夹）：

```
xcrun dsymutil -symbol-map~ / Library / Developer / Xcode / Archives / 2017-11-23 / MyGreatApp \ 11-23-17 \，\ 12.00 \ PM.xcarchive / BCSymbolMaps~ / Downloads / dSYMs / 3B15C133-88AA-35B0 -B8BA-84AF76826CE0.dSYM

```
为每个运行此命令。dSYM您下载的dSYMs文件夹中的文件。



#### 确定崩溃报告是否符号化

崩溃报告可以是非符号化的，完全符号化的或部分符号化的。非符号化的崩溃报告将不包含回溯中的方法或函数名称。相反，您在加载的二进制图像中具有可执行代码的十六进制地址。在完全符号化的崩溃报告中，回溯的每一行中的十六进制地址将替换为相应的符号。在部分符号化的崩溃报告中，只有回溯中的某些地址已替换为其相应的符号。

显然，您应该尝试完全符合您收到的任何崩溃报告，因为它将提供有关崩溃的最深入见解。部分符号化的崩溃报告可能包含足够的信息来了解崩溃，具体取决于崩溃的类型以及成功符号化的回溯的哪些部分。非符号化的崩溃报告很少有用


![Crash日志2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/Crash日志2.png)


#### 用Xcode标记iOS崩溃报告

Xcode将自动尝试表示它遇到的所有崩溃报告。您需要为符号化做的只是将崩溃报告添加到Xcode Organizer。


```
Xcode不接受没有.crash扩展名的崩溃报告。如果您收到没有扩展程序或扩展程序的崩溃报告，请在执行下面列出的步骤之前.txt将其重命名为.crash扩展程序。
```

- 1、将iOS设备连接到Mac
- 2、从“窗口”菜单中选择“设备”
- 3、 在左列的“设备”部分下，选择一个设备
- 4、单击右侧面板“设备信息”部分下的“查看设备日志”按钮
- 5、将崩溃报告拖到所显示面板的左列
- 6、Xcode将自动表示崩溃报告并显示结果


**为了表示崩溃报告，Xcode需要能够找到以下内容**

- 1、崩溃的应用程序的二进制dSYM文件和文件。
- 2、dSYM应用程序链接的所有自定义框架的二进制文件和文件。对于使用应用程序从源构建的框架，它们的dSYM文件将与应用程序的dSYM文件一起复制到存档中。对于由第三方构建的框架，您需要向作者询问该dSYM文件。
- 3、崩溃时该应用程序运行的操作系统的符号。这些符号包含特定操作系统版本（例如iOS 9.3.3）中包含的框架的调试信息。OS符号是特定于体系结构的 - 用于64位设备的iOS版本不包含armv7符号。Xcode将自动从连接到Mac的每个设备复制OS符号。

如果缺少任何这些，Xcode可能无法表示崩溃报告，或者可能只是部分地表示崩溃报告。


#### 用atos表示崩溃报告

该 ATOS命令将数字地址转换为其符号等效项。如果有完整的调试符号信息，则输出atos将包括文件名和源行号信息。该atos命令可用于在非符号化或部分符号化的崩溃报告的回溯中表示各个地址。使用atos以下命令表示崩溃报告的一部分：

- 1、在回溯中找到要符号化的行。请注意第二列中二进制图像的名称，以及第三列中的地址。
- 2、在崩溃报告底部的二进制图像列表中查找具有该名称的二进制图像。请注意二进制映像的体系结构和加载地址。


![Crash日志3](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/Crash日志3.png)



#### 符号故障排除
如果Xcode未能完全符合崩溃报告，可能是因为您的Mac缺少dSYM应用程序二进制dSYM文件的文件，应用程序链接的一个或多个框架的文件，或者应用程序运行的OS的设备符号它坠毁了。以下步骤显示如何使用Spotlight确定dSYM在Mac上是否存在表示二进制图像中的回溯地址所需的文件。


![Crash日志4](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/Crash收集/Crash日志4.png)

- 1、在回溯中找到Xcode无法符号化的行。请注意第二列中二进制图像的名称
- 2、在崩溃报告底部的二进制图像列表中查找具有该名称的二进制图像。此列表包含崩溃时加载到进程中的每个二进制映像的UUID。
```
您可以使用grep命令行工具快速查找二进制映像列表中的条目。
$ grep --after-context = 1000“二进制图像：”<崩溃报告的路径> | grep <二进制名称>
```
- 3、将二进制映像的UUID转换为以8-4-4-4-12（XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX）为一组分隔的32个字符串。请注意，所有字母必须是大写的。
- 4、使用mdfind命令行工具使用查询搜索UUID "com_apple_xcode_dsym_uuids == <UUID>"（包括引号）。
```
使用mdfind命令行工具搜索dSYM具有给定UUID的文件。
$ mdfind“com_apple_xcode_dsym_uuids == <UUID>”

```
- 5、如果Spotlight找到dSYMUUID 的文件，mdfind将打印该dSYM文件的路径，并可能打印其包含的存档。如果dSYM找不到UUID 的文件， mdfind将退出而不打印任何内容。



### 分析崩溃报告



#### 头

每个崩溃报告都以标题开头。

```
Incident Identifier(事件标识符): B6FD1E8E-B39F-430B-ADDE-FC3A45ED368C
CrashReporter Key(密钥): f04e68ec62d3c66057628c9ba9839e30d55937dc
Hardware Model(硬件型号): iPad6,8
Process(进程): TheElements [303]
Path(路径): /private/var/containers/Bundle/Application/888C1FA2-3666-4AE2-9E8E-62E2F787DEC1/TheElements.app/TheElements
Identifier(标识符): com.example.apple-samplecode.TheElements
Version(版本): 1.12
Code Type(代码类型): ARM-64 (Native)
Role: Foreground
Parent Process: launchd [1]
Coalition: com.example.apple-samplecode.TheElements [402]

Date/Time: 2016-08-22 10:43:07.5806 -0700
Launch Time: 2016-08-22 10:43:01.0293 -0700
OS Version: iPhone OS 10.0 (14A5345a)
Report Version: 104
```
- 1、`Incident Identifier`事件标识符：报告的唯一标识符。两个报告永远不会共享相同的事件标识符。
- 2、`CrashReporter Key`CrashReporter密钥：匿名的每设备标识符。来自同一设备的两个报告将包含相同的值。
- 3、`Beta Identifier`Beta标识符：崩溃应用程序的设备和供应商组合的唯一标识符。来自同一供应商和同一设备的两个应用程序报告将包含相同的值。此字段仅存在于为通过TestFlight分发的应用程序生成的崩溃报告中，并替换CrashReporter Key字段。
- 4、`Process`进程：崩溃进程的可执行文件名称。这与CFBundleExecutable应用程序的信息属性列表中的键值匹配。
- 5、`Version`版本：崩溃的进程版本。该字段的值是崩溃的应用程序CFBundleVersion和的串联CFBundleVersionString。
- 6、`Code Type`代码类型：崩溃的进程的目标体系结构。这将是一ARM-64，ARM，x86-64，或x86。
- 7、`Role`角色：终止时分配给进程的task_role。
- 8、`OS Version`操作系统版本：发生崩溃的操作系统版本，包括内部版本号。

**由于未捕获的Objective-C异常导致进程终止时生成的崩溃报告中的Exception Codes部分的摘录。**

```
Exception Type: EXC_CRASH (SIGABRT)
Exception Codes: 0x0000000000000000, 0x0000000000000000
Exception Note: EXC_CORPSE_NOTIFY
Triggered by Thread: 0

```

 **当进程因为取消引用NULL指针而终止时生成的崩溃报告中的Exception Codes部分的摘录。**

```
Exception Type: EXC_BAD_ACCESS (SIGSEGV)
Exception Subtype: KERN_INVALID_ADDRESS at 0x0000000000000000
Termination Signal: Segmentation fault: 11
Termination Reason: Namespace SIGNAL, Code 0xb
Terminating Process: exc handler [0]
Triggered by Thread: 0
```

- 1、`Exception Codes`异常代码：有关异常的处理器特定信息，编码为一个或多个64位十六进制数。通常，此字段将不存在，因为Crash Reporter会解析异常代码以将其作为人类可读的描述呈现在其他字段中。
- 2、`Exception Subtype`异常子类型：异常代码的人类可读名称。
- 3、`Exception Message`异常消息：从异常代码中提取的其他人类可读信息。
- 4、`Exception Note`异常注意：非特定于一种异常类型的附加信息。如果该字段包含，SIMULATED (this is NOT a crash)那么进程没有崩溃，但是在系统请求时被杀死，通常是看门狗
- 5、`Termination Reason`终止原因：终止进程时指定的退出原因信息。进程内部和外部的关键系统组件将在遇到致命错误时终止进程（例如，错误的代码签名，缺少的依赖库，或在没有适当权利的情况下访问隐私敏感信息）。macOS Sierra，iOS 10，watchOS 3和tvOS 10采用了新的基础设施来记录这些错误，这些操作系统生成的崩溃报告列出了终止原因字段中的错误消息
- 6、`Triggered by Thread`由线程触发：发生异常的线程。


**内存访问不良[EXC_BAD_ACCESS // SIGSEGV // SIGBUS]**


该进程尝试访问无效内存，或者尝试以内存保护级别不允许的方式访问内存（例如，写入只读内存）。该例外子类型字段包含一个kern_return_t描述错误，并且被错误地访问的存储器的地址。

以下是调试错误内存访问崩溃的一些提示：

- 1、如果崩溃线程的Backtraces顶部objc_msgSend或objc_release附近，则该进程可能已尝试向已释放的对象发送消息。您应该使用Zombies工具对应用程序进行概要分析，以便更好地了解此崩溃的情况。
- 2、如果在崩溃线程gpus_ReturnNotPermittedKillClient的Backtraces顶部附近，则该进程被终止，因为它在后台尝试使用OpenGL ES或Metal进行渲染。请参阅QA1766：如何在移动到后台时修复OpenGL ES应用程序崩溃。
- 3、启用Address Sanitizer运行您的应用程序。地址清理程序在已编译的代码中添加了有关内存访问的附加检测。当您的应用程序运行时，如果以可能导致崩溃的方式访问内存，Xcode将提醒您。


**异常退出[EXC_CRASH // SIGABRT]**

该过程异常退出。使用此异常类型导致崩溃的最常见原因是未被​​捕获的Objective-C / C ++ 异常和调用abort()。

如果App Extensions花费太多时间进行初始化（看门狗终止），它将以此异常类型终止。如果由于启动时挂起而导致扩展名被终止，则生成的崩溃报告的异常子类型将是LAUNCH_HANG。由于扩展没有main函数，因此初始化所花费的时间都发生在+load扩展和依赖库中的静态构造函数和方法中。你应该尽可能多地推迟这项工作。



**跟踪陷阱[EXC_BREAKPOINT // SIGTRAP]**



与异常退出类似，此异常旨在为附加的调试器提供在其执行的特定点中断进程的机会。您可以使用该__builtin_trap()函数从您自己的代码中触发此异常。如果未附加调试器，则终止该过程并生成崩溃报告。

较低级别的库（例如libdispatch）会在遇到致命错误时捕获进程。有关错误的其他信息可以在崩溃报告的“ 其他诊断信息”部分或设备的控制台中找到。

如果在运行时遇到意外情况，则Swift代码将以此异常类型终止，例如：

- 1、具有nil值的非可选类型
- 2、强制类型转换失败
 


**非法指令[EXC_BAD_INSTRUCTION // SIGILL]**
该进程试图执行非法或未定义的指令。该进程可能试图通过配置错误的函数指针跳转到无效地址。

在Intel处理器上，ud2操作码会导致EXC_BAD_INSTRUCTION异常，但通常用于捕获进程以进行调试。如果在运行时遇到意外情况，则Intel处理器上的Swift代码将以此异常类型终止。有关详细信息，请参阅跟踪陷阱

**退出[SIGQUIT]**

该进程在另一个进程的请求下终止，并具有管理其生命周期的权限。SIGQUIT并不意味着该过程崩溃，但它确实可能以可检测的方式行为不端。

在iOS上，如果加载时间过长，主机应用将退出键盘扩展。崩溃报告中显示的Backtraces不太可能指向负责的代码。最有可能的是，扩展的启动路径上的一些其他代码需要很长时间才能完成，但在时间限制之前完成，并且当扩展退出时执行移动到Backtraces中显示的代码。您应该对扩展进行概要分析，以便更好地了解启动期间大多数工作的位置，并将该工作移至后台线程或将其推迟到以后（扩展加载后）。

**被杀[SIGKILL]**

该过程在系统请求时终止。查看“ 终止原因”字段以更好地了解终止原因。

该终止原因字段将包含一个名称空间，然后一个代码。以下代码特定于watchOS：

- 1、终止代码0xc51bad01表示监视应用程序已终止，因为它在执行后台任务时使用了太多CPU时间。要解决此问题，请优化执行后台任务的代码以提高CPU效率，或减少应用程序在后台运行时执行的工作量。
- 2、终止代码0xc51bad02表示监视应用程序因未能在分配的时间内完成后台任务而终止。要解决此问题，请减少应用在后台运行时执行的工作量。
- 3、终止代码0xc51bad03表示监视应用程序未能在分配的时间内完成后台任务，并且系统整体上非常繁忙，以至于应用程序可能没有多少CPU时间来执行后台任务。虽然应用程序可以通过减少它在后台任务中执行的工作量来避免此问题，0xc51bad03但并不表示该应用程序执行了任何错误操作。更有可能的是，由于整体系统负载，应用程序无法完成其工作


**保护资源违规[EXC_GUARD]**

该过程违反了受保护的资源保护。系统库可能会将某些文件描述符标记为保护，之后对这些描述符的正常操作将触发EXC_GUARD异常（当它想要对这些文件描述符进行操作时，系统使用特殊的“保护”私有API）。这有助于您快速跟踪问题，例如关闭系统库打开的文件描述符。例如，如果某个应用程序关闭了用于访问支持Core Data存储的SQLite文件的文件描述符，那么Core Data将在以后神秘地崩溃。保护异常会更快地发现这些问题，从而使它们更容易调试。

来自较新版本的iOS的崩溃报告包括有关EXC_GUARD在异常子类型和异常消息字段中导致异常的操作的人类可读详细信息。在来自macOS或旧版iOS的崩溃报告中，此信息被编码为第一个异常代码，作为位域，按如下方式分解：


**资源限制[EXC_RESOURCE]**


该过程超出了资源消耗限制。这是来自操作系统的通知，该进程使用了​​太多资源。确切的资源列在Exception Subtype字段中。如果包含“ 异常备注”字段NON-FATAL CONDITION，则即使生成了崩溃报告，也不会终止该进程。

- 1、异常子类型MEMORY表示进程已超过系统强加的内存限制。这可能是终止超额内存使用的先兆。
- 2、异常子类型WAKEUPS表示进程中的线程每秒被唤醒太多次，这迫使CPU经常唤醒并消耗电池寿命。

通常，这是由线程到线程的通信（通常使用peformSelector:onThread:或者dispatch_async）引起的，这种通信在不知不觉中发生的频率远远超过它应该发生的频率。因为触发此异常的通信类型经常发生，所以通常会有多个具有非常相似的Backtraces的后台线程- 指示通信的来源。



**其他异常类型**
某些崩溃报告可能包含未命名的异常类型，它将打印为十六进制值（例如00000020）。如果您收到其中一个崩溃报告，请直接查看“ 例外代码”字段以获取更多信息。

- 1、异常代码0xbaaaaaad表示日志是整个系统的堆栈，而不是崩溃报告。要拍摄叠印，请同时按侧面按钮和两个音量按钮。这些日志通常是由用户意外创建的，并不表示错误。
- 2、异常代码0xbad22222表示iOS已终止VoIP应用程序，因为它过于频繁地恢复。
- 3、异常代码0x8badf00d表示iOS已终止应用程序，因为发生了监视程序超时。应用程序启动，终止或响应系统事件花费的时间太长。其中一个常见原因是在主线程上进行同步网络连接。无论什么操作都Thread 0需要移动到后台线程，或者以不同的方式处理，以便它不会阻塞主线程。
- 4、异常代码0xc00010ff表示应用程序被操作系统杀死以响应热事件。这可能是由于发生此崩溃的特定设备或其运行环境的问题。有关使您的应用程序更高效运行的提示，请参阅iOS性能和使用Instruments WWDC会话进行功耗优化。
- 5、异常代码0xdead10cc表示应用程序已被操作系统终止，因为它在挂起期间保留了文件锁或sqlite数据库锁。如果您的应用程序在挂起时对锁定文件或sqlite数据库执行操作，则它必须请求额外的后台执行时间来完成这些操作并在挂起之前放弃锁定。
- 6、异常代码0x2bad45ec表示由于安全违规而导致应用程序被iOS终止。终止描述“在安全模式下检测到进行不安全绘制的过程”表示应用程序试图在不允许的情况下绘制到屏幕，例如屏幕被锁定时。用户可能不会注意到此终止，因为屏幕关闭或发生此终止时会显示锁定屏幕。

```
使用应用切换器终止暂停的应用不会生成崩溃报告。应用程序暂停后，它有资格随时被iOS终止，因此不会生成崩溃报告。


```


**其他诊断信息**
本节包括特定于终止类型的其他诊断信息，其中可能包括：

- 1、特定于应用程序的信息：在进程终止之前捕获的框架错误消息
- 2、内核消息：有关代码签名问题的详细信息
- 3、Dyld错误消息：动态链接器发出的错误消息


**流程终止时生成的崩溃报告中的“应用程序特定信息”部分的摘录，因为找不到链接的框架**

```
Dyld Error Message:
Dyld Message: Library not loaded: @rpath/MyCustomFramework.framework/MyCustomFramework
Referenced from: /private/var/containers/Bundle/Application/CD9DB546-A449-41A4-A08B-87E57EE11354/TheElements.app/TheElements
Reason: no suitable image found.

```

**流程终止时生成的崩溃报告中的“特定于应用程序的信息”部分的摘录，因为它无法快速加载其初始视图控制器**

```
Application Specific Information:
com.example.apple-samplecode.TheElements failed to scene-create after 19.81s (launch took 0.19s of total time limit 20.00s)

Elapsed total CPU time (seconds): 7.690 (user 7.690, system 0.000), 19% CPU
Elapsed application CPU time (seconds): 0.697, 2% CPU

```

**回溯**

崩溃报告中最有趣的部分是它终止时每个进程线程的回溯。这些跟踪中的每一条都与将进程与调试器暂停时看到的类似

```
Thread 0 name: Dispatch queue: com.apple.main-thread
Thread 0 Crashed:
0   TheElements                       0x000000010006bc20 -[AtomicElementViewController myTransitionDidStop:finished:context:] (AtomicElementViewController.m:203)
1   UIKit                             0x0000000194cef0f0 -[UIViewAnimationState sendDelegateAnimationDidStop:finished:] + 312
2   UIKit                             0x0000000194ceef30 -[UIViewAnimationState animationDidStop:finished:] + 160
3   QuartzCore                        0x0000000192178404 CA::Layer::run_animation_callbacks(void*) + 260
4   libdispatch.dylib                 0x000000018dd6d1c0 _dispatch_client_callout + 16
5   libdispatch.dylib                 0x000000018dd71d6c _dispatch_main_queue_callback_4CF + 1000
6   CoreFoundation                    0x000000018ee91f2c __CFRUNLOOP_IS_SERVICING_THE_MAIN_DISPATCH_QUEUE__ + 12
7   CoreFoundation                    0x000000018ee8fb18 __CFRunLoopRun + 1660
8   CoreFoundation                    0x000000018edbe048 CFRunLoopRunSpecific + 444
9   GraphicsServices                  0x000000019083f198 GSEventRunModal + 180
10  UIKit                             0x0000000194d21bd0 -[UIApplication _run] + 684
11  UIKit                             0x0000000194d1c908 UIApplicationMain + 208
12  TheElements                       0x00000001000653c0 main (main.m:55)
13  libdyld.dylib                     0x000000018dda05b8 start + 4

Thread 1:
0   libsystem_kernel.dylib            0x000000018deb2a88 __workq_kernreturn + 8
1   libsystem_pthread.dylib           0x000000018df75188 _pthread_wqthread + 968
2   libsystem_pthread.dylib           0x000000018df74db4 start_wqthread + 4
```

第一行列出了线程号和当前正在执行的调度队列的标识符。其余行列出了有关回溯中各个堆栈帧的详细信息。从左到右：

- 1、堆栈帧号。堆栈帧以调用顺序呈现，其中第0帧是在执行暂停时执行的函数。第一帧是在第0帧调用函数的函数，依此类推。
- 2、堆栈帧的执行函数所在的二进制文件的名称。
- 3、对于第0帧，执行停止时执行的机器指令的地址。对于剩余的堆栈帧，当控制返回到堆栈帧时将下一次执行的机器指令的地址。
- 4、在符号化崩溃报告中，堆栈框架中函数的方法名称。


**来自非符号化崩溃报告的Last Exception Backtrace部分的摘录。**
```
Last Exception Backtrace:
(0x18eee41c0 0x18d91c55c 0x18eee3e88 0x18f8ea1a0 0x195013fe4 0x1951acf20 0x18ee03dc4 0x1951ab8f4 0x195458128 0x19545fa20 0x19545fc7c 0x19545ff70 0x194de4594 0x194e94e8c 0x194f47d8c 0x194f39b40 0x194ca92ac 0x18ee917dc 0x18ee8f40c 0x18ee8f89c 0x18edbe048 0x19083f198 0x194d21bd0 0x194d1c908 0x1000ad45c 0x18dda05b8)
```
必须对包含仅包含十六进制地址的Last Exception Backtrace的崩溃日志进行符号化，以生成可用的回溯


**号化崩溃报告中的Last Exception Backtrace部分的摘录。在应用程序的故事板中加载场景时引发了此异常。缺少用于连接到场景中元素的相应IBOutlet**

```
Last Exception Backtrace:
0   CoreFoundation                    0x18eee41c0 __exceptionPreprocess + 124
1   libobjc.A.dylib                   0x18d91c55c objc_exception_throw + 56
2   CoreFoundation                    0x18eee3e88 -[NSException raise] + 12
3   Foundation                        0x18f8ea1a0 -[NSObject(NSKeyValueCoding) setValue:forKey:] + 272
4   UIKit                             0x195013fe4 -[UIViewController setValue:forKey:] + 104
5   UIKit                             0x1951acf20 -[UIRuntimeOutletConnection connect] + 124
6   CoreFoundation                    0x18ee03dc4 -[NSArray makeObjectsPerformSelector:] + 232
7   UIKit                             0x1951ab8f4 -[UINib instantiateWithOwner:options:] + 1756
8   UIKit                             0x195458128 -[UIStoryboard instantiateViewControllerWithIdentifier:] + 196
9   UIKit                             0x19545fa20 -[UIStoryboardSegueTemplate instantiateOrFindDestinationViewControllerWithSender:] + 92
10  UIKit                             0x19545fc7c -[UIStoryboardSegueTemplate _perform:] + 56
11  UIKit                             0x19545ff70 -[UIStoryboardSegueTemplate perform:] + 160
12  UIKit                             0x194de4594 -[UITableView _selectRowAtIndexPath:animated:scrollPosition:notifyDelegate:] + 1352
13  UIKit                             0x194e94e8c -[UITableView _userSelectRowAtPendingSelectionIndexPath:] + 268
14  UIKit                             0x194f47d8c _runAfterCACommitDeferredBlocks + 292
15  UIKit                             0x194f39b40 _cleanUpAfterCAFlushAndRunDeferredBlocks + 560
16  UIKit                             0x194ca92ac _afterCACommitHandler + 168
17  CoreFoundation                    0x18ee917dc __CFRUNLOOP_IS_CALLING_OUT_TO_AN_OBSERVER_CALLBACK_FUNCTION__ + 32
18  CoreFoundation                    0x18ee8f40c __CFRunLoopDoObservers + 372
19  CoreFoundation                    0x18ee8f89c __CFRunLoopRun + 1024
20  CoreFoundation                    0x18edbe048 CFRunLoopRunSpecific + 444
21  GraphicsServices                  0x19083f198 GSEventRunModal + 180
22  UIKit                             0x194d21bd0 -[UIApplication _run] + 684
23  UIKit                             0x194d1c908 UIApplicationMain + 208
24  TheElements                       0x1000ad45c main (main.m:55)
25  libdyld.dylib                     0x18dda05b8 start + 4

```



64位iOS使用“零成本”异常实现。在“零成本”系统中，每个函数都有附加数据，这些数据描述了如果在函数中抛出异常，如何展开堆栈。如果在没有展开数据的堆栈帧中抛出异常，则异常处理无法继续，进程将停止。堆栈上可能有一个异常处理程序，但如果没有一个框架的展开数据，那么就无法从抛出异常的堆栈框架到达那里。指定该-no_compact_unwind标志意味着您没有获得该代码的展开表，因此您不能在这些函数之间抛出异常。

此外，如果要在应用程序或库中包含纯C代码，则可能需要指定该-funwind-tables标志以包含该代码中所有函数的展开表。


#### 线程状态

本节列出了崩溃线程的线程状态。这是一个寄存器列表及其执行停止时的值。在阅读崩溃报告时，无需了解线程状态，但您可以使用此信息更好地了解崩溃的情况

**来自ARM64设备的崩溃报告的“线程状态”部分的摘录。**

```
Thread 0 crashed with ARM Thread State (64-bit):
x0: 0x0000000000000000   x1: 0x000000019ff776c8   x2: 0x0000000000000000   x3: 0x000000019ff776c8
x4: 0x0000000000000000   x5: 0x0000000000000001   x6: 0x0000000000000000   x7: 0x00000000000000d0
x8: 0x0000000100023920   x9: 0x0000000000000000  x10: 0x000000019ff7dff0  x11: 0x0000000c0000000f
x12: 0x000000013e63b4d0  x13: 0x000001a19ff75009  x14: 0x0000000000000000  x15: 0x0000000000000000
x16: 0x0000000187b3f1b9  x17: 0x0000000181ed488c  x18: 0x0000000000000000  x19: 0x000000013e544780
x20: 0x000000013fa49560  x21: 0x0000000000000001  x22: 0x000000013fc05f90  x23: 0x000000010001e069
x24: 0x0000000000000000  x25: 0x000000019ff776c8  x26: 0xee009ec07c8c24c7  x27: 0x0000000000000020
x28: 0x0000000000000000  fp: 0x000000016fdf29e0   lr: 0x0000000100017cf8
sp: 0x000000016fdf2980   pc: 0x0000000100017d14 cpsr: 0x60000000

```


**崩溃报告的二进制映像部分中应用程序条目的摘录**

```
Binary Images:
0x100060000 - 0x100073fff TheElements arm64 <2defdbea0c873a52afa458cf14cd169e> /var/containers/Bundle/Application/888C1FA2-3666-4AE2-9E8E-62E2F787DEC1/TheElements.app/TheElements
...
```

每行包括单个二进制图像的以下详细信息：

- 进程中的二进制映像的地址空间。
- 二进制文件的二进制名称或包标识符（仅限macOS）。在来自macOS的崩溃报告中，如果二进制文件是操作系统的一部分，则前缀为（+）。
- （仅限macOS）二进制文件的短版本字符串和包版本，用短划线分隔。
- （仅限iOS）二进制图像的体系结构。二进制文件可能包含多个“切片”，每个“切片”支持一个体系结构。这些切片中只有一个加载到过程中。
- 唯一标识二进制映像的UUID。此值随二进制的每个构建而变化，用于在表示崩溃报告时定位相应的dSYM文件。
- 磁盘上二进制文件的路径

#### 了解低内存报告

当检测到低内存条件时，iOS中的虚拟内存系统依赖于应用程序的协作来释放内存。低内存通知作为释放内存的请求发送到所有正在运行的应用程序和进程，希望减少使用的内存量。如果内存压力仍然存在，系统可以终止后台进程以减轻内存压力。如果可以释放足够的内存，您的应用程序将继续运行。如果没有，您的应用程序将被iOS终止，因为没有足够的内存来满足应用程序的需求，并且将生成低内存报告并将其存储在设备上。

低内存报告的格式与其他崩溃报告的不同之处在于，应用程序线程没有回溯。低内存报告以类似于崩溃报告的标头的标头开头。标题后面是列出系统范围内存统计信息的字段集合。记下“ 页面大小”字段的值。低内存报告中每个进程的内存使用量按内存页数报告。

低内存报告中最重要的部分是进程表。此表列出了生成低内存报告时所有正在运行的进程，包括系统守护程序。如果一个过程被“抛弃”，原因将列在[reason]列下。一个过程可能会被抛弃


- 1、[per-process-limit]：该进程超过了系统强加的内存限制。驻留内存的每进程限制由系统为所有应用程序建立。越过此限制使该过程有资格终止。
- 2、[vm-pageshortage] / [vm-thrashing] / [vm]：由于内存压力，该进程被终止。
- 3、[vnode-limit]：打开的文件太多。
- 4、[highwater]：系统守护进程越过其高水位标记以便使用内存。
- 5、[jettisoned]：由于其他原因，该过程被抛弃了。















