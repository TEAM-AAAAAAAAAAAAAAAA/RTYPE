set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)

#set(ECS_SRC
#    ${INCROOT}/ecs.cpp
#    PARENT_SCOPE
#)

set(ECS_INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)

add_subdirectory(components)
