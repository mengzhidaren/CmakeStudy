add_executable(07camera
        main.cpp
        demo1.cpp
        demo2.cpp
        )

message("07camera libs=[${LIBS}]")
target_link_libraries(07camera
        PRIVATE
        ${LIBS})
message("07camera 1111=[${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
message("07camera 2222=[${CMAKE_CURRENT_BINARY_DIR}]")

if (ChangeOutPath)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/07)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader2 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/07)
else ()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/07)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader2 DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/07)
endif ()
#将生成的文件夹下内容全部拷贝到，指定目标目录；
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/03shader)