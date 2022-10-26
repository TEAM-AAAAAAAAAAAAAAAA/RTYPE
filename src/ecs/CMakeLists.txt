set(ECS_INCROOT ${PROJECT_SOURCE_DIR}/src/ecs PARENT_SCOPE)
set(ECS_SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)

set(TARGET ${PROJECT_NAME}_ecs)

add_subdirectory(components)
add_subdirectory(systems)
add_subdirectory(utils)

set(ECS_SRC
    ${COMPONENTS_SRC}
    ${SYSTEMS_SRC}
)

set(ECS_INCDIRS
    ${ECS_INCROOT}
    ${COMPONENTS_INCDIRS}
    ${SYSTEMS_INCDIRS}
)
