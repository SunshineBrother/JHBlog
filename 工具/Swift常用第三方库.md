<head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=Edge">
<meta name="viewport" content="width=device-width, initial-scale=1.0,user-scalable=no">

<!-- Start of Baidu Transcode -->
<meta http-equiv="Cache-Control" content="no-siteapp">
<meta http-equiv="Cache-Control" content="no-transform">
<meta name="applicable-device" content="pc,mobile">
<meta name="MobileOptimized" content="width">
<meta name="HandheldFriendly" content="true">
<meta name="mobile-agent" content="format=html5;url=https://www.jianshu.com/p/f4282df18537">
<!-- End of Baidu Transcode -->

<meta name="description" content="网络 Alamofire:http网络请求事件处理的框架。 Moya:这是一个基于Alamofire的更高层网络请求封装抽象层。 Reachability.swift:用来检查应用当前的网络连接状况。 综合 Perfect:swift的服务器端开发框架（针对于移动后端开发、网站和web应用程序开发）。 RxSwift:函数响应式编程框架，是ReactiveX的swift版本，可以简化异步操作...">

<meta name="360-site-verification" content="604a14b53c6b871206001285921e81d8">
<meta property="wb:webmaster" content="294ec9de89e7fadb">
<meta property="qc:admins" content="104102651453316562112116375">
<meta property="qc:admins" content="11635613706305617">
<meta property="qc:admins" content="1163561616621163056375">
<meta name="google-site-verification" content="cV4-qkUJZR6gmFeajx_UyPe47GW9vY6cnCrYtCHYNh4">
<meta name="google-site-verification" content="HF7lfF8YEGs1qtCE-kPml8Z469e2RHhGajy6JPVy5XI">
<meta http-equiv="mobile-agent" content="format=html5; url=https://www.jianshu.com/p/f4282df18537">

<!-- Apple -->
<meta name="apple-mobile-web-app-title" content="简书">

<!--  Meta for Smart App Banner -->
<meta name="apple-itunes-app" content="app-id=888237539, app-argument=jianshu://notes/22347247">
<!-- End -->

<!--  Meta for Twitter Card -->
<meta content="summary" property="twitter:card">
<meta content="@jianshucom" property="twitter:site">
<meta content="Swift常用第三方库" property="twitter:title">
<meta content="网络 Alamofire:http网络请求事件处理的框架。 Moya:这是一个基于Alamofire的更高层网络请求封装抽象层。 Reachability.swift:用来检..." property="twitter:description">
<meta content="https://www.jianshu.com/p/f4282df18537" property="twitter:url">
<!-- End -->

<!--  Meta for OpenGraph -->
<meta property="fb:app_id" content="865829053512461">
<meta property="og:site_name" content="简书">
<meta property="og:title" content="Swift常用第三方库">
<meta property="og:type" content="article">
<meta property="og:url" content="https://www.jianshu.com/p/f4282df18537">
<meta property="og:description" content="网络 Alamofire:http网络请求事件处理的框架。 Moya:这是一个基于Alamofire的更高层网络请求封装抽象层。 Reachability.swift:用来检查应用当前的网络连接...">
<!-- End -->

<!--  Meta for Facebook Applinks -->
<meta property="al:ios:url" content="jianshu://notes/22347247">
<meta property="al:ios:app_store_id" content="888237539">
<meta property="al:ios:app_name" content="简书">

<meta property="al:android:url" content="jianshu://notes/22347247">
<meta property="al:android:package" content="com.jianshu.haruki">
<meta property="al:android:app_name" content="简书">
<!-- End -->


<title>Swift常用第三方库 - 简书</title>

<meta name="csrf-param" content="authenticity_token">
<meta name="csrf-token" content="YEkcccL6UsUOJFMeBoHhlylcMJzgONbP8oDS4Y7siVLbl91GFHdX7KHf2zVrpfgn8rS7wYC5vP6lZwHjklXNzQ==">

<link rel="stylesheet" media="all" href="//cdn2.jianshu.io/assets/web-d5108cec60c4ed55f041.css">

<link rel="stylesheet" media="all" href="//cdn2.jianshu.io/assets/web/pages/notes/show/entry-f1bfe3a5bcbd20b68049.css">

<link href="//cdn2.jianshu.io/assets/favicons/favicon-e743bfb1821442341c3ab15bdbe804f7ad97676bd07a770ccc9483473aa76f06.ico" rel="shortcut icon" type="image/x-icon">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/57-a6f1f1ee62ace44f6dc2f6a08575abd3c3b163288881c78dd8d75247682a4b27.png" sizes="57x57">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/72-fb9834bcfce738fd7b9c5e31363e79443e09a81a8e931170b58bc815387c1562.png" sizes="72x72">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/76-49d88e539ff2489475d603994988d871219141ecaa0b1a7a9a1914f4fe3182d6.png" sizes="76x76">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/114-24252fe693524ed3a9d0905e49bff3cbd0228f25a320aa09053c2ebb4955de97.png" sizes="114x114">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/120-1bb7371f5e87f93ce780a5f1a05ff1b176828ee0d1d130e768575918a2e05834.png" sizes="120x120">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/152-bf209460fc1c17bfd3e2b84c8e758bc11ca3e570fd411c3bbd84149b97453b99.png" sizes="152x152">

<!-- Start of 访问统计 -->
<script src="https://zz.bdstatic.com/linksubmit/push.js"></script><script src="//hm.baidu.com/hm.js?0c0e9d9b1e7d617b3e6842e85b9fb068"></script><script>
var _hmt = _hmt || [];
(function() {
var hm = document.createElement("script");
hm.src = "//hm.baidu.com/hm.js?0c0e9d9b1e7d617b3e6842e85b9fb068";
var s = document.getElementsByTagName("script")[0];
s.parentNode.insertBefore(hm, s);
})();
</script>

<!-- End of 访问统计 -->
<style type="text/css">@charset "UTF-8";.image-package .image-container{position:relative;z-index:2;background-color:#eee;-webkit-transition:background-color .1s linear;-o-transition:background-color .1s linear;transition:background-color .1s linear;margin:0 auto}body.reader-night-mode .image-package .image-container{background-color:#545454}.image-package .image-container-fill{z-index:1}.image-package .image-container .image-view{position:absolute;top:0;left:0;width:100%;height:100%;overflow:hidden}.image-package .image-container .image-view-error:after{content:"图片获取失败，请点击重试";position:absolute;top:50%;left:50%;width:100%;-webkit-transform:translate(-50%,-50%);-ms-transform:translate(-50%,-50%);transform:translate(-50%,-50%);color:#888;font-size:14px}.image-package .image-container .image-view img.image-loading{opacity:.3}.image-package .image-container .image-view img{-webkit-transition:all .15s linear;-o-transition:all .15s linear;transition:all .15s linear;z-index:2;opacity:1}</style><style type="text/css">fieldset[disabled] .multiselect {
pointer-events: none;
}

.multiselect__spinner {
position: absolute;
right: 1px;
top: 1px;
width: 48px;
height: 35px;
background: #fff;
display: block;
}

.multiselect__spinner:after,
.multiselect__spinner:before {
position: absolute;
content: "";
top: 50%;
left: 50%;
margin: -8px 0 0 -8px;
width: 16px;
height: 16px;
border-radius: 100%;
border-color: #41b883 transparent transparent;
border-style: solid;
border-width: 2px;
box-shadow: 0 0 0 1px transparent;
}

.multiselect__spinner:before {
animation: a 2.4s cubic-bezier(.41,.26,.2,.62);
animation-iteration-count: infinite;
}

.multiselect__spinner:after {
animation: a 2.4s cubic-bezier(.51,.09,.21,.8);
animation-iteration-count: infinite;
}

.multiselect__loading-enter-active,
.multiselect__loading-leave-active {
transition: opacity .4s ease-in-out;
opacity: 1;
}

.multiselect__loading-enter,
.multiselect__loading-leave-active {
opacity: 0;
}

.multiselect,
.multiselect__input,
.multiselect__single {
font-family: inherit;
font-size: 14px;
-ms-touch-action: manipulation;
touch-action: manipulation;
}

.multiselect {
box-sizing: content-box;
display: block;
position: relative;
width: 100%;
min-height: 40px;
text-align: left;
color: #35495e;
}

.multiselect * {
box-sizing: border-box;
}

.multiselect:focus {
outline: none;
}

.multiselect--disabled {
opacity: .6;
}

.multiselect--active {
z-index: 1;
}

.multiselect--active:not(.multiselect--above) .multiselect__current,
.multiselect--active:not(.multiselect--above) .multiselect__input,
.multiselect--active:not(.multiselect--above) .multiselect__tags {
border-bottom-left-radius: 0;
border-bottom-right-radius: 0;
}

