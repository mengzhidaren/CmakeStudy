add_executable(04texture
        mian.cpp
#        demo.h
        demo1.cpp
        demo2.cpp
        )

message("04texture libs=[${LIBS}]")
target_link_libraries(04texture
        PRIVATE
        ${LIBS})
message("04texture 1111=[${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
message("04texture 2222=[${CMAKE_CURRENT_BINARY_DIR}]")

if (ChangeOutPath)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/04)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader2 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/04)
else ()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/04)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader2 DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/04)
endif ()
#将生成的文件夹下内容全部拷贝到，指定目标目录；
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/03shader)