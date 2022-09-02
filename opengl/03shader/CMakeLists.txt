add_executable(03shader
        main.cpp demo1.cpp demo.h demo2.cpp demo3.cpp)

message("shader libs=[${LIBS}]")
target_link_libraries(03shader
        PRIVATE
        ${LIBS})
message("shader 1111=[${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
message("shader 2222=[${CMAKE_RUNTIME_OUTPUT_DIRECTORY}]")



file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
#将生成的文件夹下内容全部拷贝到，指定目标目录；
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})