//
// Created by 27351 on 2022/9/4.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define STB_IMAGE_IMPLEMENTATION
#include <yyl/stb_image.h>

#include <yyl/shader.h>
#include <iostream>
#include "demo.h"
namespace matrix2{


using namespace std;
using namespace glm;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float offsetV = 0.2f;
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        offsetV += 0.01f;
    }
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        offsetV -= 0.01f;
    }
}

GLFWwindow *createWindows()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // if(Mac_OS)//如果使用的是Mac OS X系统
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL2", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    //绑定窗口环境
    glfwMakeContextCurrent(window);
    //在调用任何OpenGL的函数之前我们需要初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to init GLAD" << std::endl;
        return nullptr;
    }
    // 设置视口
    glViewport(0, 0, 800, 600);
    //当用户改变窗口的大小的时候，窗口会回调这个函数
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
    { glViewport(0, 0, width, height); });
    return window;
}

//1. 顶点数组对象(Vertex Array Object, VAO)
unsigned int create1VAO()
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    return VAO;
}
//1. 顶点缓冲对象(Vertex Buffer Objects, VBO)
unsigned int createVBO()
{
    float vertices[] = {
            // 位置X   Y   Z  // 颜色 R G  B    //纹理坐标 S T
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f,   // 右上
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,  // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f   // 左上
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //位置属性指针XYZ   对应vertex.vert中的变量 layout(location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    //颜色属性指针RGB   对应vertex.vert中的变量 layout(location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //纹理属性指针ST    对应vertex.vert中的变量 layout(location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    return VBO;
}
//2. 索引缓冲对象(Element Buffer Object，EBO，也叫Index Buffer Object，IBO)
//面试：主要解决顶点坐标重复，优化顶点坐标
unsigned int createEBO()
{
    unsigned int indices[] = {
            // 注意索引从0开始!
            0, 1, 2, // 第一个三角形
            0, 2, 3  // 第二个三角形
    };
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    //5.复制我们的索引数组到一个索引缓冲中，供OpenGL使用
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //把索引数据复制到缓冲的内存中
    //把[indices]数据 复制到缓冲的内存 给<缓冲buffer>然后上面的<缓冲buffer>EBO就有值了
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    return EBO;
}
//"static/container.jpg"
void loadImage(const std::string &fileName, bool isJpg)
{
    //加载图片
    int width, height, nrChannels;
    auto *data = stbi_load(fileUtils::staticPath(fileName).c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        //填充纹理
        glTexImage2D(GL_TEXTURE_2D, 0, isJpg ? GL_RGB : GL_RGBA, width, height, 0, isJpg ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
        //自动生成所有需要的多级渐远纹理   多级渐远纹理是缩小时图像采样的方式
        //生成了纹理和相应的多级渐远纹理后，需要释放图像的内存
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
// GL_REPEAT	对纹理的默认行为。重复纹理图像。
// GL_MIRRORED_REPEAT	和GL_REPEAT一样，但每次重复图片是镜像放置的。
// GL_CLAMP_TO_EDGE	纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
// GL_CLAMP_TO_BORDER	超出的坐标为用户指定的边缘颜色。 需要配置颜色glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
void createTextureView(unsigned int textureV)
{
    glBindTexture(GL_TEXTURE_2D, textureV);
    //为纹理设置环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //为纹理设置过滤方式      多级渐远纹理只能用于缩小
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//GLAD是用来管理OpenGL的函数指针的 所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
int main()
{
    GLFWwindow *window = createWindows();
    if (window == NULL)
    {
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_PROGRAM_POINT_SIZE);
    Shader outShader("05\\shader2\\vertex.vert", "05\\shader2\\fragment.frag");

    unsigned int VAO = create1VAO();
    unsigned int VBO = createVBO();
    createEBO();

    //生成纹理 绑定纹理
    unsigned int textureV;
    glGenTextures(1, &textureV);
    createTextureView(textureV);
    loadImage("container.jpg", true);

    unsigned int textureV2;
    glGenTextures(1, &textureV2);
    createTextureView(textureV2);
    //翻转Y轴 图像
    stbi_set_flip_vertically_on_load(true);
    loadImage("awesomeface.png", false);
    outShader.use();
    // outShader.setInt("texture1",0);
    outShader.setInt("texture2", 1);
    outShader.setFloat("offsetV", 0.2);

    // vec4 position = vec4(1.0, 1.0, 1.0, 1.0);
    // //初始化一个单位矩阵
    // mat4 trans = mat4(1.0);
    // //向右平移1个单位
    // trans = translate(trans, vec3(0.5f, 0.0f, 0.0f));
    // position = trans * position;
    // //缩放
    // trans = scale(trans, vec3(0.5, 0.5f, 0.5f));
    // position = trans * position;
    // //旋转  z轴45度
    // trans = rotate(trans, float(radians(45.0)), vec3(0.0, 0.0f, 1.0f));
    // position = trans * position;
    // cout << "-" << position.x << "-" << position.y << "-" << position.z << "-" << endl;

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.2, 0.3, 0.6, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureV);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureV2);
        outShader.use();
        outShader.setFloat("offsetV", offsetV);
        // trans = mat4(1.0);
        mat4 model = mat4(1.0);
        mat4 view = mat4(1.0);
        mat4 projection = mat4(1.0);
        //创建一个模型矩阵。这个模型矩阵包含了位移、缩放与旋转操作,它们会被应用到所有物体的顶点上
        //下面是X轴转-55.0度
        model = rotate(model, radians(-55.0f), vec3(1.0, 0.0, 0.0));
        //将矩阵向我们要进行移动场景的反方向移动
        //Z轴向后 -3.0
        view = translate(view, vec3(0.0f, 0.0f, -3.0f));
        //定义一个投影矩阵。我们希望在场景中使用透视投影
        //45度角观察  距离0.1w-100.0w 的  四个轴xyzw中的W
        projection = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // outShader.setMat4("model", model);
        // outShader.setMat4("view", view);
        // outShader.setMat4("projection", projection);
        mat4 pvm = projection * view * model;
        outShader.setMat4("pvm", pvm);
        glBindVertexArray(VAO);
        //EBO填充
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //重新赋值刷新状态
        // trans = mat4(1.0);
        glBindVertexArray(0);
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
}