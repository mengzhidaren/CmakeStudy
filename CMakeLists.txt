cmake_minimum_required(VERSION 3.23)
project(cmakedemo VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
#文件以utf-8方式加载
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
# include(cmakeConfig/cmake_compiler.cmake)
include(cmakeConfig/cmake_output_path.cmake)

include(lib/attachLib.cmake)

add_subdirectory(opengl)


message("工具链： CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")

# add_executable(cmakedemo main.cpp)
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
# include(CTest)
# enable_testing()
# 这里
# find_package(Vulkan REQUIRED)
# if(Vulkan_FOUND)
# message("找到了 ${Vulkan_INCLUDE_DIRS}")
# endif()