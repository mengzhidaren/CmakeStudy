add_library(yyllib SHARED)

target_sources(yyllib
        PRIVATE
        yyl.cpp
        yyl/shader.h
        )

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
message("yyl libs=[${LIBS}]")
target_link_libraries(yyllib
        ${LIBS}
        )
target_include_directories(
        yyllib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR})
