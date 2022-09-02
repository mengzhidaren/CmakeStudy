//
// Created by yyl on 2022/9/2.
//
#include "demo.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace shaper2 {


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

//1. 顶点数组对象(Vertex Array Object, VAO)
    unsigned int create1VAO() {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        return VAO;
    }

//1. 顶点缓冲对象(Vertex Buffer Objects, VBO)
    unsigned int createVBO() {
        float vertices[] = {
                // 位置X Y Z             // 颜色 R G B
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // 右下
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下
                0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
        };
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //位置属性
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        //颜色属性
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        return VBO;
    }

    unsigned int createShaderProgram() {
        // 顶点着色器
        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "layout (location = 1) in vec3 aColor;\n"
                                         "out vec3 outColor;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos, 1.0);\n"
                                         "   outColor=aColor;\n"
                                         "   gl_PointSize = 20.0;\n"
                                         "}\n";
        //第二步 ->顶点着色器 片段着色器
        //顶点着色器(Vertex Shader)是几个可编程的着色器中的一个
        //源码附加到着色器对象上，然后编译它
        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShaderId);
        checkShader(vertexShaderId);
        // 片段着色器   片段着色器所做的是计算像素最后的颜色输出
        unsigned int framentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        const char *fragmentSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "in vec3 outColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    FragColor = vec4(outColor, 1.0f);\n"
                                     "}\n";
        glShaderSource(framentShaderId, 1, &fragmentSource, NULL);
        glCompileShader(framentShaderId);
        checkShader(framentShaderId);
        unsigned int shaderProgram = glCreateProgram();
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
        return shaderProgram;
    }

//GLAD是用来管理OpenGL的函数指针的 所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    int main() {
        GLFWwindow *window = createWindows();
        if (window == NULL) {
            return -1;
        }
        glEnable(GL_PROGRAM_POINT_SIZE);
        unsigned int VAO = create1VAO();
        unsigned int VBO = createVBO();
        // unsigned int EBO = createEBO();

        unsigned int shaderProgram = createShaderProgram();


        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.2, 0.3, 0.6, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            //填充三角形
            glDrawArrays(GL_TRIANGLES, 0, 3);
            //三个点
            // glDrawArrays(GL_POINTS, 0, 3);
            //三个线
            // glDrawArrays(GL_LINE_LOOP, 0, 3);

            //EBO填充
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            //解绑VAO
            glBindVertexArray(0);
            processInput(window);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
        glfwTerminate();
        return 0;
    }


}