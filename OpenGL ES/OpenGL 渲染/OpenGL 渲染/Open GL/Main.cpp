//
//  Main.cpp
//  Open GL
//
//  Created by yunna on 2020/6/11.
//  Copyright © 2020 yunna. All rights reserved.
//


//GLTool包含了类似于C语言的独立函数
#include "GLTools.h"
//矩阵工具类，可以利用GLMatrixStack 加载单元矩阵/矩阵/矩阵相乘/压栈/出栈/缩放/平移/旋转
#include "GLMatrixStack.h"
//矩阵工具类，表示位置
#include "GLFrame.h"
//用来快速设置正/透视投影，完成坐标从3D->2D
#include "GLFrustum.h"
//三角形批次类，利用它可以传输定点、光照、纹理、颜色、数据到存储着色器
#include "GLBatch.h"
#include "GLGeometryTransform.h"

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

//存储着色器管理工具类
GLShaderManager shaderManager;
//模型视图矩阵
GLMatrixStack modelViewMatrix;
//矩阵投影
GLMatrixStack projectionMatrix;
//设置观察者视图坐标
GLFrame cameraFrame;
//设置图形环绕时，视图坐标
GLFrame objectFrame;
//投影设置
GLFrustum viewFrustum;

//容器类（7种不同的图元对应7种容器对象）
GLBatch  pointBatch;
GLBatch  lineBatch;
GLBatch  lineStripBatch;
GLBatch  lineLoopBatch;
GLBatch  triangleBatch;
GLBatch  triangleStripBatch;
GLBatch  triangleFanBatch;


//几何变换的管道 存储投影、视图矩阵变换
GLGeometryTransform    transformPipeline;


GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };



// 跟踪效果步骤
int nStep = 0;

//设置你需要渲染的图形的相关订单数据，颜色等
/*
 1、 初始化准备
 背景颜⾊色
 存储着⾊器、管理器初始化
 开启深度测试
 设置变换管道中模型视图矩阵/投影矩阵
 设置观察者视图坐标位置
 
 2、定义三⻆形顶点数据
 使用三⻆形批次类,使用点/线/线段/线环的方式绘制图形
 
 
 3、绘制金字塔准备
 定义⾦字塔顶点数据
 使用三⻆形批次类,使⽤GL_TRIANGLES 绘制金字塔
 
 4、4.绘制六角形准备
 循环定义顶点数据
 使⽤三⻆形批次类,使用GL_TRIANGLES_FAN.传输数据
 
 5.绘制三⻆角形环准备
 循环定义顶点数据
 使⽤用三角形批次类,使用GL_TRIANGLE_STRIP.传输数据
 
 
 setupRC 触发条件:
 1.⼿手动main函数触发
 处理理业务:
 1.设置窗⼝口背景颜⾊色
 2.初始化存储着⾊色器器shaderManager
 3.设置图形顶点数据
 4.利利⽤用GLBatch 三⻆角形批次类,将数据传递到着⾊色器器
 
 */