.multiselect--active .multiselect__select {
transform: rotate(180deg);
}

.multiselect--above.multiselect--active .multiselect__current,
.multiselect--above.multiselect--active .multiselect__input,
.multiselect--above.multiselect--active .multiselect__tags {
border-top-left-radius: 0;
border-top-right-radius: 0;
}

.multiselect__input,
.multiselect__single {
position: relative;
display: inline-block;
min-height: 20px;
line-height: 20px;
border: none;
border-radius: 5px;
background: #fff;
padding: 0 0 0 5px;
width: 100%;
transition: border .1s ease;
box-sizing: border-box;
margin-bottom: 8px;
vertical-align: top;
}

.multiselect__tag~.multiselect__input,
.multiselect__tag~.multiselect__single {
width: auto;
}

.multiselect__input:hover,
.multiselect__single:hover {
border-color: #cfcfcf;
}

.multiselect__input:focus,
.multiselect__single:focus {
border-color: #a8a8a8;
outline: none;
}

.multiselect__single {
padding-left: 6px;
margin-bottom: 8px;
}

.multiselect__tags-wrap {
display: inline;
}

.multiselect__tags {
min-height: 40px;
display: block;
padding: 8px 40px 0 8px;
border-radius: 5px;
border: 1px solid #e8e8e8;
background: #fff;
}

.multiselect__tag {
position: relative;
display: inline-block;
padding: 4px 26px 4px 10px;
border-radius: 5px;
margin-right: 10px;
color: #fff;
line-height: 1;
background: #41b883;
margin-bottom: 5px;
white-space: nowrap;
overflow: hidden;
max-width: 100%;
text-overflow: ellipsis;
}

.multiselect__tag-icon {
cursor: pointer;
margin-left: 7px;
position: absolute;
right: 0;
top: 0;
bottom: 0;
font-weight: 700;
font-style: normal;
width: 22px;
text-align: center;
line-height: 22px;
transition: all .2s ease;
border-radius: 5px;
}

.multiselect__tag-icon:after {
content: "\D7";
color: #266d4d;
font-size: 14px;
}

.multiselect__tag-icon:focus,
.multiselect__tag-icon:hover {
background: #369a6e;
}

.multiselect__tag-icon:focus:after,
.multiselect__tag-icon:hover:after {
color: #fff;
}

.multiselect__current {
min-height: 40px;
overflow: hidden;
padding: 8px 12px 0;
padding-right: 30px;
white-space: nowrap;
border-radius: 5px;
border: 1px solid #e8e8e8;
}

.multiselect__current,
.multiselect__select {
line-height: 16px;
box-sizing: border-box;
display: block;
margin: 0;
text-decoration: none;
cursor: pointer;
}

.multiselect__select {
position: absolute;
width: 40px;
height: 38px;
right: 1px;
top: 1px;
padding: 4px 8px;
text-align: center;
transition: transform .2s ease;
}

.multiselect__select:before {
position: relative;
right: 0;
top: 65%;
color: #999;
margin-top: 4px;
border-style: solid;
border-width: 5px 5px 0;
border-color: #999 transparent transparent;
content: "";
}

.multiselect__placeholder {
color: #adadad;
display: inline-block;
margin-bottom: 10px;
padding-top: 2px;
}

.multiselect--active .multiselect__placeholder {
display: none;
}

.multiselect__content-wrapper {
position: absolute;
display: block;
background: #fff;
width: 100%;
max-height: 240px;
overflow: auto;
border: 1px solid #e8e8e8;
border-top: none;
border-bottom-left-radius: 5px;
border-bottom-right-radius: 5px;
z-index: 1;
-webkit-overflow-scrolling: touch;
}

.multiselect__content {
list-style: none;
display: inline-block;
padding: 0;
margin: 0;
min-width: 100%;
vertical-align: top;
}

.multiselect--above .multiselect__content-wrapper {
bottom: 100%;
border-bottom-left-radius: 0;
border-bottom-right-radius: 0;
border-top-left-radius: 5px;
border-top-right-radius: 5px;
border-bottom: none;
border-top: 1px solid #e8e8e8;
}

.multiselect__content::webkit-scrollbar {
display: none;
}

.multiselect__element {
display: block;
}

.multiselect__option {
display: block;
padding: 12px;
min-height: 40px;
line-height: 16px;
text-decoration: none;
text-transform: none;
vertical-align: middle;
position: relative;
cursor: pointer;
white-space: nowrap;
}

.multiselect__option:after {
top: 0;
right: 0;
position: absolute;
line-height: 40px;
padding-right: 12px;
padding-left: 20px;
}

.multiselect__option--highlight {
background: #41b883;
outline: none;
color: #fff;
}

.multiselect__option--highlight:after {
content: attr(data-select);
background: #41b883;
color: #fff;
}

.multiselect__option--selected {
background: #f3f3f3;
color: #35495e;
font-weight: 700;
}

.multiselect__option--selected:after {
content: attr(data-selected);
color: silver;
}

.multiselect__option--selected.multiselect__option--highlight {
background: #ff6a6a;
color: #fff;
}

.multiselect__option--selected.multiselect__option--highlight:after {
background: #ff6a6a;
content: attr(data-deselect);
color: #fff;
}

.multiselect--disabled {
background: #ededed;
pointer-events: none;
}

.multiselect--disabled .multiselect__current,
.multiselect--disabled .multiselect__select,
.multiselect__option--disabled {
background: #ededed;
color: #a6a6a6;
}

.multiselect__option--disabled {
cursor: text;
pointer-events: none;
}

.multiselect__option--disabled.multiselect__option--highlight {
background: #dedede!important;
}

.multiselect-enter-active,
.multiselect-leave-active {
transition: all .15s ease;
}

.multiselect-enter,
.multiselect-leave-active {
opacity: 0;
}

.multiselect__strong {
margin-bottom: 8px;
line-height: 20px;
display: inline-block;
vertical-align: top;
}

[dir=rtl] .multiselect {
text-align: right;
}

[dir=rtl] .multiselect__select {
right: auto;
left: 1px;
}

[dir=rtl] .multiselect__tags {
padding: 8px 8px 0 40px;
}

[dir=rtl] .multiselect__content {
text-align: right;
}

[dir=rtl] .multiselect__option:after {
right: auto;
left: 0;
}

[dir=rtl] .multiselect__clear {
right: auto;
left: 12px;
}

[dir=rtl] .multiselect__spinner {
right: auto;
left: 1px;
}

