#add_library(glad STATIC)
add_library(glad SHARED)
target_sources(glad
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
        )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(
        glad
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)