//
// Created by 27351 on 2022/9/4.
//
#include <yyl/base.h>
#include "demo.h"

namespace light1{

int main()
{
    // 窗口对象
    GLFWwindow *window = createWindows();

    // -----------------------

    // 设置视口
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);

    Shader objShader("08/shader/obj.vert", "08/shader/obj.frag");
    Shader lightShader("08/shader/light.vert", "08/shader/light.frag");

    PlaneGeometry planeGeometry(1.0, 1.0, 1.0, 1.0);
    BoxGeometry boxGeometry(1.0, 1.0, 1.0);
    SphereGeometry sphereGeometry(0.1, 10.0, 10.0);

    // 生成纹理
    GLuint texture1;
    glGenTextures(1, &texture1);
    bindTextureParam(texture1);
    // 加载图片
    // 图像y轴翻转
    stbi_set_flip_vertically_on_load(true);
    loadImage("container.jpg", true);

    GLuint texture2;
    glGenTextures(1, &texture2);
    bindTextureParam(texture2);
    //翻转Y轴 图像
    stbi_set_flip_vertically_on_load(true);
    loadImage("awesomeface.png", false);

    objShader.use();
    objShader.setInt("texture1", 0);
    objShader.setInt("texture2", 1);

    float factor = 0.0;

    // 旋转矩阵
    glm::mat4 ex = glm::eulerAngleX(45.0f);
    glm::mat4 ey = glm::eulerAngleY(45.0f);
    glm::mat4 ez = glm::eulerAngleZ(45.0f);

    glm::mat4 qularXYZ = glm::eulerAngleXYZ(45.0f, 45.0f, 45.0f);

    float fov = 45.0f; // 视锥体的角度
    glm::vec3 view_translate = glm::vec3(0.0, 0.0, -5.0);
    ImVec4 clear_color = ImVec4(0.2, 0.3, 0.3, 1.0);

    // 光照信息

    glm::vec3 lightPosition = glm::vec3(1.0, 1.5, 0.0); // 光照位置
    objShader.setVec3("lightColor", glm::vec3(0.0f, 1.0f, 0.0f));

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        guiViewStart();
        objShader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 model = glm::mat4(1.0f);

        float rotate = glfwGetTime() * 0.2f;

        glm::qua<float> qu = glm::qua<float>(glm::vec3(rotate, rotate, rotate));
        model = glm::mat4_cast(qu);
        objShader.setMat4("pvm", projection * view * model);

        factor = glfwGetTime();
        objShader.setFloat("factor", -factor * 0.3);

        glBindVertexArray(boxGeometry.VAO);
        glDrawElements(GL_TRIANGLES, boxGeometry.indices.size(), GL_UNSIGNED_INT, 0);

        // 绘制灯光物体
        lightShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(lightPosition.x * glm::sin(glfwGetTime()), lightPosition.y, lightPosition.z));
        lightShader.setMat4("pvm", projection * view * model);
        glBindVertexArray(sphereGeometry.VAO);
        glDrawElements(GL_TRIANGLES, sphereGeometry.indices.size(), GL_UNSIGNED_INT, 0);

        guiViewEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    boxGeometry.dispose();
    planeGeometry.dispose();
    sphereGeometry.dispose();
    glfwTerminate();

    return 0;
}

}
