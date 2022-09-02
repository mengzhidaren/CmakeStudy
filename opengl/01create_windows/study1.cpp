//
// Created by yyl on 2022/9/2.
//

#include "stdio.h"
#include "glad/glad.h"
#include "GlFW/glfw3.h"
#include "iostream"
//https://learnopengl-cn.github.io/
//https://github.com/yocover
//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//GLAD是用来管理OpenGL的函数指针的 所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // if(Mac_OS)//如果使用的是Mac OS X系统
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //绑定窗口环境
    glfwMakeContextCurrent(window);
    //当用户改变窗口的大小的时候，窗口会回调这个函数
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
    { glViewport(0, 0, width, height); });

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "failed to init GLAD" << std::endl;
        return -1 ;
    }

    //我们每次循环的开始前检查一次GLFW是否被要求退出
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2, 0.3, 0.6, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        //检查键盘输入、鼠标移动
        processInput(window);
        //交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
        //它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
        glfwSwapBuffers(window);
        // 检查并调用事件，交换缓冲
        glfwPollEvents();
    }
    //释放/删除之前的分配的所有资源
    glfwTerminate();
    return 0;
}