void SetupRC(){
    // 灰色的背景
     glClearColor(0.7f, 0.7f, 0.7f, 1.0f );
     shaderManager.InitializeStockShaders();
     glEnable(GL_DEPTH_TEST);
     //设置变换管线以使用两个矩阵堆栈
     transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
     cameraFrame.MoveForward(-15.0f);
     
     /*
      常见函数：
      void GLBatch::Begin(GLenum primitive,GLuint nVerts,GLuint nTextureUnits = 0);
       参数1：表示使用的图元
       参数2：顶点数
       参数3：纹理坐标（可选）
      
      //负责顶点坐标
      void GLBatch::CopyVertexData3f(GLFloat *vNorms);
      
      //结束，表示已经完成数据复制工作
      void GLBatch::End(void);
      
      
      */
     //定义一些点，三角形形状。
    
     GLfloat vCoast[9] = {
         3,3,0,0,3,0,3,0,0
         
     };
     
     //用点的形式
     pointBatch.Begin(GL_POINTS, 3);
     pointBatch.CopyVertexData3f(vCoast);
     pointBatch.End();
     
     //通过线的形式
     lineBatch.Begin(GL_LINES, 3);
     lineBatch.CopyVertexData3f(vCoast);
     lineBatch.End();
     
     //通过线段的形式
     lineStripBatch.Begin(GL_LINE_STRIP, 3);
     lineStripBatch.CopyVertexData3f(vCoast);
     lineStripBatch.End();
     
     //通过线环的形式
     lineLoopBatch.Begin(GL_LINE_LOOP, 3);
     lineLoopBatch.CopyVertexData3f(vCoast);
     lineLoopBatch.End();
     
     //通过三角形创建金字塔
     GLfloat vPyramid[12][3] = {
         -2.0f, 0.0f, -2.0f,
         2.0f, 0.0f, -2.0f,
         0.0f, 4.0f, 0.0f,
         
         2.0f, 0.0f, -2.0f,
         2.0f, 0.0f, 2.0f,
         0.0f, 4.0f, 0.0f,
         
         2.0f, 0.0f, 2.0f,
         -2.0f, 0.0f, 2.0f,
         0.0f, 4.0f, 0.0f,
         
         -2.0f, 0.0f, 2.0f,
         -2.0f, 0.0f, -2.0f,
         0.0f, 4.0f, 0.0f};
     
     
     //GL_TRIANGLES 每3个顶点定义一个新的三角形
     triangleBatch.Begin(GL_TRIANGLES, 12);
     triangleBatch.CopyVertexData3f(vPyramid);
     triangleBatch.End();
     
     // 三角形扇形--六边形
     GLfloat vPoints[100][3];
     int nVerts = 0;
     //半径
     GLfloat r = 3.0f;
     //原点(x,y,z) = (0,0,0);
     vPoints[nVerts][0] = 0.0f;
     vPoints[nVerts][1] = 0.0f;
     vPoints[nVerts][2] = 0.0f;
     
     //M3D_2PI 就是2Pi 的意思，就一个圆的意思。 绘制圆形
     for(GLfloat angle = 0; angle < M3D_2PI; angle += M3D_2PI / 6.0f) {
         
         //数组下标自增（每自增1次就表示一个顶点）
         nVerts++;
         /*
          弧长=半径*角度,这里的角度是弧度制,不是平时的角度制
          既然知道了cos值,那么角度=arccos,求一个反三角函数就行了
          */
         //x点坐标 cos(angle) * 半径
         vPoints[nVerts][0] = float(cos(angle)) * r;
         //y点坐标 sin(angle) * 半径
         vPoints[nVerts][1] = float(sin(angle)) * r;
         //z点的坐标
         vPoints[nVerts][2] = -0.5f;
     }
     
     // 结束扇形 前面一共绘制7个顶点（包括圆心）
     //添加闭合的终点
     //课程添加演示：屏蔽173-177行代码，并把绘制节点改为7.则三角形扇形是无法闭合的。
     nVerts++;
     vPoints[nVerts][0] = r;
     vPoints[nVerts][1] = 0;
     vPoints[nVerts][2] = 0.0f;
     
     // 加载！
     //GL_TRIANGLE_FAN 以一个圆心为中心呈扇形排列，共用相邻顶点的一组三角形
     triangleFanBatch.Begin(GL_TRIANGLE_FAN, 8);
     triangleFanBatch.CopyVertexData3f(vPoints);
     triangleFanBatch.End();
     
     //三角形条带，一个小环或圆柱段
     //顶点下标
     int iCounter = 0;
     //半径
     GLfloat radius = 3.0f;
     //从0度~360度，以0.3弧度为步长
     for(GLfloat angle = 0.0f; angle <= (2.0f*M3D_PI); angle += 0.3f)
     {
         //或许圆形的顶点的X,Y
         GLfloat x = radius * sin(angle);
         GLfloat y = radius * cos(angle);
         
         //绘制2个三角形（他们的x,y顶点一样，只是z点不一样）
         vPoints[iCounter][0] = x;
         vPoints[iCounter][1] = y;
         vPoints[iCounter][2] = -0.5;
         iCounter++;
         
         vPoints[iCounter][0] = x;
         vPoints[iCounter][1] = y;
         vPoints[iCounter][2] = 0.5;
         iCounter++;
     }
     
     // 关闭循环
     //结束循环，在循环位置生成2个三角形
     vPoints[iCounter][0] = vPoints[0][0];
     vPoints[iCounter][1] = vPoints[0][1];
     vPoints[iCounter][2] = -0.5;
     iCounter++;
     
     vPoints[iCounter][0] = vPoints[1][0];
     vPoints[iCounter][1] = vPoints[1][1];
     vPoints[iCounter][2] = 0.5;
     iCounter++;
     
     // GL_TRIANGLE_STRIP 共用一个条带（strip）上的顶点的一组三角形
     triangleStripBatch.Begin(GL_TRIANGLE_STRIP, iCounter);
     triangleStripBatch.CopyVertexData3f(vPoints);
     triangleStripBatch.End();
     
     
}


