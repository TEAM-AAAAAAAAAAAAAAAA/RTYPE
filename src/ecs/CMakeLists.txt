set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)

set(SRC
    ${SRC}
    ${SRCROOT}/ecs.cpp
    ${SRCROOT}/ecs.hpp
    ${SRCROOT}/sparseArray.hpp
    PARENT_SCOPE
)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
