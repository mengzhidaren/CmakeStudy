add_library(dynLib SHARED)
target_sources(dynLib
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/dynLib.cpp
)
target_include_directories(dynLib
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/demo2
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR})