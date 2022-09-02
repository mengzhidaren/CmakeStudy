add_executable(03shader
        main.cpp demo1.cpp demo.h demo2.cpp demo3.cpp)

message("shader libs=[${LIBS}]")
target_link_libraries(03shader
        PRIVATE
        ${LIBS})

