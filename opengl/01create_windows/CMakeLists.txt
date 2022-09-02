add_executable(01createWindow)
target_sources(01createWindow
        PRIVATE
        study1.cpp
        )


message("LIBS=[ ${LIBS} ]")

target_link_libraries(01createWindow
        PRIVATE
        ${LIBS})

