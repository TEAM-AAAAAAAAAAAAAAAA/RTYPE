set(INC_ROOT ${PROJECT_SOURCE_DIR}/src/demo)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/src/demo)
set(ECS_SRC ../ecs)

set(TARGET rtype_demo)

set(SRC
        ${SRC_ROOT}/Demo.cpp
)

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} PRIVATE
    ${PROJECT_NAME}_ecs Boost::thread pthread
)

if (CLIENT_COMPILATION_MODE)
    target_link_libraries(${TARGET} PRIVATE
        sfml-system sfml-network sfml-graphics sfml-window
    )
endif()


set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

if (CLIENT_COMPILATION_MODE)
    add_compile_definitions(CLIENT_COMPILATION_MODE)
endif()
