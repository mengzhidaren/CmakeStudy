message("current dir=${CMAKE_CURRENT_SOURCE_DIR}")
# 开始加载------glfw-----------
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
list(APPEND LIBS glm)
# 加载结束

add_subdirectory(lib/yyl)
list(APPEND LIBS yyllib)


