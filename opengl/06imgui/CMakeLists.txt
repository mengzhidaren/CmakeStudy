add_executable(06imgui
        main.cpp
        demo1.cpp
        )

message("06imgui libs=[${LIBS}]")
target_link_libraries(06imgui
        PRIVATE
        ${LIBS})
message("06imgui 1111=[${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
message("06imgui 2222=[${CMAKE_CURRENT_BINARY_DIR}]")

if (ChangeOutPath)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/06)
else ()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/06)
endif ()
#将生成的文件夹下内容全部拷贝到，指定目标目录；
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/03shader)