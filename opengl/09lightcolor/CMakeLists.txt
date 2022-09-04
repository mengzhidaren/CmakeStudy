add_executable(09light
        light2color.cpp)

message("09light libs=[${LIBS}]")
target_link_libraries(09light
        PRIVATE
        ${LIBS})
message("09light 1111=[${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
message("09light 2222=[${CMAKE_CURRENT_BINARY_DIR}]")

if (ChangeOutPath)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader2 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/09)
else ()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader2 DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/09)
endif ()
#将生成的文件夹下内容全部拷贝到，指定目标目录；
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/03shader)