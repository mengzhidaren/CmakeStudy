//
// Created by 27351 on 2022/9/3.
//
#include <iostream>
//using namespace std;
//#include "yyl/file_utils.hpp"
#include "yyl/file_utils.h"
#include "demo.h"
using namespace std;
int main(){
    texture1::main();
//    texture2::main();
//shaper2::main();
//    shaper3::main();

    cout << "current_path="<<fileUtils::currentPath("shader\\vertex.vert") << endl;
    cout << "current_path="<<fileUtils::staticPath("container.jpg") << endl;

    return 0;
}