set(INCROOT ${PROJECT_SOURCE_DIR}/src/game)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/game)

set(SRC
    ${SRC}
    ${SRCROOT}/Demo.cpp
    PARENT_SCOPE
)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
