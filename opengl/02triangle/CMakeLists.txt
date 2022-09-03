add_executable(02triangle
        main.cpp
        demo2.cpp
        demo3.cpp
        demo4.cpp demo1.cpp demo.h)
#target_sources(02triangle
#        PRIVATE
#        main.cpp
#        )


#message("02triangle  LIBS=[ ${LIBS} ]")

target_link_libraries(02triangle
        PRIVATE
        ${LIBS})

