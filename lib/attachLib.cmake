message("current dir=${CMAKE_CURRENT_SOURCE_DIR}")
# 开始加载------glfw-----------
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" ON)
option(GLFW_VULKAN_STATIC "Assume the Vulkan loader is linked with the application" OFF)
add_subdirectory(lib/glfw)
list(APPEND LIBS glfw ${GLFW_LIBRARIES})
# 加载结束
# 开始加载 ----------glad-----------
add_subdirectory(lib/glad)
list(APPEND LIBS glad)
if (NOT WIN32)
    LIST(APPEND LIBS dl)
endif ()
# 加载结束
# 开始加载-------glm----------------
add_subdirectory(lib/glm)
# 加载结束