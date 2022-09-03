add_executable(01createWindow)
target_sources(01createWindow
        PRIVATE
        study1.cpp
        )


#message("01createWindow   LIBS=[ ${LIBS} ]")

target_link_libraries(01createWindow
        PRIVATE
        ${LIBS})

