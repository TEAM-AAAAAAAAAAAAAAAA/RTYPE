set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components/client)

set(COMPONENTS_SRC
    ${SRCROOT}/Controllable.hpp
    ${SRCROOT}/Drawable.hpp
    ${SRCROOT}/Shootable.hpp
    ${SRCROOT}/Hitbox.hpp
    ${SRCROOT}/Parallax.hpp
    ${SRCROOT}/Animated.hpp
    PARENT_SCOPE
)

set(COMPONENTS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
