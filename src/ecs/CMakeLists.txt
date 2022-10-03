set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)

set(ECS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE)

add_subdirectory(components)
add_subdirectory(systems)