@keyframes a {
0% {
transform: rotate(0);
}

to {
transform: rotate(2turn);
}
}</style><style type="text/css">
#free-reward-panel .reward-users-modal main {
padding: 0;
}
</style><style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.reward-note-modal .v-modal {
width: 620px;
text-align: center;
}
.reward-note-modal .v-modal form {
margin: 0 auto 25px auto;
padding: 0 40px;
}
.reward-note-modal .v-modal .reward-intro {
margin-top: 20px;
margin-bottom: 20px;
font-size: 16px;
}
.reward-note-modal .v-modal .reward-intro .avatar {
cursor: default !important;
width: 36px;
height: 36px;
margin-right: 10px;
display: inline-block;
}
.reward-note-modal .v-modal .reward-intro .intro {
margin-right: 5px;
font-weight: bold;
vertical-align: middle;
}
.reward-note-modal .v-modal .reward-intro i {
color: #EA6F5A;
vertical-align: middle;
}
.reward-note-modal .v-modal .main-inputs {
margin: 25px 0;
}
.reward-note-modal .v-modal .main-inputs .amount-group {
margin: 0 -5px;
}
.reward-note-modal .v-modal .main-inputs .amount-group input {
display: none;
}
.reward-note-modal .v-modal .main-inputs .amount-group input:checked + .option {
color: #EA6F5A;
border-color: #EA6F5A;
}
.reward-note-modal .v-modal .main-inputs .amount-group .custom-amount:checked + .option .custom-text {
opacity: 0;
}
.reward-note-modal .v-modal .main-inputs .amount-group .custom-amount:checked + .option .custom-amount-input {
opacity: 1;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option {
position: relative;
margin: 0 5px 15px;
width: 156px;
height: 56px;
line-height: 54px;
border: 1px solid #E6E6E6;
border-radius: 4px;
font-weight: normal;
color: #999999;
cursor: pointer;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option i {
font-size: 16px;
vertical-align: middle;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .amount {
font-size: 28px;
vertical-align: middle;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .piece {
font-size: 13px;
vertical-align: sub;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input {
position: absolute;
top: 0;
z-index: -1;
width: 100%;
opacity: 0;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input i {
position: absolute;
top: 0;
left: 10px;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input .piece {
position: absolute;
top: 4px;
right: 10px;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input input {
display: block;
margin: 0 auto;
width: 80px;
height: 54px;
line-height: 54px;
border: none;
font-size: 28px;
text-align: center;
background: transparent;
-moz-appearance: textfield;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input input::-webkit-outer-spin-button, .reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input input::-webkit-inner-spin-button {
-webkit-appearance: none !important;
}
.reward-note-modal .v-modal .main-inputs .message {
padding: 15px 20px;
margin-bottom: 0;
font-size: 14px;
border: 1px solid #E6E6E6;
color: #333333;
border-radius: 4px;
background-color: rgba(180, 180, 180, 0.1);
}
.reward-note-modal .v-modal .main-inputs .message textarea {
width: 100%;
height: 44px;
padding: 0;
margin: 0;
resize: none;
background: none !important;
border: none !important;
-webkit-box-sizing: border-box;
box-sizing: border-box;
-webkit-box-shadow: none;
box-shadow: none;
}
.reward-note-modal .v-modal .main-inputs .message textarea:focus {
outline: none;
}
.reward-note-modal .v-modal .reward-info .amount {
font-size: 28px;
font-weight: bold;
color: #EA6F5A;
}
.reward-note-modal .v-modal .reward-info .pay-method {
font-size: 14px;
}
.reward-note-modal .v-modal .reward-info .pay-method a {
color: #3194D0;
}
.reward-note-modal .v-modal .choose-pay {
margin: 0 -5px;
}
.reward-note-modal .v-modal .choose-pay input {
display: none;
}
.reward-note-modal .v-modal .choose-pay input:checked + .option {
color: #EA6F5A;
border-color: #EA6F5A;
}
.reward-note-modal .v-modal .choose-pay .option {
margin: 20px 5px 10px;
width: 156px;
height: 56px;
line-height: 54px;
text-align: center;
border: 1px solid #E6E6E6;
border-radius: 4px;
cursor: pointer;
}
.reward-note-modal .v-modal .choose-pay .option img {
height: 30px;
}
.reward-note-modal .v-modal .choose-pay .option img.day.alipay, .reward-note-modal .v-modal .choose-pay .option img.night.alipay {
min-width: 85px;
}
.reward-note-modal .v-modal .choose-pay .option img.day.wechat, .reward-note-modal .v-modal .choose-pay .option img.night.wechat {
min-width: 112px;
}
.reward-note-modal .v-modal .choose-pay .option img.night {
display: none;
}
.reward-note-modal .v-modal .choose-pay .tooltip {
width: 230px;
}
.reward-note-modal .v-modal .modal-footer {
padding: 0 15px 20px;
border: none;
background-color: transparent;
text-align: center;
}
.reward-note-modal .v-modal .modal-footer .btn {
padding: 8px 45px;
font-size: 24px;
}
.reward-note-modal .v-modal .btn-pay {
padding: 8px 25px;
font-size: 16px;
color: #ffffff;
background-color: #F5A623;
}
.weixin-pay, .success-pay {
text-align: center;
}
.weixin-pay .v-modal, .success-pay .v-modal {
width: 350px;
}
.weixin-pay .ic-successed, .success-pay .ic-successed {
font-size: 60px;
color: #3db922;
}
.weixin-pay h2, .weixin-pay h3, .success-pay h2, .success-pay h3 {
margin-bottom: 20px;
color: #333333;
}
.weixin-pay h2, .success-pay h2 {
margin: 0 0 40px 0;
font-size: 24px;
}
.weixin-pay .bind-text, .success-pay .bind-text {
position: relative;
margin-bottom: 30px;
font-size: 14px;
color: #999999;
}
.weixin-pay .bind-text:before, .weixin-pay .bind-text:after, .success-pay .bind-text:before, .success-pay .bind-text:after {
content: "";
border-top: 1px solid #999;
display: block;
position: absolute;
width: 40px;
top: 8px;
}
.weixin-pay .bind-text:before, .success-pay .bind-text:before {
left: 30px;
}
.weixin-pay .bind-text:after, .success-pay .bind-text:after {
right: 30px;
}
.weixin-pay .share-bind, .success-pay .share-bind {
display: block;
margin-bottom: 30px;
}
.weixin-pay .share-bind i, .success-pay .share-bind i {
margin-right: 4px;
font-size: 22px;
vertical-align: middle;
}
.weixin-pay .share-bind.wechat i, .success-pay .share-bind.wechat i {
color: #00BB29;
}
.weixin-pay .share-bind.weibo i, .success-pay .share-bind.weibo i {
color: #E05244;
}
.weixin-pay .wx-qr-code, .success-pay .wx-qr-code {
display: inline-block;
}
.weixin-pay .wx-qr-code img, .success-pay .wx-qr-code img {
margin: 0 auto;
padding: 10px;
width: 200px;
background-color: #ffffff;
}
.weixin-pay .pay-amount, .success-pay .pay-amount {
margin: 20px 0;
color: #787878;
}
.weixin-pay .pay-amount span, .success-pay .pay-amount span {
color: #F5A623;
}
</style><style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.v-modal-wrap {
position: fixed;
left: 0;
top: 0;
right: 0;
bottom: 0;
z-index: 9999;
background-color: transparent;
}
.v-modal-wrap.modal-leave-active {
-webkit-transition: opacity 0.3s;
-o-transition: opacity 0.3s;
transition: opacity 0.3s;
}
.v-modal-wrap.modal-enter-active .v-modal-mask, .v-modal-wrap.modal-leave-active .v-modal-mask {
opacity: 0;
}
.v-modal-wrap.modal-enter-active .v-modal, .v-modal-wrap.modal-leave-active .v-modal {
-webkit-transform: translate(-50%, -70%);
-ms-transform: translate(-50%, -70%);
transform: translate(-50%, -70%);
opacity: 0;
}
.v-modal-wrap .v-modal-mask {
background-color: rgba(255, 255, 255, 0.7);
position: absolute;
left: 0;
right: 0;
top: 0;
bottom: 0;
-webkit-transition: opacity 0.3s;
-o-transition: opacity 0.3s;
transition: opacity 0.3s;
opacity: 1;
}
.v-modal-wrap .v-modal {
position: absolute;
left: 50%;
top: 50%;
-webkit-transform: translate(-50%, -50%);
-ms-transform: translate(-50%, -50%);
transform: translate(-50%, -50%);
border-radius: 6px;
border: 1px solid rgba(0, 0, 0, 0.1);
background-color: #fff;
-webkit-box-shadow: 0 5px 25px rgba(0, 0, 0, 0.1);
box-shadow: 0 5px 25px rgba(0, 0, 0, 0.1);
-webkit-transition: opacity 0.3s, -webkit-transform 0.3s;
transition: opacity 0.3s, -webkit-transform 0.3s;
-o-transition: opacity 0.3s, transform 0.3s;
transition: opacity 0.3s, transform 0.3s;
transition: opacity 0.3s, transform 0.3s, -webkit-transform 0.3s;
opacity: 1;
display: -webkit-box;
display: -webkit-flex;
display: -ms-flexbox;
display: flex;
-webkit-box-orient: vertical;
-webkit-box-direction: normal;
-webkit-flex-direction: column;
-ms-flex-direction: column;
flex-direction: column;
overflow: hidden;
}
.v-modal-wrap .v-modal > header:before, .v-modal-wrap .v-modal > header:after, .v-modal-wrap .v-modal > main:before, .v-modal-wrap .v-modal > main:after, .v-modal-wrap .v-modal > footer:before, .v-modal-wrap .v-modal > footer:after {
content: '';
clear: both;
display: table;
}
.v-modal-wrap .v-modal > header {
padding: 20px;
border-bottom: 1px solid #F0F0F0;
}
.v-modal-wrap .v-modal > header h4 {
margin: 0;
color: #333;
text-align: left;
}
.v-modal-wrap .v-modal .close {
position: absolute;
right: 16px;
top: 20px;
font-size: 26px;
line-height: 20px;
color: rgba(0, 0, 0, 0.8);
}
.v-modal-wrap .v-modal .close:hover {
color: #000000;
}
.v-modal-wrap .v-modal > main {
padding: 20px 20px 20px 20px;
font-size: 15px;
color: #333;
-webkit-box-flex: 1;
-webkit-flex-grow: 1;
-ms-flex-positive: 1;
flex-grow: 1;
overflow-x: hidden;
overflow-y: auto;
}
.v-modal-wrap .v-modal > footer {
padding: 20px;
background-color: #fff;
}
.v-modal-wrap .v-modal > footer button {
padding: 0;
margin: 0;
background-color: transparent;
border: 0;
float: right;
}
.v-modal-wrap .v-modal > footer button:focus {
outline: 0;
}
.v-modal-wrap .v-modal > footer .submit {
padding: 4px 12px;
border: 1px solid;
border-radius: 20px;
}
.v-modal-wrap .v-modal > footer .cancel {
margin-top: 5px;
}
.v-modal-wrap .v-modal > footer .cancel:hover {
color: #333333;
}
.reader-night-mode .v-modal-wrap .v-modal-mask {
background-color: rgba(63, 63, 63, 0.7);
}
.reader-night-mode .v-modal-wrap .v-modal {
background-color: #3f3f3f;
}
.reader-night-mode .v-modal-wrap .v-modal header {
border-color: #2F2F2F;
}
.reader-night-mode .v-modal-wrap .v-modal header h4 {
color: #C8C8C8;
}
.reader-night-mode .v-modal-wrap .v-modal .close {
color: #C8C8C8;
}
.reader-night-mode .v-modal-wrap .v-modal .close:hover {
color: #ffffff;
}
.reader-night-mode .v-modal-wrap .v-modal main {
color: #C8C8C8;
}
.reader-night-mode .v-modal-wrap .v-modal footer {
background-color: #3f3f3f;
}
.reader-night-mode .v-modal-wrap .v-modal footer .cancel:hover {
color: #C8C8C8;
}
</style><style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.like[data-v-6ddd02c6] {
display: inline-block;
}
.like .like-group[data-v-6ddd02c6] {
position: relative;
padding: 13px 0 15px 0;
font-size: 0;
border: 1px solid #EA6F5A;
border-radius: 40px;
}
.like .like-group[data-v-6ddd02c6]:hover {
background-color: rgba(236, 97, 73, 0.05);
}
.like .like-group .btn-like[data-v-6ddd02c6] {
display: inline-block;
font-size: 19px;
}
.like .like-group .btn-like[data-v-6ddd02c6]:before {
content: '';
position: absolute;
left: 12px;
top: 2px;
width: 50px;
height: 50px;
background-image: url(//cdn2.jianshu.io/assets/web/like_animation_steps-62a00a7b52377d3069927cdb8e61fd34.png);
background-position: left;
background-repeat: no-repeat;
background-size: 1000px 50px;
}
.like .like-group .btn-like a[data-v-6ddd02c6] {
position: relative;
padding: 18px 30px 18px 55px;
color: #EA6F5A;
}
.like .like-group .modal-wrap[data-v-6ddd02c6] {
font-size: 18px;
border-left: 1px solid rgba(236, 97, 73, 0.4);
display: inline-block;
margin-left: -15px;
}
.like .like-group .modal-wrap a[data-v-6ddd02c6] {
color: #EA6F5A;
padding: 18px 26px 18px 18px;
}
.like .like-group.like-animation[data-v-6ddd02c6], .like .like-group.active[data-v-6ddd02c6] {
background-color: #EA6F5A;
}
.like .like-group.like-animation .btn-like a[data-v-6ddd02c6], .like .like-group.active .btn-like a[data-v-6ddd02c6] {
color: white;
}
.like .like-group.like-animation .modal-wrap[data-v-6ddd02c6], .like .like-group.active .modal-wrap[data-v-6ddd02c6] {
border-left: 1px solid white;
}
.like .like-group.like-animation .modal-wrap a[data-v-6ddd02c6], .like .like-group.active .modal-wrap a[data-v-6ddd02c6] {
color: white;
}
.like .like-group.like-animation .btn-like[data-v-6ddd02c6]:before {
-webkit-animation: likeBlast-data-v-6ddd02c6 0.6s 1 steps(19);
animation: likeBlast-data-v-6ddd02c6 0.6s 1 steps(19);
background-position: right;
}
@-webkit-keyframes likeBlast {
0% {
background-position: left;
}
100% {
background-position: right;
}
}
@keyframes likeBlast-data-v-6ddd02c6 {
0% {
background-position: left;
}
100% {
background-position: right;
}
}
.like .like-group.active .btn-like[data-v-6ddd02c6]:before {
background-position: right;
}
</style><style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.main {
position: relative;
margin: 0 auto;
padding: 0 0 30px 0;
width: 620px;
}
.main .title {
padding-left: 8px;
border-left: 3px solid #EA6F5A;
line-height: 1;
font-size: 15px;
}
.main .collection-settings {
position: absolute;
top: 2px;
right: 0;
font-size: 13px;
color: #A0A0A0;
}
.main .collection-settings span {
padding-left: 4px;
}
.main .include-collection {
width: 100%;
padding-top: 20px;
display: -webkit-box;
display: -webkit-flex;
display: -ms-flexbox;
display: flex;
-webkit-box-orient: horizontal;
-webkit-box-direction: normal;
-webkit-flex-direction: row;
-ms-flex-direction: row;
flex-direction: row;
-webkit-box-pack: start;
-webkit-justify-content: flex-start;
-ms-flex-pack: start;
justify-content: flex-start;
-webkit-box-align: center;
-webkit-align-items: center;
-ms-flex-align: center;
align-items: center;
-webkit-flex-wrap: wrap;
-ms-flex-wrap: wrap;
flex-wrap: wrap;
}
.main .include-collection .item {
display: inline-block;
margin: 0 12px 12px 0;
min-height: 32px;
background-color: white;
border: 1px solid #DCDCDC;
border-radius: 4px;
vertical-align: top;
overflow: hidden;
}
.main .include-collection .item img {
width: 32px;
height: 32px;
}
.main .include-collection .item .name {
display: inline-block;
padding: 0 10px;
font-size: 14px;
}
.main .include-collection .add-collection-wrap {
margin: 0 12px 12px 0;
}
.main .include-collection .add-collection {
padding: 8px 12px;
font-size: 14px;
border: 1px solid #DCDCDC;
border-radius: 4px;
}
.main .include-collection .add-collection i {
margin-right: 4px;
color: #969696;
}
.main .recommend-note a {
position: relative;
margin: 20px 2px 0 0;
width: 200px;
height: 160px;
display: inline-block;
}
.main .recommend-note a:after {
content: "";
position: absolute;
width: 200px;
height: 160px;
border-radius: 0 0 4px 4px;
-webkit-box-shadow: inset 0px -80px 50px -22px rgba(0, 0, 0, 0.6);
box-shadow: inset 0px -80px 50px -22px rgba(0, 0, 0, 0.6);
top: 0;
left: 0;
z-index: 1;
}
.main .recommend-note .name {
position: absolute;
bottom: 40px;
left: 10px;
right: 10px;
font-size: 17px;
font-weight: bold;
color: #ffffff;
z-index: 2;
}
.main .recommend-note .author {
position: absolute;
bottom: 10px;
left: 10px;
right: 10px;
z-index: 2;
}
.main .recommend-note .avatar {
width: 20px;
height: 20px;
display: inline-block;
}
.main .recommend-note .avatar img {
border-radius: 50%;
}
.main .recommend-note .author-name {
font-size: 12px;
color: #ffffff;
display: inline-block;
vertical-align: -1px;
}
.main .show-more {
margin: 0 12px 12px 0;
font-size: 14px;
color: #A0A0A0;
}
<style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.main {
position: relative;
margin: 0 auto;
padding: 0 0 30px 0;
width: 620px;
}
.main .title {
padding-left: 8px;
border-left: 3px solid #EA6F5A;
line-height: 1;
font-size: 15px;
}
.main .collection-settings {
position: absolute;
top: 2px;
right: 0;
font-size: 13px;
color: #A0A0A0;
}
.main .collection-settings span {
padding-left: 4px;
}
.main .include-collection {
width: 100%;
padding-top: 20px;
display: -webkit-box;
display: -webkit-flex;
display: -ms-flexbox;
display: flex;
-webkit-box-orient: horizontal;
-webkit-box-direction: normal;
-webkit-flex-direction: row;
-ms-flex-direction: row;
flex-direction: row;
-webkit-box-pack: start;
-webkit-justify-content: flex-start;
-ms-flex-pack: start;
justify-content: flex-start;
-webkit-box-align: center;
-webkit-align-items: center;
-ms-flex-align: center;
align-items: center;
-webkit-flex-wrap: wrap;
-ms-flex-wrap: wrap;
flex-wrap: wrap;
}
.main .include-collection .item {
display: inline-block;
margin: 0 12px 12px 0;
min-height: 32px;
background-color: white;
border: 1px solid #DCDCDC;
border-radius: 4px;
vertical-align: top;
overflow: hidden;
}
.main .include-collection .item img {
width: 32px;
height: 32px;
}
.main .include-collection .item .name {
display: inline-block;
padding: 0 10px;
font-size: 14px;
}
.main .include-collection .add-collection-wrap {
margin: 0 12px 12px 0;
}
.main .include-collection .add-collection {
padding: 8px 12px;
font-size: 14px;
border: 1px solid #DCDCDC;
border-radius: 4px;
}
.main .include-collection .add-collection i {
margin-right: 4px;
color: #969696;
}
.main .recommend-note a {
position: relative;
margin: 20px 2px 0 0;
width: 200px;
height: 160px;
display: inline-block;
}
.main .recommend-note a:after {
content: "";
position: absolute;
width: 200px;
height: 160px;
border-radius: 0 0 4px 4px;
-webkit-box-shadow: inset 0px -80px 50px -22px rgba(0, 0, 0, 0.6);
box-shadow: inset 0px -80px 50px -22px rgba(0, 0, 0, 0.6);
top: 0;
left: 0;
z-index: 1;
}
.main .recommend-note .name {
position: absolute;
bottom: 40px;
left: 10px;
right: 10px;
font-size: 17px;
font-weight: bold;
color: #ffffff;
z-index: 2;
}
.main .recommend-note .author {
position: absolute;
bottom: 10px;
left: 10px;
right: 10px;
z-index: 2;
}
.main .recommend-note .avatar {
width: 20px;
height: 20px;
display: inline-block;
}
.main .recommend-note .avatar img {
border-radius: 50%;
}
.main .recommend-note .author-name {
font-size: 12px;
color: #ffffff;
display: inline-block;
vertical-align: -1px;
}
.main .show-more {
margin: 0 12px 12px 0;
font-size: 14px;
color: #A0A0A0;
}
</style></style><head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=Edge">
<meta name="viewport" content="width=device-width, initial-scale=1.0,user-scalable=no">

<!-- Start of Baidu Transcode -->
<meta http-equiv="Cache-Control" content="no-siteapp">
<meta http-equiv="Cache-Control" content="no-transform">
<meta name="applicable-device" content="pc,mobile">
<meta name="MobileOptimized" content="width">
<meta name="HandheldFriendly" content="true">
<meta name="mobile-agent" content="format=html5;url=https://www.jianshu.com/p/f4282df18537">
<!-- End of Baidu Transcode -->

<meta name="description" content="网络 Alamofire:http网络请求事件处理的框架。 Moya:这是一个基于Alamofire的更高层网络请求封装抽象层。 Reachability.swift:用来检查应用当前的网络连接状况。 综合 Perfect:swift的服务器端开发框架（针对于移动后端开发、网站和web应用程序开发）。 RxSwift:函数响应式编程框架，是ReactiveX的swift版本，可以简化异步操作...">

<meta name="360-site-verification" content="604a14b53c6b871206001285921e81d8">
<meta property="wb:webmaster" content="294ec9de89e7fadb">
<meta property="qc:admins" content="104102651453316562112116375">
<meta property="qc:admins" content="11635613706305617">
<meta property="qc:admins" content="1163561616621163056375">
<meta name="google-site-verification" content="cV4-qkUJZR6gmFeajx_UyPe47GW9vY6cnCrYtCHYNh4">
<meta name="google-site-verification" content="HF7lfF8YEGs1qtCE-kPml8Z469e2RHhGajy6JPVy5XI">
<meta http-equiv="mobile-agent" content="format=html5; url=https://www.jianshu.com/p/f4282df18537">

<!-- Apple -->
<meta name="apple-mobile-web-app-title" content="简书">

<!--  Meta for Smart App Banner -->
<meta name="apple-itunes-app" content="app-id=888237539, app-argument=jianshu://notes/22347247">
<!-- End -->

<!--  Meta for Twitter Card -->
<meta content="summary" property="twitter:card">
<meta content="@jianshucom" property="twitter:site">
<meta content="Swift常用第三方库" property="twitter:title">
<meta content="网络 Alamofire:http网络请求事件处理的框架。 Moya:这是一个基于Alamofire的更高层网络请求封装抽象层。 Reachability.swift:用来检..." property="twitter:description">
<meta content="https://www.jianshu.com/p/f4282df18537" property="twitter:url">
<!-- End -->

<!--  Meta for OpenGraph -->
<meta property="fb:app_id" content="865829053512461">
<meta property="og:site_name" content="简书">
<meta property="og:title" content="Swift常用第三方库">
<meta property="og:type" content="article">
<meta property="og:url" content="https://www.jianshu.com/p/f4282df18537">
<meta property="og:description" content="网络 Alamofire:http网络请求事件处理的框架。 Moya:这是一个基于Alamofire的更高层网络请求封装抽象层。 Reachability.swift:用来检查应用当前的网络连接...">
<!-- End -->

<!--  Meta for Facebook Applinks -->
<meta property="al:ios:url" content="jianshu://notes/22347247">
<meta property="al:ios:app_store_id" content="888237539">
<meta property="al:ios:app_name" content="简书">

<meta property="al:android:url" content="jianshu://notes/22347247">
<meta property="al:android:package" content="com.jianshu.haruki">
<meta property="al:android:app_name" content="简书">
<!-- End -->


<title>Swift常用第三方库 - 简书</title>

<meta name="csrf-param" content="authenticity_token">
<meta name="csrf-token" content="YEkcccL6UsUOJFMeBoHhlylcMJzgONbP8oDS4Y7siVLbl91GFHdX7KHf2zVrpfgn8rS7wYC5vP6lZwHjklXNzQ==">

<link rel="stylesheet" media="all" href="//cdn2.jianshu.io/assets/web-d5108cec60c4ed55f041.css">

<link rel="stylesheet" media="all" href="//cdn2.jianshu.io/assets/web/pages/notes/show/entry-f1bfe3a5bcbd20b68049.css">

<link href="//cdn2.jianshu.io/assets/favicons/favicon-e743bfb1821442341c3ab15bdbe804f7ad97676bd07a770ccc9483473aa76f06.ico" rel="shortcut icon" type="image/x-icon">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/57-a6f1f1ee62ace44f6dc2f6a08575abd3c3b163288881c78dd8d75247682a4b27.png" sizes="57x57">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/72-fb9834bcfce738fd7b9c5e31363e79443e09a81a8e931170b58bc815387c1562.png" sizes="72x72">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/76-49d88e539ff2489475d603994988d871219141ecaa0b1a7a9a1914f4fe3182d6.png" sizes="76x76">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/114-24252fe693524ed3a9d0905e49bff3cbd0228f25a320aa09053c2ebb4955de97.png" sizes="114x114">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/120-1bb7371f5e87f93ce780a5f1a05ff1b176828ee0d1d130e768575918a2e05834.png" sizes="120x120">
<link rel="apple-touch-icon-precomposed" href="//cdn2.jianshu.io/assets/apple-touch-icons/152-bf209460fc1c17bfd3e2b84c8e758bc11ca3e570fd411c3bbd84149b97453b99.png" sizes="152x152">

<!-- Start of 访问统计 -->
<script src="https://zz.bdstatic.com/linksubmit/push.js"></script><script src="//hm.baidu.com/hm.js?0c0e9d9b1e7d617b3e6842e85b9fb068"></script><script>
var _hmt = _hmt || [];
(function() {
var hm = document.createElement("script");
hm.src = "//hm.baidu.com/hm.js?0c0e9d9b1e7d617b3e6842e85b9fb068";
var s = document.getElementsByTagName("script")[0];
s.parentNode.insertBefore(hm, s);
})();
</script>

<!-- End of 访问统计 -->
<style type="text/css">@charset "UTF-8";.image-package .image-container{position:relative;z-index:2;background-color:#eee;-webkit-transition:background-color .1s linear;-o-transition:background-color .1s linear;transition:background-color .1s linear;margin:0 auto}body.reader-night-mode .image-package .image-container{background-color:#545454}.image-package .image-container-fill{z-index:1}.image-package .image-container .image-view{position:absolute;top:0;left:0;width:100%;height:100%;overflow:hidden}.image-package .image-container .image-view-error:after{content:"图片获取失败，请点击重试";position:absolute;top:50%;left:50%;width:100%;-webkit-transform:translate(-50%,-50%);-ms-transform:translate(-50%,-50%);transform:translate(-50%,-50%);color:#888;font-size:14px}.image-package .image-container .image-view img.image-loading{opacity:.3}.image-package .image-container .image-view img{-webkit-transition:all .15s linear;-o-transition:all .15s linear;transition:all .15s linear;z-index:2;opacity:1}</style><style type="text/css">fieldset[disabled] .multiselect {
pointer-events: none;
}

.multiselect__spinner {
position: absolute;
right: 1px;
top: 1px;
width: 48px;
height: 35px;
background: #fff;
display: block;
}

.multiselect__spinner:after,
.multiselect__spinner:before {
position: absolute;
content: "";
top: 50%;
left: 50%;
margin: -8px 0 0 -8px;
width: 16px;
height: 16px;
border-radius: 100%;
border-color: #41b883 transparent transparent;
border-style: solid;
border-width: 2px;
box-shadow: 0 0 0 1px transparent;
}

.multiselect__spinner:before {
animation: a 2.4s cubic-bezier(.41,.26,.2,.62);
animation-iteration-count: infinite;
}

.multiselect__spinner:after {
animation: a 2.4s cubic-bezier(.51,.09,.21,.8);
animation-iteration-count: infinite;
}

.multiselect__loading-enter-active,
.multiselect__loading-leave-active {
transition: opacity .4s ease-in-out;
opacity: 1;
}

.multiselect__loading-enter,
.multiselect__loading-leave-active {
opacity: 0;
}

.multiselect,
.multiselect__input,
.multiselect__single {
font-family: inherit;
font-size: 14px;
-ms-touch-action: manipulation;
touch-action: manipulation;
}

.multiselect {
box-sizing: content-box;
display: block;
position: relative;
width: 100%;
min-height: 40px;
text-align: left;
color: #35495e;
}

.multiselect * {
box-sizing: border-box;
}

.multiselect:focus {
outline: none;
}

.multiselect--disabled {
opacity: .6;
}

.multiselect--active {
z-index: 1;
}

.multiselect--active:not(.multiselect--above) .multiselect__current,
.multiselect--active:not(.multiselect--above) .multiselect__input,
.multiselect--active:not(.multiselect--above) .multiselect__tags {
border-bottom-left-radius: 0;
border-bottom-right-radius: 0;
}

.multiselect--active .multiselect__select {
transform: rotate(180deg);
}

.multiselect--above.multiselect--active .multiselect__current,
.multiselect--above.multiselect--active .multiselect__input,
.multiselect--above.multiselect--active .multiselect__tags {
border-top-left-radius: 0;
border-top-right-radius: 0;
}

.multiselect__input,
.multiselect__single {
position: relative;
display: inline-block;
min-height: 20px;
line-height: 20px;
border: none;
border-radius: 5px;
background: #fff;
padding: 0 0 0 5px;
width: 100%;
transition: border .1s ease;
box-sizing: border-box;
margin-bottom: 8px;
vertical-align: top;
}

.multiselect__tag~.multiselect__input,
.multiselect__tag~.multiselect__single {
width: auto;
}

.multiselect__input:hover,
.multiselect__single:hover {
border-color: #cfcfcf;
}

.multiselect__input:focus,
.multiselect__single:focus {
border-color: #a8a8a8;
outline: none;
}

.multiselect__single {
padding-left: 6px;
margin-bottom: 8px;
}

.multiselect__tags-wrap {
display: inline;
}

.multiselect__tags {
min-height: 40px;
display: block;
padding: 8px 40px 0 8px;
border-radius: 5px;
border: 1px solid #e8e8e8;
background: #fff;
}

.multiselect__tag {
position: relative;
display: inline-block;
padding: 4px 26px 4px 10px;
border-radius: 5px;
margin-right: 10px;
color: #fff;
line-height: 1;
background: #41b883;
margin-bottom: 5px;
white-space: nowrap;
overflow: hidden;
max-width: 100%;
text-overflow: ellipsis;
}

.multiselect__tag-icon {
cursor: pointer;
margin-left: 7px;
position: absolute;
right: 0;
top: 0;
bottom: 0;
font-weight: 700;
font-style: normal;
width: 22px;
text-align: center;
line-height: 22px;
transition: all .2s ease;
border-radius: 5px;
}

.multiselect__tag-icon:after {
content: "\D7";
color: #266d4d;
font-size: 14px;
}

.multiselect__tag-icon:focus,
.multiselect__tag-icon:hover {
background: #369a6e;
}

.multiselect__tag-icon:focus:after,
.multiselect__tag-icon:hover:after {
color: #fff;
}

.multiselect__current {
min-height: 40px;
overflow: hidden;
padding: 8px 12px 0;
padding-right: 30px;
white-space: nowrap;
border-radius: 5px;
border: 1px solid #e8e8e8;
}

.multiselect__current,
.multiselect__select {
line-height: 16px;
box-sizing: border-box;
display: block;
margin: 0;
text-decoration: none;
cursor: pointer;
}

.multiselect__select {
position: absolute;
width: 40px;
height: 38px;
right: 1px;
top: 1px;
padding: 4px 8px;
text-align: center;
transition: transform .2s ease;
}

.multiselect__select:before {
position: relative;
right: 0;
top: 65%;
color: #999;
margin-top: 4px;
border-style: solid;
border-width: 5px 5px 0;
border-color: #999 transparent transparent;
content: "";
}

.multiselect__placeholder {
color: #adadad;
display: inline-block;
margin-bottom: 10px;
padding-top: 2px;
}

.multiselect--active .multiselect__placeholder {
display: none;
}

.multiselect__content-wrapper {
position: absolute;
display: block;
background: #fff;
width: 100%;
max-height: 240px;
overflow: auto;
border: 1px solid #e8e8e8;
border-top: none;
border-bottom-left-radius: 5px;
border-bottom-right-radius: 5px;
z-index: 1;
-webkit-overflow-scrolling: touch;
}

.multiselect__content {
list-style: none;
display: inline-block;
padding: 0;
margin: 0;
min-width: 100%;
vertical-align: top;
}

.multiselect--above .multiselect__content-wrapper {
bottom: 100%;
border-bottom-left-radius: 0;
border-bottom-right-radius: 0;
border-top-left-radius: 5px;
border-top-right-radius: 5px;
border-bottom: none;
border-top: 1px solid #e8e8e8;
}

.multiselect__content::webkit-scrollbar {
display: none;
}

.multiselect__element {
display: block;
}

.multiselect__option {
display: block;
padding: 12px;
min-height: 40px;
line-height: 16px;
text-decoration: none;
text-transform: none;
vertical-align: middle;
position: relative;
cursor: pointer;
white-space: nowrap;
}

.multiselect__option:after {
top: 0;
right: 0;
position: absolute;
line-height: 40px;
padding-right: 12px;
padding-left: 20px;
}

.multiselect__option--highlight {
background: #41b883;
outline: none;
color: #fff;
}

.multiselect__option--highlight:after {
content: attr(data-select);
background: #41b883;
color: #fff;
}

.multiselect__option--selected {
background: #f3f3f3;
color: #35495e;
font-weight: 700;
}

.multiselect__option--selected:after {
content: attr(data-selected);
color: silver;
}

.multiselect__option--selected.multiselect__option--highlight {
background: #ff6a6a;
color: #fff;
}

.multiselect__option--selected.multiselect__option--highlight:after {
background: #ff6a6a;
content: attr(data-deselect);
color: #fff;
}

.multiselect--disabled {
background: #ededed;
pointer-events: none;
}

.multiselect--disabled .multiselect__current,
.multiselect--disabled .multiselect__select,
.multiselect__option--disabled {
background: #ededed;
color: #a6a6a6;
}

.multiselect__option--disabled {
cursor: text;
pointer-events: none;
}

.multiselect__option--disabled.multiselect__option--highlight {
background: #dedede!important;
}

.multiselect-enter-active,
.multiselect-leave-active {
transition: all .15s ease;
}

.multiselect-enter,
.multiselect-leave-active {
opacity: 0;
}

.multiselect__strong {
margin-bottom: 8px;
line-height: 20px;
display: inline-block;
vertical-align: top;
}

[dir=rtl] .multiselect {
text-align: right;
}

[dir=rtl] .multiselect__select {
right: auto;
left: 1px;
}

[dir=rtl] .multiselect__tags {
padding: 8px 8px 0 40px;
}

[dir=rtl] .multiselect__content {
text-align: right;
}

[dir=rtl] .multiselect__option:after {
right: auto;
left: 0;
}

[dir=rtl] .multiselect__clear {
right: auto;
left: 12px;
}

[dir=rtl] .multiselect__spinner {
right: auto;
left: 1px;
}

@keyframes a {
0% {
transform: rotate(0);
}

to {
transform: rotate(2turn);
}
}</style><style type="text/css">
#free-reward-panel .reward-users-modal main {
padding: 0;
}
</style><style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.reward-note-modal .v-modal {
width: 620px;
text-align: center;
}
.reward-note-modal .v-modal form {
margin: 0 auto 25px auto;
padding: 0 40px;
}
.reward-note-modal .v-modal .reward-intro {
margin-top: 20px;
margin-bottom: 20px;
font-size: 16px;
}
.reward-note-modal .v-modal .reward-intro .avatar {
cursor: default !important;
width: 36px;
height: 36px;
margin-right: 10px;
display: inline-block;
}
.reward-note-modal .v-modal .reward-intro .intro {
margin-right: 5px;
font-weight: bold;
vertical-align: middle;
}
.reward-note-modal .v-modal .reward-intro i {
color: #EA6F5A;
vertical-align: middle;
}
.reward-note-modal .v-modal .main-inputs {
margin: 25px 0;
}
.reward-note-modal .v-modal .main-inputs .amount-group {
margin: 0 -5px;
}
.reward-note-modal .v-modal .main-inputs .amount-group input {
display: none;
}
.reward-note-modal .v-modal .main-inputs .amount-group input:checked + .option {
color: #EA6F5A;
border-color: #EA6F5A;
}
.reward-note-modal .v-modal .main-inputs .amount-group .custom-amount:checked + .option .custom-text {
opacity: 0;
}
.reward-note-modal .v-modal .main-inputs .amount-group .custom-amount:checked + .option .custom-amount-input {
opacity: 1;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option {
position: relative;
margin: 0 5px 15px;
width: 156px;
height: 56px;
line-height: 54px;
border: 1px solid #E6E6E6;
border-radius: 4px;
font-weight: normal;
color: #999999;
cursor: pointer;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option i {
font-size: 16px;
vertical-align: middle;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .amount {
font-size: 28px;
vertical-align: middle;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .piece {
font-size: 13px;
vertical-align: sub;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input {
position: absolute;
top: 0;
z-index: -1;
width: 100%;
opacity: 0;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input i {
position: absolute;
top: 0;
left: 10px;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input .piece {
position: absolute;
top: 4px;
right: 10px;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input input {
display: block;
margin: 0 auto;
width: 80px;
height: 54px;
line-height: 54px;
border: none;
font-size: 28px;
text-align: center;
background: transparent;
-moz-appearance: textfield;
}
.reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input input::-webkit-outer-spin-button, .reward-note-modal .v-modal .main-inputs .amount-group .option .custom-amount-input input::-webkit-inner-spin-button {
-webkit-appearance: none !important;
}
.reward-note-modal .v-modal .main-inputs .message {
padding: 15px 20px;
margin-bottom: 0;
font-size: 14px;
border: 1px solid #E6E6E6;
color: #333333;
border-radius: 4px;
background-color: rgba(180, 180, 180, 0.1);
}
.reward-note-modal .v-modal .main-inputs .message textarea {
width: 100%;
height: 44px;
padding: 0;
margin: 0;
resize: none;
background: none !important;
border: none !important;
-webkit-box-sizing: border-box;
box-sizing: border-box;
-webkit-box-shadow: none;
box-shadow: none;
}
.reward-note-modal .v-modal .main-inputs .message textarea:focus {
outline: none;
}
.reward-note-modal .v-modal .reward-info .amount {
font-size: 28px;
font-weight: bold;
color: #EA6F5A;
}
.reward-note-modal .v-modal .reward-info .pay-method {
font-size: 14px;
}
.reward-note-modal .v-modal .reward-info .pay-method a {
color: #3194D0;
}
.reward-note-modal .v-modal .choose-pay {
margin: 0 -5px;
}
.reward-note-modal .v-modal .choose-pay input {
display: none;
}
.reward-note-modal .v-modal .choose-pay input:checked + .option {
color: #EA6F5A;
border-color: #EA6F5A;
}
.reward-note-modal .v-modal .choose-pay .option {
margin: 20px 5px 10px;
width: 156px;
height: 56px;
line-height: 54px;
text-align: center;
border: 1px solid #E6E6E6;
border-radius: 4px;
cursor: pointer;
}
.reward-note-modal .v-modal .choose-pay .option img {
height: 30px;
}
.reward-note-modal .v-modal .choose-pay .option img.day.alipay, .reward-note-modal .v-modal .choose-pay .option img.night.alipay {
min-width: 85px;
}
.reward-note-modal .v-modal .choose-pay .option img.day.wechat, .reward-note-modal .v-modal .choose-pay .option img.night.wechat {
min-width: 112px;
}
.reward-note-modal .v-modal .choose-pay .option img.night {
display: none;
}
.reward-note-modal .v-modal .choose-pay .tooltip {
width: 230px;
}
.reward-note-modal .v-modal .modal-footer {
padding: 0 15px 20px;
border: none;
background-color: transparent;
text-align: center;
}
.reward-note-modal .v-modal .modal-footer .btn {
padding: 8px 45px;
font-size: 24px;
}
.reward-note-modal .v-modal .btn-pay {
padding: 8px 25px;
font-size: 16px;
color: #ffffff;
background-color: #F5A623;
}
.weixin-pay, .success-pay {
text-align: center;
}
.weixin-pay .v-modal, .success-pay .v-modal {
width: 350px;
}
.weixin-pay .ic-successed, .success-pay .ic-successed {
font-size: 60px;
color: #3db922;
}
.weixin-pay h2, .weixin-pay h3, .success-pay h2, .success-pay h3 {
margin-bottom: 20px;
color: #333333;
}
.weixin-pay h2, .success-pay h2 {
margin: 0 0 40px 0;
font-size: 24px;
}
.weixin-pay .bind-text, .success-pay .bind-text {
position: relative;
margin-bottom: 30px;
font-size: 14px;
color: #999999;
}
.weixin-pay .bind-text:before, .weixin-pay .bind-text:after, .success-pay .bind-text:before, .success-pay .bind-text:after {
content: "";
border-top: 1px solid #999;
display: block;
position: absolute;
width: 40px;
top: 8px;
}
.weixin-pay .bind-text:before, .success-pay .bind-text:before {
left: 30px;
}
.weixin-pay .bind-text:after, .success-pay .bind-text:after {
right: 30px;
}
.weixin-pay .share-bind, .success-pay .share-bind {
display: block;
margin-bottom: 30px;
}
.weixin-pay .share-bind i, .success-pay .share-bind i {
margin-right: 4px;
font-size: 22px;
vertical-align: middle;
}
.weixin-pay .share-bind.wechat i, .success-pay .share-bind.wechat i {
color: #00BB29;
}
.weixin-pay .share-bind.weibo i, .success-pay .share-bind.weibo i {
color: #E05244;
}
.weixin-pay .wx-qr-code, .success-pay .wx-qr-code {
display: inline-block;
}
.weixin-pay .wx-qr-code img, .success-pay .wx-qr-code img {
margin: 0 auto;
padding: 10px;
width: 200px;
background-color: #ffffff;
}
.weixin-pay .pay-amount, .success-pay .pay-amount {
margin: 20px 0;
color: #787878;
}
.weixin-pay .pay-amount span, .success-pay .pay-amount span {
color: #F5A623;
}
</style><style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.v-modal-wrap {
position: fixed;
left: 0;
top: 0;
right: 0;
bottom: 0;
z-index: 9999;
background-color: transparent;
}
.v-modal-wrap.modal-leave-active {
-webkit-transition: opacity 0.3s;
-o-transition: opacity 0.3s;
transition: opacity 0.3s;
}
.v-modal-wrap.modal-enter-active .v-modal-mask, .v-modal-wrap.modal-leave-active .v-modal-mask {
opacity: 0;
}
.v-modal-wrap.modal-enter-active .v-modal, .v-modal-wrap.modal-leave-active .v-modal {
-webkit-transform: translate(-50%, -70%);
-ms-transform: translate(-50%, -70%);
transform: translate(-50%, -70%);
opacity: 0;
}
.v-modal-wrap .v-modal-mask {
background-color: rgba(255, 255, 255, 0.7);
position: absolute;
left: 0;
right: 0;
top: 0;
bottom: 0;
-webkit-transition: opacity 0.3s;
-o-transition: opacity 0.3s;
transition: opacity 0.3s;
opacity: 1;
}
.v-modal-wrap .v-modal {
position: absolute;
left: 50%;
top: 50%;
-webkit-transform: translate(-50%, -50%);
-ms-transform: translate(-50%, -50%);
transform: translate(-50%, -50%);
border-radius: 6px;
border: 1px solid rgba(0, 0, 0, 0.1);
background-color: #fff;
-webkit-box-shadow: 0 5px 25px rgba(0, 0, 0, 0.1);
box-shadow: 0 5px 25px rgba(0, 0, 0, 0.1);
-webkit-transition: opacity 0.3s, -webkit-transform 0.3s;
transition: opacity 0.3s, -webkit-transform 0.3s;
-o-transition: opacity 0.3s, transform 0.3s;
transition: opacity 0.3s, transform 0.3s;
transition: opacity 0.3s, transform 0.3s, -webkit-transform 0.3s;
opacity: 1;
display: -webkit-box;
display: -webkit-flex;
display: -ms-flexbox;
display: flex;
-webkit-box-orient: vertical;
-webkit-box-direction: normal;
-webkit-flex-direction: column;
-ms-flex-direction: column;
flex-direction: column;
overflow: hidden;
}
.v-modal-wrap .v-modal > header:before, .v-modal-wrap .v-modal > header:after, .v-modal-wrap .v-modal > main:before, .v-modal-wrap .v-modal > main:after, .v-modal-wrap .v-modal > footer:before, .v-modal-wrap .v-modal > footer:after {
content: '';
clear: both;
display: table;
}
.v-modal-wrap .v-modal > header {
padding: 20px;
border-bottom: 1px solid #F0F0F0;
}
.v-modal-wrap .v-modal > header h4 {
margin: 0;
color: #333;
text-align: left;
}
.v-modal-wrap .v-modal .close {
position: absolute;
right: 16px;
top: 20px;
font-size: 26px;
line-height: 20px;
color: rgba(0, 0, 0, 0.8);
}
.v-modal-wrap .v-modal .close:hover {
color: #000000;
}
.v-modal-wrap .v-modal > main {
padding: 20px 20px 20px 20px;
font-size: 15px;
color: #333;
-webkit-box-flex: 1;
-webkit-flex-grow: 1;
-ms-flex-positive: 1;
flex-grow: 1;
overflow-x: hidden;
overflow-y: auto;
}
.v-modal-wrap .v-modal > footer {
padding: 20px;
background-color: #fff;
}
.v-modal-wrap .v-modal > footer button {
padding: 0;
margin: 0;
background-color: transparent;
border: 0;
float: right;
}
.v-modal-wrap .v-modal > footer button:focus {
outline: 0;
}
.v-modal-wrap .v-modal > footer .submit {
padding: 4px 12px;
border: 1px solid;
border-radius: 20px;
}
.v-modal-wrap .v-modal > footer .cancel {
margin-top: 5px;
}
.v-modal-wrap .v-modal > footer .cancel:hover {
color: #333333;
}
.reader-night-mode .v-modal-wrap .v-modal-mask {
background-color: rgba(63, 63, 63, 0.7);
}
.reader-night-mode .v-modal-wrap .v-modal {
background-color: #3f3f3f;
}
.reader-night-mode .v-modal-wrap .v-modal header {
border-color: #2F2F2F;
}
.reader-night-mode .v-modal-wrap .v-modal header h4 {
color: #C8C8C8;
}
.reader-night-mode .v-modal-wrap .v-modal .close {
color: #C8C8C8;
}
.reader-night-mode .v-modal-wrap .v-modal .close:hover {
color: #ffffff;
}
.reader-night-mode .v-modal-wrap .v-modal main {
color: #C8C8C8;
}
.reader-night-mode .v-modal-wrap .v-modal footer {
background-color: #3f3f3f;
}
.reader-night-mode .v-modal-wrap .v-modal footer .cancel:hover {
color: #C8C8C8;
}
</style><style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.like[data-v-6ddd02c6] {
display: inline-block;
}
.like .like-group[data-v-6ddd02c6] {
position: relative;
padding: 13px 0 15px 0;
font-size: 0;
border: 1px solid #EA6F5A;
border-radius: 40px;
}
.like .like-group[data-v-6ddd02c6]:hover {
background-color: rgba(236, 97, 73, 0.05);
}
.like .like-group .btn-like[data-v-6ddd02c6] {
display: inline-block;
font-size: 19px;
}
.like .like-group .btn-like[data-v-6ddd02c6]:before {
content: '';
position: absolute;
left: 12px;
top: 2px;
width: 50px;
height: 50px;
background-image: url(//cdn2.jianshu.io/assets/web/like_animation_steps-62a00a7b52377d3069927cdb8e61fd34.png);
background-position: left;
background-repeat: no-repeat;
background-size: 1000px 50px;
}
.like .like-group .btn-like a[data-v-6ddd02c6] {
position: relative;
padding: 18px 30px 18px 55px;
color: #EA6F5A;
}
.like .like-group .modal-wrap[data-v-6ddd02c6] {
font-size: 18px;
border-left: 1px solid rgba(236, 97, 73, 0.4);
display: inline-block;
margin-left: -15px;
}
.like .like-group .modal-wrap a[data-v-6ddd02c6] {
color: #EA6F5A;
padding: 18px 26px 18px 18px;
}
.like .like-group.like-animation[data-v-6ddd02c6], .like .like-group.active[data-v-6ddd02c6] {
background-color: #EA6F5A;
}
.like .like-group.like-animation .btn-like a[data-v-6ddd02c6], .like .like-group.active .btn-like a[data-v-6ddd02c6] {
color: white;
}
.like .like-group.like-animation .modal-wrap[data-v-6ddd02c6], .like .like-group.active .modal-wrap[data-v-6ddd02c6] {
border-left: 1px solid white;
}
.like .like-group.like-animation .modal-wrap a[data-v-6ddd02c6], .like .like-group.active .modal-wrap a[data-v-6ddd02c6] {
color: white;
}
.like .like-group.like-animation .btn-like[data-v-6ddd02c6]:before {
-webkit-animation: likeBlast-data-v-6ddd02c6 0.6s 1 steps(19);
animation: likeBlast-data-v-6ddd02c6 0.6s 1 steps(19);
background-position: right;
}
@-webkit-keyframes likeBlast {
0% {
background-position: left;
}
100% {
background-position: right;
}
}
@keyframes likeBlast-data-v-6ddd02c6 {
0% {
background-position: left;
}
100% {
background-position: right;
}
}
.like .like-group.active .btn-like[data-v-6ddd02c6]:before {
background-position: right;
}
</style><style type="text/css">
@charset "UTF-8";
/*
* 变量
*/
.main {
position: relative;
margin: 0 auto;
padding: 0 0 30px 0;
width: 620px;
}
.main .title {
padding-left: 8px;
border-left: 3px solid #EA6F5A;
line-height: 1;
font-size: 15px;
}
.main .collection-settings {
position: absolute;
top: 2px;
right: 0;
font-size: 13px;
color: #A0A0A0;
}
.main .collection-settings span {
padding-left: 4px;
}
.main .include-collection {
width: 100%;
padding-top: 20px;
display: -webkit-box;
display: -webkit-flex;
display: -ms-flexbox;
display: flex;
-webkit-box-orient: horizontal;
-webkit-box-direction: normal;
-webkit-flex-direction: row;
-ms-flex-direction: row;
flex-direction: row;
-webkit-box-pack: start;
-webkit-justify-content: flex-start;
-ms-flex-pack: start;
justify-content: flex-start;
-webkit-box-align: center;
-webkit-align-items: center;
-ms-flex-align: center;
align-items: center;
-webkit-flex-wrap: wrap;
-ms-flex-wrap: wrap;
flex-wrap: wrap;
}
.main .include-collection .item {
display: inline-block;
margin: 0 12px 12px 0;
min-height: 32px;
background-color: white;
border: 1px solid #DCDCDC;
border-radius: 4px;
vertical-align: top;
overflow: hidden;
}
.main .include-collection .item img {
width: 32px;
height: 32px;
}
.main .include-collection .item .name {
display: inline-block;
padding: 0 10px;
font-size: 14px;
}
.main .include-collection .add-collection-wrap {
margin: 0 12px 12px 0;
}
.main .include-collection .add-collection {
padding: 8px 12px;
font-size: 14px;
border: 1px solid #DCDCDC;
border-radius: 4px;
}
.main .include-collection .add-collection i {
margin-right: 4px;
color: #969696;
}
.main .recommend-note a {
position: relative;
margin: 20px 2px 0 0;
width: 200px;
height: 160px;
display: inline-block;
}
.main .recommend-note a:after {
content: "";
position: absolute;
width: 200px;
height: 160px;
border-radius: 0 0 4px 4px;
-webkit-box-shadow: inset 0px -80px 50px -22px rgba(0, 0, 0, 0.6);
box-shadow: inset 0px -80px 50px -22px rgba(0, 0, 0, 0.6);
top: 0;
left: 0;
z-index: 1;
}
.main .recommend-note .name {
position: absolute;
bottom: 40px;
left: 10px;
right: 10px;
font-size: 17px;
font-weight: bold;
color: #ffffff;
z-index: 2;
}
.main .recommend-note .author {
position: absolute;
bottom: 10px;
left: 10px;
right: 10px;
z-index: 2;
}
.main .recommend-note .avatar {
width: 20px;
height: 20px;
display: inline-block;
}
.main .recommend-note .avatar img {
border-radius: 50%;
}
.main .recommend-note .author-name {
font-size: 12px;
color: #ffffff;
display: inline-block;
vertical-align: -1px;
}
.main .show-more {
margin: 0 12px 12px 0;
font-size: 14px;
color: #A0A0A0;
}
</style></head></head>
