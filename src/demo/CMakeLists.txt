set(INC_ROOT ${PROJECT_SOURCE_DIR}/src/demo)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/src/demo)
set(ECS_SRC ${PROJECT_SOURCE_DIR}/src/ecs)

set(TARGET rtype_demo)

set(SRC
        ${SRC_ROOT}/Demo.cpp
        )

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} PRIVATE
    sfml-system sfml-network sfml-graphics sfml-window
)

set(INCDIRS
        ${ECS_ROOT}
        ${INCROOT}
        PARENT_SCOPE
        )

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
