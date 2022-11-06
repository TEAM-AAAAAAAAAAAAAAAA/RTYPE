set(ECS_INCROOT ${PROJECT_SOURCE_DIR}/src/ecs PARENT_SCOPE)
set(ECS_SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)

set(TARGET ${PROJECT_NAME}_ecs)

add_subdirectory(components)
add_subdirectory(systems)

set(ECS_SRC
    ${ECS_SRCROOT}/WorldManager.cpp
    ${ECS_SRCROOT}/WorldManager.hpp
    ${COMPONENTS_SRC}
    ${SYSTEMS_SRC}
    PARENT_SCOPE
)

set(ECS_INCDIRS
    ${ECS_INCROOT}
    ${COMPONENTS_INCDIRS}
    ${SYSTEMS_INCDIRS}
)

install(DIRECTORY ${ECS_INCROOT} DESTINATION include)
