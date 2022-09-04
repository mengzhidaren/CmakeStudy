add_executable(03shader
        main.cpp demo1.cpp demo.h demo2.cpp demo3.cpp)

#message("03shader libs=[${LIBS}]")
target_link_libraries(03shader
        PRIVATE
        ${LIBS})
#message("03shader 1111=[${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
#message("03shader 2222=[${CMAKE_CURRENT_BINARY_DIR}]")

if (ChangeOutPath)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/03)
else ()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/03)
endif ()
#将生成的文件夹下内容全部拷贝到，指定目标目录；
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/03shader)