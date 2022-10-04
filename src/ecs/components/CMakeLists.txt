set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)

set(COMPONENTS_SRC
    ${SRCROOT}/Controllable.hpp
    ${SRCROOT}/Damage.hpp
    ${SRCROOT}/Drawable.hpp
    ${SRCROOT}/EnemyAI.hpp
    ${SRCROOT}/Health.hpp
    ${SRCROOT}/Position.hpp
    ${SRCROOT}/Shootable.hpp
    ${SRCROOT}/Size.hpp
    ${SRCROOT}/Velocity.hpp
    PARENT_SCOPE
)

set(COMPONENTS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
