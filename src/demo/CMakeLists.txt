set(INC_ROOT ${PROJECT_SOURCE_DIR}/src/demo)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/src/demo)
set(ECS_SRC ../ecs)

set(TARGET rtype_demo)

set(SRC
        ${SRC_ROOT}/Demo.cpp
)

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} PRIVATE
    sfml-system sfml-network sfml-graphics sfml-window ${PROJECT_NAME}_ecs pthread
)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
