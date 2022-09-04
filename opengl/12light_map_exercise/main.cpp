#include <yyl/base.h>

int main(int argc, char *argv[])
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

    Shader lightShader("12/shader/light.vert", "12/shader/light.frag");
    // Shader boxShader("src/13_light_material/shader/box.vert", "src/13_light_material/shader/box.frag");
    Shader boxShader("12/shader/box.vert", "12/shader/box.frag");
    PlaneGeometry planeGeometry(1.0, 1.0, 1.0, 1.0);
    BoxGeometry boxGeometry(1.0, 1.0, 1.0);
    SphereGeometry lightGeometry(0.1, 10.0, 10.0);

    // 生成纹理
    GLuint diffuseMap=loadTexture("container2.png");
    GLuint specularMap=loadTexture("container2_specular.png");
    GLuint specularColorMap=loadTexture("texture/lighting_maps_specular_color.png");
    GLuint emissionMap=loadTexture("texture/matrix.jpg");
    // GLuint emissionMap=loadTexture("static/texture/marble.jpg");

    boxShader.use();
    //
    boxShader.setInt("material.diffuse",0);
    boxShader.setInt("material.specular",1);
    boxShader.setInt("material.specularColor",2);
    boxShader.setInt("material.emission",3);

    // 光照信息和位置
    glm::vec3 lightPosition = glm::vec3(1.0, 1.5, 0.0);
    boxShader.setVec3("lightColor",glm::vec3(1.0,1.0,1.0));
    // boxShader.setFloat("ambientStrength",0.9);
// 传递材质属性
    // boxShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    boxShader.setFloat("material.shininess", 64.0f);

    // 设置光照属性
    boxShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    boxShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f); // 将光照调暗了一些以搭配场景
    boxShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);


    // 旋转矩阵
    glm::mat4 ex = glm::eulerAngleX(45.0f);
    glm::mat4 ey = glm::eulerAngleY(45.0f);
    glm::mat4 ez = glm::eulerAngleZ(45.0f);
    glm::mat4 qularXYZ = glm::eulerAngleXYZ(45.0f, 45.0f, 45.0f);
    glm::vec3 view_translate = glm::vec3(0.0, 0.0, -5.0);
    ImVec4 clear_color = ImVec4(0.2, 0.3, 0.3, 1.0);

    float factor = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        guiViewStart();

        //获取摄像机视角
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

        //自动旋转物体
        glm::mat4 model = glm::mat4(1.0f);
        float rotate = glfwGetTime() * 0.2f;
        glm::qua<float> qu = glm::qua<float>(glm::vec3(rotate, rotate, rotate));
        model = glm::mat4_cast(qu);

        //移动灯光
        glm::vec3 lightPos = glm::vec3(lightPosition.x * glm::sin(glfwGetTime()), lightPosition.y, lightPosition.z);
        //激活shader
        boxShader.use();
        factor=glfwGetTime();
        boxShader.setFloat("factor",-factor*0.3);
        //修改光源颜色
        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);   // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

        boxShader.setVec3("light.ambient", ambientColor);
        boxShader.setVec3("light.diffuse", diffuseColor);



        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, specularColorMap);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, emissionMap);

        float radius=10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;


        boxShader.setMat4("view", view);
        boxShader.setMat4("projection", projection);
        boxShader.setMat4("model", model);
        boxShader.setVec3("lightPos", lightPos);
        boxShader.setVec3("viewPos", camera.Position);


        glBindVertexArray(boxGeometry.VAO);
        glDrawElements(GL_TRIANGLES, boxGeometry.indices.size(), GL_UNSIGNED_INT, 0);

        // 绘制灯光物体
        lightShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        lightShader.setMat4("pvm", projection * view * model);
        glBindVertexArray(lightGeometry.VAO);
        glDrawElements(GL_TRIANGLES, lightGeometry.indices.size(), GL_UNSIGNED_INT, 0);




        // glBindVertexArray(planeGeometry.VAO);
        // glDrawElements(GL_TRIANGLES, planeGeometry.indices.size(), GL_UNSIGNED_INT, 0);

        guiViewEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    boxGeometry.dispose();
    lightGeometry.dispose();
    glfwTerminate();

    return 0;
}
