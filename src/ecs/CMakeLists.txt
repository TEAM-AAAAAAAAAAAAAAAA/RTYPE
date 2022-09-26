set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)

set(SRC
    ${SRC}
    ${SRCROOT}/Registry.hpp
    ${SRCROOT}/SparseArray.hpp
    PARENT_SCOPE
)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
