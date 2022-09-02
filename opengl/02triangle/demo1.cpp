//
// Created by yyl on 2022/9/2.
//
#include "demo.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
namespace demo1Exe {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

//三角形的三个点
// x  y  z
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // 左下角
            0.5f, -0.5f, 0.0f,    // 右下角
            0.0f, 0.5f, 0.0f    // 最上角
    };
// 顶点着色器
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "   gl_PointSize = 20.0;\n"
                                     "}\0";

    const char *fragmentSource = "#version 330 core\n"
                                 "out vec4 FragColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                 "}\n";

//检查 着色器的编译 是否加载成功
    void checkShader(unsigned int vertexShader) {
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        } else {
            std::cout << "shader load OK" << std::endl;
        }
    }

//检查 链接着色器程序 是否加载成功
    void checkProgram(unsigned int shaderProgram) {
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        } else {
            std::cout << "shaderProgram load OK" << std::endl;
        }
    }

//GLAD是用来管理OpenGL的函数指针的 所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    int main() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // if(Mac_OS)//如果使用的是Mac OS X系统
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL2", NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        //绑定窗口环境
        glfwMakeContextCurrent(window);
        //在调用任何OpenGL的函数之前我们需要初始化GLAD
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "failed to init GLAD" << std::endl;
            return -1;
        }
        // 设置视口
        glViewport(0, 0, 800, 600);
        glEnable(GL_PROGRAM_POINT_SIZE);
        //当用户改变窗口的大小的时候，窗口会回调这个函数
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });

        //第一步 ->顶点输入



        //创建缓冲区
        unsigned int VBO;
        int bufferID = 1;
        glGenBuffers(bufferID, &VBO);
        //顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
        //把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
        glBindBuffer(GL_ARRAY_BUFFER, VBO);


        //专门用来把用户定义的数据复制到当前绑定缓冲的函数->把之前定义的顶点数据复制到缓冲的内存中
        //顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上
        //GL_STATIC_DRAW ：数据不会或几乎不会改变
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        //VAO的使用：
        //1. 创建VAO对像
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        //顶点数组对象(Vertex Array Object, VAO)可以像顶点缓冲对象那样被绑定
        // 如果我们绑定VAO失败，OpenGL会拒绝绘制任何东西
        //2.绑定VAO对象后面的顶点属性，之后的调用都会储存在这个VAO中
        glBindVertexArray(VAO);

        // 设置顶点属性指针  这样VAO就记录下来了
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);



        //第二步 ->顶点着色器 片段着色器
        unsigned int vertexShaderId, framentShaderId;
        //顶点着色器(Vertex Shader)是几个可编程的着色器中的一个
        //源码附加到着色器对象上，然后编译它
        vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShaderId);
        checkShader(vertexShaderId);
        // 片段着色器   片段着色器所做的是计算像素最后的颜色输出
        framentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(framentShaderId, 1, &fragmentSource, NULL);
        glCompileShader(framentShaderId);
        checkShader(framentShaderId);

        //着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接完成的版本
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShaderId);
        glAttachShader(shaderProgram, framentShaderId);
        //把着色器链接(Link)为一个着色器程序对象
        glLinkProgram(shaderProgram);
        checkProgram(shaderProgram);
        //UseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)
        glUseProgram(shaderProgram);
        // 着色器对象链接到程序对象以后就不再需要它们,记得删除着色器对象
        glDeleteShader(vertexShaderId);
        glDeleteShader(framentShaderId);

        //我们每次循环的开始前检查一次GLFW是否被要求退出
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.2, 0.3, 0.6, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            //当我们渲染一个物体时要使用着色器程序
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            //填充三角形
            // glDrawArrays(GL_TRIANGLES, 0, 3);
            //三个点
            glDrawArrays(GL_POINTS, 0, 3);
            //三个线
            glDrawArrays(GL_LINE_LOOP, 0, 3);

            glBindVertexArray(0);
            //检查键盘输入、鼠标移动
            processInput(window);
            //交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
            //它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
            glfwSwapBuffers(window);
            // 检查并调用事件，交换缓冲
            glfwPollEvents();
        }
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
        //释放/删除之前的分配的所有资源
        glfwTerminate();
        return 0;
    }

}