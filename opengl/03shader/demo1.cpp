//
// Created by yyl on 2022/9/2.
//
//
// Created by yyl on 2022/9/2.
//
#include "demo.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

namespace shaper1 {


    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

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

    GLFWwindow *createWindows() {
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
            return nullptr;
        }
        //绑定窗口环境
        glfwMakeContextCurrent(window);
        //在调用任何OpenGL的函数之前我们需要初始化GLAD
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "failed to init GLAD" << std::endl;
            return nullptr;
        }
        // 设置视口
        glViewport(0, 0, 800, 600);
        //当用户改变窗口的大小的时候，窗口会回调这个函数
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });
        return window;
    }

//四角形的四个点
// x  y  z
    float vertices1[] = {
            -0.5f, 0.5f, 0.0f,     // 上角
            -0.75f, -0.5f, 0.0f, // 右角
            -0.25f, -0.5f, 0.0f, // 左角
    };                         //四角形的四个点
// x  y  z
    float vertices2[] = {
            0.5f, 0.5f, 0.0f,    // 上角
            0.75f, -0.5f, 0.0f, // 右角
            0.25f, -0.5f, 0.0f, // 左角
    };
    const char *fragmentSource1 = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "void main()\n"
                                  "{\n"

                                  "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                  "}\n";
    const char *fragmentSource2 = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "uniform vec4 ourColor;\n"
                                  "void main()\n"
                                  "{\n"
                                  "    FragColor = ourColor;\n"
                                  "}\n";
// 顶点着色器
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "out vec4 mColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "   mColor = vec4(1.0f, 0.8f, 0.1f, 1.0f); "
                                     "   gl_PointSize = 20.0;\n"
                                     "}\0";

    unsigned int *createShaderProgram() {

        //第二步 ->顶点着色器 片段着色器
        //顶点着色器(Vertex Shader)是几个可编程的着色器中的一个
        //源码附加到着色器对象上，然后编译它
        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        unsigned int framentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
        unsigned int framentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
        //加载和编译
        glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShaderId);
        checkShader(vertexShaderId);
        //加载和编译
        glShaderSource(framentShader1, 1, &fragmentSource1, NULL);
        glCompileShader(framentShader1);
        checkShader(framentShader1);
        //加载和编译
        glShaderSource(framentShader2, 1, &fragmentSource2, NULL);
        glCompileShader(framentShader2);
        checkShader(framentShader2);

        unsigned int shaderProgram1 = glCreateProgram();
        glAttachShader(shaderProgram1, vertexShaderId);
        glAttachShader(shaderProgram1, framentShader1);
        //把着色器链接(Link)为一个着色器程序对象
        glLinkProgram(shaderProgram1);
        checkProgram(shaderProgram1);

        unsigned int shaderProgram2 = glCreateProgram();
        glAttachShader(shaderProgram2, vertexShaderId);
        glAttachShader(shaderProgram2, framentShader2);
        //把着色器链接(Link)为一个着色器程序对象
        glLinkProgram(shaderProgram2);
        checkProgram(shaderProgram2);

        // 着色器对象链接到程序对象以后就不再需要它们,记得删除着色器对象
        glDeleteShader(vertexShaderId);
        glDeleteShader(framentShader1);
        glDeleteShader(framentShader2);
        unsigned int programList[2] = {shaderProgram1, shaderProgram2};

        return programList;
    }

//GLAD是用来管理OpenGL的函数指针的 所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    int main() {
        GLFWwindow *window = createWindows();
        if (window == NULL) {
            return -1;
        }
        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

        glEnable(GL_PROGRAM_POINT_SIZE);
        //着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接完成的版本
        // unsigned int *shaderProgram = createShaderProgram();

        //第二步 ->顶点着色器 片段着色器
        //顶点着色器(Vertex Shader)是几个可编程的着色器中的一个
        //源码附加到着色器对象上，然后编译它
        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        unsigned int framentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
        unsigned int framentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
        //加载和编译
        glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShaderId);
        checkShader(vertexShaderId);
        //加载和编译
        glShaderSource(framentShader1, 1, &fragmentSource1, NULL);
        glCompileShader(framentShader1);
        checkShader(framentShader1);


        unsigned int shaderProgram1 = glCreateProgram();
        glAttachShader(shaderProgram1, vertexShaderId);
        glAttachShader(shaderProgram1, framentShader1);
        //把着色器链接(Link)为一个着色器程序对象
        glLinkProgram(shaderProgram1);
        checkProgram(shaderProgram1);


        //加载和编译
        glShaderSource(framentShader2, 1, &fragmentSource2, NULL);
        glCompileShader(framentShader2);
        checkShader(framentShader2);
        unsigned int shaderProgram2 = glCreateProgram();
        glAttachShader(shaderProgram2, vertexShaderId);
        glAttachShader(shaderProgram2, framentShader2);
        //把着色器链接(Link)为一个着色器程序对象
        glLinkProgram(shaderProgram2);
        checkProgram(shaderProgram2);

        // 着色器对象链接到程序对象以后就不再需要它们,记得删除着色器对象
        glDeleteShader(vertexShaderId);
        glDeleteShader(framentShader1);
        glDeleteShader(framentShader2);

        // unsigned int *VAO = create1VAO();
        // unsigned int *VBO = createVBO();
        unsigned int VAO[2];
        glGenVertexArrays(2, VAO);
        unsigned int VBO[2];
        glGenBuffers(2, VBO);
        //2.绑定VAO对象后面的顶点属性，之后的缓存对像的调用都会储存在这个VAO中
        glBindVertexArray(VAO[0]);
        //绑定VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        //填充VBO数据
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
        //设置顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        //启用顶点属性指针
        glEnableVertexAttribArray(0);

        glBindVertexArray(VAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) (0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        //线框绘制模式
        // glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        // glUseProgram(shaderProgram2);


        int colorLocation = glGetUniformLocation(shaderProgram2, "ourColor");

        //第二步优化顶重复的点坐标 把需要绘制的坐标给一个索引
        //unsigned int EBO = createEBO();

        //我们每次循环的开始前检查一次GLFW是否被要求退出
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.2, 0.3, 0.6, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);

            //当我们渲染一个物体时要使用着色器程序
            glUseProgram(shaderProgram1);
            glBindVertexArray(VAO[0]);
            glDrawArrays(GL_POINTS, 0, 3);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glUseProgram(shaderProgram2);

            float time = glfwGetTime();
            float greenValue = (sin(time) / 2.0f) + 0.5f;
            glUniform4f(colorLocation, 0.3f, greenValue, 0.2f, 1.0f);

            glBindVertexArray(VAO[1]);
            glDrawArrays(GL_POINTS, 0, 3);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            //解绑VAO
            glBindVertexArray(0);
            //检查键盘输入、鼠标移动
            processInput(window);
            //交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲）
            //它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
            glfwSwapBuffers(window);
            // 检查并调用事件，交换缓冲
            glfwPollEvents();
        }
        glDeleteVertexArrays(2, VAO);
        glDeleteBuffers(2, VBO);
        glDeleteProgram(shaderProgram1);
        glDeleteProgram(shaderProgram2);
        //释放/删除之前的分配的所有资源
        glfwTerminate();
        return 0;
    }
}