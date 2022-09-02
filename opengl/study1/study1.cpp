//
// Created by yyl on 2022/9/2.
//

#include "study1.h"
#include "stdio.h"
#include "glad/glad.h"
#include "GlFW/glfw3.h"

int main(int arg,char **args){

    printf("study1 start");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return 0;
}