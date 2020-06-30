//
//  Main.cpp
//  Open GL
//
//  Created by yunna on 2020/6/11.
//  Copyright © 2020 yunna. All rights reserved.
//

#include <iostream>
#include <GLUT/GlUT.h>
#include "math3d.h"

void draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    glClear(GL_COLOR_BUFFER_BIT);

    //设置颜色
    glColor3f(1.0f, 0.0f, 0.0f);
    
    //开始渲染
    glBegin(GL_POLYGON);
      
    const int n = 55;//当n为3时为三角形；n为4时是四边形，n为5时为五边形。。。。。
    const GLfloat R = 0.5f;//圆的半径
    const GLfloat pi = 3.1415926f;
    for (int i = 0; i < n; i++){
        glVertex2f(R*cos(2 * pi / n*i), R*sin(2 * pi / n*i));
    }
    //结束渲染
    glEnd();
    
    //强制刷新缓存区，保证绘制命令得以执行
    glFlush();
    
}
 
int main(int argc,char *argv[]){
    
    //初始化GLUT库,这个函数只是传说命令参数并且初始化glut库
    glutInit(&argc, argv);
     
    //2.创建一个窗口并制定窗口名
    glutCreateWindow("CC_Window");
    
    //3.注册一个绘图函数，操作系统在必要时刻就会对窗体进行重绘制操作
    //它设置了一个显示回调（diplay callback），即GLUT在每次更新窗口内容的时候回自动调用该例程
    glutDisplayFunc(draw);
    
    //这是一个无限执行的循环，它会负责一直处理窗口和操作系统的用户输入等操作。（注意：不会执行在glutMainLoop()之后的所有命令。）
    glutMainLoop();
    

    return  0;
}














