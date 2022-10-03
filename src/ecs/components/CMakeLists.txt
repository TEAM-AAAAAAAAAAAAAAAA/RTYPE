set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)

set(SRC
    ${SRCROOT}/Controllable.hpp
    ${SRCROOT}/Drawable.hpp
    ${SRCROOT}/Position.hpp
    ${SRCROOT}/Size.hpp
    PARENT_SCOPE
)

set(INCDIRS
    ${INCROOT}
    PARENT_SCOPE)
