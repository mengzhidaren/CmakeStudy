//
// Created by 27351 on 2022/9/4.
//
#include "file_utils.h"

namespace fileUtils {
//    std::string currentPathCwd(const std::string& filePath) {
//        char *pathDir = getcwd(NULL, 0);
//        std::string newPath = std::string(pathDir) + std::string(filePath);
//        free(pathDir);
//        std::cout << "currentPathCwd=" << newPath << std::endl;
//        return newPath;
//    }

    std::string currentPath(const std::string &filePath) {
        auto currentPath = std::filesystem::current_path();
        std::string newPath = currentPath.string()+"\\" + filePath;
//        std::cout << "currentPath=" << newPath << std::endl;
        return newPath;
    }
    std::string staticPath(const std::string &filePath) {
        auto currentPath = std::filesystem::current_path().parent_path().parent_path();
        std::string newPath = currentPath.string()+"\\static\\" + filePath;
//        std::cout << "staticPath=" << newPath << std::endl;
        return newPath;
    }


}