//颜色组合
#include "GLTools.h"
#include "GLShaderManager.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLBatch    squareBatch;
GLBatch greenBatch;
GLBatch redBatch;
GLBatch blueBatch;
GLBatch blackBatch;

GLShaderManager    shaderManager;


GLfloat blockSize = 0.2f;
GLfloat vVerts[] = { -blockSize, -blockSize, 0.0f,
    blockSize, -blockSize, 0.0f,
    blockSize,  blockSize, 0.0f,
    -blockSize,  blockSize, 0.0f};


void SetupRC()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
    shaderManager.InitializeStockShaders();

    //绘制1个移动矩形
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
    
    //绘制4个固定矩形
    GLfloat vBlock[] = {
        0.25f, 0.25f, 0.0f,
        0.75f, 0.25f, 0.0f,
        0.75f, 0.75f, 0.0f,
        0.25f, 0.75f, 0.0f};
    
    greenBatch.Begin(GL_TRIANGLE_FAN, 4);
    greenBatch.CopyVertexData3f(vBlock);
    greenBatch.End();
    
    
    GLfloat vBlock2[] = {
        -0.75f, 0.25f, 0.0f,
        -0.25f, 0.25f, 0.0f,
        -0.25f, 0.75f, 0.0f,
        -0.75f, 0.75f, 0.0f};
    
    redBatch.Begin(GL_TRIANGLE_FAN, 4);
    redBatch.CopyVertexData3f(vBlock2);
    redBatch.End();
    
    
    GLfloat vBlock3[] = {
        -0.75f, -0.75f, 0.0f,
        -0.25f, -0.75f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        -0.75f, -0.25f, 0.0f};
    
    blueBatch.Begin(GL_TRIANGLE_FAN, 4);
    blueBatch.CopyVertexData3f(vBlock3);
    blueBatch.End();
    
    
    GLfloat vBlock4[] = {
        0.25f, -0.75f, 0.0f,
        0.75f, -0.75f, 0.0f,
        0.75f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f};
    
    blackBatch.Begin(GL_TRIANGLE_FAN, 4);
    blackBatch.CopyVertexData3f(vBlock4);
    blackBatch.End();
}

//上下左右键位控制移动
void SpecialKeys(int key, int x, int y)
{
    GLfloat stepSize = 0.025f;
    
    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[7];
    
    if(key == GLUT_KEY_UP)
        blockY += stepSize;
    
    if(key == GLUT_KEY_DOWN)
        blockY -= stepSize;
    
    if(key == GLUT_KEY_LEFT)
        blockX -= stepSize;
    
    if(key == GLUT_KEY_RIGHT)
        blockX += stepSize;
    
    
    if(blockX < -1.0f) blockX = -1.0f;
    if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2;;
    if(blockY < -1.0f + blockSize * 2)  blockY = -1.0f + blockSize * 2;
    if(blockY > 1.0f) blockY = 1.0f;
    
    
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize*2;
    
    vVerts[3] = blockX + blockSize*2;
    vVerts[4] = blockY - blockSize*2;
    
    vVerts[6] = blockX + blockSize*2;
    vVerts[7] = blockY;
    
    vVerts[9] = blockX;
    vVerts[10] = blockY;
    
    squareBatch.CopyVertexData3f(vVerts);
    
    glutPostRedisplay();
}


//召唤场景
void RenderScene(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    //定义4种颜色
    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 0.5f };
    GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat vBlue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    
    //召唤场景的时候，将4个固定矩形绘制好
    //使用 单位着色器
    //参数1：简单的使用默认笛卡尔坐标系（-1，1），所有片段都应用一种颜色。GLT_SHADER_IDENTITY
    //参数2：着色器颜色
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
    greenBatch.Draw();
    
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    redBatch.Draw();
    
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vBlue);
    blueBatch.Draw();
    

    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vBlack);
    blackBatch.Draw();
    
    //组合核心代码
    //1.开启混合
    glEnable(GL_BLEND);
    //2.开启组合函数 计算混合颜色因子
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //3.使用着色器管理器
    //*使用 单位着色器
    //参数1：简单的使用默认笛卡尔坐标系（-1，1），所有片段都应用一种颜色。GLT_SHADER_IDENTITY
    //参数2：着色器颜色
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    //4.容器类开始绘制
    squareBatch.Draw();
    //5.关闭混合功能
    glDisable(GL_BLEND);
    
    //同步绘制命令
    glutSwapBuffers();
}


void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
}

int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("移动矩形，观察颜色");
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    
    SetupRC();
    
    glutMainLoop();
    return 0;
}
