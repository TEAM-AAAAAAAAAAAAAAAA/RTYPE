set(INCROOT ${PROJECT_SOURCE_DIR}/src/components)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/components)

set(SRC
    ${SRC}
    ${SRCROOT}/Position.hpp
    PARENT_SCOPE
)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
