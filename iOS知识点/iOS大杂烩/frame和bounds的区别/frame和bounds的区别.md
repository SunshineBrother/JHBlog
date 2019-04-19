 ## frame和bounds的区别


frame: 该view在父view坐标系统中的位置和大小。（参照点是，父亲的坐标系统）

bounds：该view在本地坐标系统中的位置和大小。（参照点是，本地坐标系统，就相当于ViewB自己的坐标系统，以0,0点为起点）。



![image](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/frame和bounds的区别/image.png)


**未修改bounds**

```

UIView *superView = [[UIView alloc]initWithFrame:CGRectMake(100, 100, 200, 200)];
superView.backgroundColor = [UIColor grayColor];
[self.view addSubview:superView];
//    superView.bounds = CGRectMake(30, 30, 200, 200);

NSLog(@"superView frame:%@========bounds:%@",NSStringFromCGRect(superView.frame),NSStringFromCGRect(superView.bounds));




UIView *childView = [[UIView alloc]initWithFrame:CGRectMake(50, 50, 100, 100)];
childView.backgroundColor = [UIColor redColor];
[superView addSubview:childView];
NSLog(@"childView frame:%@========bounds:%@",NSStringFromCGRect(childView.frame),NSStringFromCGRect(childView.bounds));
```

![frame1](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/frame和bounds的区别/frame1.png)


**修改bounds**
```

UIView *superView = [[UIView alloc]initWithFrame:CGRectMake(100, 100, 200, 200)];
superView.backgroundColor = [UIColor grayColor];
[self.view addSubview:superView];
superView.bounds = CGRectMake(30, 30, 200, 200);

NSLog(@"superView frame:%@========bounds:%@",NSStringFromCGRect(superView.frame),NSStringFromCGRect(superView.bounds));




UIView *childView = [[UIView alloc]initWithFrame:CGRectMake(50, 50, 100, 100)];
childView.backgroundColor = [UIColor redColor];
[superView addSubview:childView];
NSLog(@"childView frame:%@========bounds:%@",NSStringFromCGRect(childView.frame),NSStringFromCGRect(childView.bounds));
```
 

![frame2](https://github.com/SunshineBrother/JHBlog/blob/master/iOS知识点/iOS大杂烩/frame和bounds的区别/frame2.png)



**总结**

- frame是改变自己相对于父视图的位置，对子视图没有影响
- bounds
    - 修改origin改变了子视图的origin值
    - 修改size，改变自己大小