void DrawWireFramedBatch(GLBatch* pBatch){
    /*------------画绿色部分----------------*/
    /* GLShaderManager 中的Uniform 值——平面着色器
     参数1：平面着色器
     参数2：运行为几何图形变换指定一个 4 * 4变换矩阵
          --transformPipeline 变换管线（指定了2个矩阵堆栈）
     参数3：颜色值
    */
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vGreen);
    pBatch->Draw();
    
    /*-----------边框部分-------------------*/
    /*
        glEnable(GLenum mode); 用于启用各种功能。功能由参数决定
        参数列表：http://blog.csdn.net/augusdi/article/details/23747081
        注意：glEnable() 不能写在glBegin() 和 glEnd()中间
        GL_POLYGON_OFFSET_LINE  根据函数glPolygonOffset的设置，启用线的深度偏移
        GL_LINE_SMOOTH          执行后，过虑线点的锯齿
        GL_BLEND                启用颜色混合。例如实现半透明效果
        GL_DEPTH_TEST           启用深度测试 根据坐标的远近自动隐藏被遮住的图形（材料
     
     
        glDisable(GLenum mode); 用于关闭指定的功能 功能由参数决定
     
     */
    
    //画黑色边框
    //偏移深度，在同一位置要绘制填充和边线，会产生z冲突，所以要偏移
    glPolygonOffset(-1.0f, -1.0f);
    glEnable(GL_POLYGON_OFFSET_LINE);
    
    // 画反锯齿，让黑边好看些
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //绘制线框几何黑色版 三种模式，实心，边框，点，可以作用在正面，背面，或者两面
    //通过调用glPolygonMode将多边形正面或者背面设为线框模式，实现线框渲染
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //设置线条宽度
    glLineWidth(2.5f);
    
    /* GLShaderManager 中的Uniform 值——平面着色器
     参数1：平面着色器
     参数2：运行为几何图形变换指定一个 4 * 4变换矩阵
         --transformPipeline.GetModelViewProjectionMatrix() 获取的
          GetMatrix函数就可以获得矩阵堆栈顶部的值
     参数3：颜色值（黑色）
     */
    
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);
    pBatch->Draw();

    // 复原原本的设置
    ////通过调用glPolygonMode将多边形正面或者背面设为全部填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
}


//通过glutDisplayFunc(函数名)注册为显示渲染函数.当屏幕发生变化/或者开发者主动渲染会调用此函数,⽤来实现数据->渲染过程
/*
 - 1、渲染工作
 清除缓存区
 将mCamera观察者图形环绕坐标系压栈
 固定管线 渲染点、线、线段、线环
 
 - 2、修改图形属性
 判断金字塔、六边形、三角形环时，添加边框、目的是让图形更加清晰
 
 - 3、绘制完毕则换还原矩阵
 
 - 4、交换缓存区
 */

