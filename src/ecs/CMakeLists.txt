set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)
set(INCROOT ${PROJECT_SOURCE_DIR}/ecs)
set(SRCROOT ${PROJECT_SOURCE_DIR}/ecs)

set(SRC
    ${SRC}
    ${SRCROOT}/Entity.hpp
    ${SRCROOT}/Registry.hpp
    ${SRCROOT}/SparseArray.hpp
set(ECS_SRC
    ${INCROOT}/ecs.cpp
    PARENT_SCOPE
)

set(ECS_INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
