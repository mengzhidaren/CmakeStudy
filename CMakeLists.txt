cmake_minimum_required(VERSION 3.24.1)
project(cmakedemo VERSION 0.1.0)

# include(cmakeConfig/cmake_compiler.cmake)
include(cmakeConfig/cmake_output_path.cmake)

add_subdirectory(simple)
# add_executable(cmakedemo main.cpp)
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
# include(CTest)
# enable_testing()

# find_package(Vulkan REQUIRED)
# if(Vulkan_FOUND)
# message("找到了 ${Vulkan_INCLUDE_DIRS}")
# endif()