void RenderScene(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    //压栈
    modelViewMatrix.PushMatrix();
    M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    
    //矩阵乘以矩阵堆栈的顶部矩阵，相乘的结果随后简存储在堆栈的顶部
    modelViewMatrix.MultMatrix(mCamera);

    M3DMatrix44f mObjectFrame;
    //只要使用 GetMatrix 函数就可以获取矩阵堆栈顶部的值，这个函数可以进行2次重载。用来使用GLShaderManager 的使用。或者是获取顶部矩阵的顶点副本数据
    objectFrame.GetMatrix(mObjectFrame);
    
    
    //矩阵乘以矩阵堆栈的顶部矩阵，相乘的结果随后简存储在堆栈的顶部
    modelViewMatrix.MultMatrix(mObjectFrame);
    
    
    /* GLShaderManager 中的Uniform 值——平面着色器
     参数1：平面着色器
     参数2：运行为几何图形变换指定一个 4 * 4变换矩阵
     --transformPipeline.GetModelViewProjectionMatrix() 获取的
     GetMatrix函数就可以获得矩阵堆栈顶部的值
     参数3：颜色值（黑色）
     */
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);
    
    switch(nStep) {
        case 0:
            //设置点的大小
            glPointSize(4.0f);
            pointBatch.Draw();
            glPointSize(1.0f);
            break;
        case 1:
            //设置线的宽度
            glLineWidth(2.0f);
            lineBatch.Draw();
            glLineWidth(1.0f);
            break;
        case 2:
            glLineWidth(2.0f);
            lineStripBatch.Draw();
            glLineWidth(1.0f);
            break;
        case 3:
            glLineWidth(2.0f);
            lineLoopBatch.Draw();
            glLineWidth(1.0f);
            break;
        case 4:
            DrawWireFramedBatch(&triangleBatch);
            break;
        case 5:
            DrawWireFramedBatch(&triangleFanBatch);
            break;
        case 6:
            DrawWireFramedBatch(&triangleStripBatch);
            break;
    }
    
    //还原到以前的模型视图矩阵（单位矩阵）
    modelViewMatrix.PopMatrix();
    
    // 进行缓冲区交换
    glutSwapBuffers();
    
}


 
//自定义函数.通过glutReshaperFunc(函数名)注册为重塑函数.当屏幕⼤小发生变化/或者第一次创建窗⼝时,会调⽤该函数调整窗⼝大小/视⼝大小
// 窗口已更改大小，或刚刚创建。无论哪种情况，我们都需要
// 使用窗口维度设置视口和投影矩阵.
void ChangeSize(int w, int h){
    glViewport(0, 0, w, h);
    //创建投影矩阵、并将它载入投影矩阵堆栈中
    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 500.0f);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    //调用顶部载入单元矩阵
    modelViewMatrix.LoadIdentity();
}






//根据空格次数。切换不同的“窗口名称”
void KeyPressFunc(unsigned char key, int x, int y)
{
    if(key == 32)
    {
        nStep++;
        
        if(nStep > 6)
            nStep = 0;
    }
    
    switch(nStep)
    {
        case 0:
            glutSetWindowTitle("GL_POINTS");
            break;
        case 1:
            glutSetWindowTitle("GL_LINES");
            break;
        case 2:
            glutSetWindowTitle("GL_LINE_STRIP");
            break;
        case 3:
            glutSetWindowTitle("GL_LINE_LOOP");
            break;
        case 4:
            glutSetWindowTitle("GL_TRIANGLES");
            break;
        case 5:
            glutSetWindowTitle("GL_TRIANGLE_STRIP");
            break;
        case 6:
            glutSetWindowTitle("GL_TRIANGLE_FAN");
            break;
    }
    
    glutPostRedisplay();
}




//特殊键位处理（上、下、左、右移动）
void SpecialKeys(int key, int x, int y)
{
    
    if(key == GLUT_KEY_UP)
        //围绕一个指定的X,Y,Z轴旋转。
        objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
    
    if(key == GLUT_KEY_DOWN)
        objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
    
    if(key == GLUT_KEY_LEFT)
        objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
    
    if(key == GLUT_KEY_RIGHT)
        objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);
    
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    //申请一个颜色缓存区、深度缓存区、双缓存区、模板缓存区
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    //设置window 的尺寸
    glutInitWindowSize(800, 600);
    //创建window的名称
    glutCreateWindow("GL_POINTS");
    //注册回调函数（改变尺寸）
    glutReshapeFunc(ChangeSize);
    //点击空格时，调用的函数
    glutKeyboardFunc(KeyPressFunc);
    //特殊键位函数（上下左右）
    glutSpecialFunc(SpecialKeys);
    //显示函数
    glutDisplayFunc(RenderScene);
    
    //判断一下是否能初始化glew库，确保项目能正常使用OpenGL 框架
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    //绘制
    SetupRC();
    
    //runloop运行循环
    glutMainLoop();
    return 0;
}
