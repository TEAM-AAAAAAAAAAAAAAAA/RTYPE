set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)

set(SRC
    ${SRCROOT}/Position.hpp
    ${SRCROOT}/InputMoveUp.hpp
    PARENT_SCOPE
)

set(INCDIRS
    ${INCROOT}
    PARENT_SCOPE)
