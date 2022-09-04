add_executable(05matrix
        main.cpp
        #        demo.h
        demo1.cpp
        demo2.cpp
        demo3.cpp
        )

message("05matrix libs=[${LIBS}]")
target_link_libraries(05matrix
        PRIVATE
        ${LIBS})
message("05matrix 1111=[${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
message("05matrix 2222=[${CMAKE_CURRENT_BINARY_DIR}]")

if (ChangeOutPath)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/05)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader2 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/05)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader3 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/05)
else ()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/05)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader2 DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/05)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/05)
endif ()
#将生成的文件夹下内容全部拷贝到，指定目标目录；
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/03shader)