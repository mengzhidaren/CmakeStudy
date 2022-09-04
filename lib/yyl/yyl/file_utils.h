//
// Created by 27351 on 2022/9/3.
//
#pragma once
#ifndef CMAKEDEMO_FILE_UTILS_H
#define CMAKEDEMO_FILE_UTILS_H
//#include <unistd.h>
//#include <direct.h>
#include <string>
//#include <iostream>
#include <filesystem>

namespace fileUtils {
//    std::string currentPathCwd(const std::string& filePath) {
//        char *pathDir = getcwd(NULL, 0);
//        std::string newPath = std::string(pathDir) + std::string(filePath);
//        free(pathDir);
//        std::cout << "currentPathCwd=" << newPath << std::endl;
//        return newPath;
//    }
//如果在这里实现方法  引用这个头文件会出现方法名重复错误 所在要在.cpp中实现方法
    std::string currentPath(const std::string &filePath);
    std::string staticPath(const std::string &filePath);


}


#endif //CMAKEDEMO_FILE_UTILS_H
