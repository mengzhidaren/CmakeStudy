add_executable(study1)
target_sources(study1
        PRIVATE
        study1.cpp
        )


message("LIBS=[ ${LIBS} ]")

target_link_libraries(study1
        PRIVATE
        ${LIBS})

