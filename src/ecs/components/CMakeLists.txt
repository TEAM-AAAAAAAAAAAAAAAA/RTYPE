set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)

set(COMPONENTS_SRC
    ${SRCROOT}/server/AttackAI.hpp
    ${SRCROOT}/server/AttackAI.cpp
    ${SRCROOT}/Direction.hpp
    ${SRCROOT}/Faction.hpp
    ${SRCROOT}/Health.hpp
    ${SRCROOT}/MovementAI.hpp
    ${SRCROOT}/MovementAI.cpp
    ${SRCROOT}/Position.hpp
    ${SRCROOT}/Size.hpp
    ${SRCROOT}/Velocity.hpp
    ${SRCROOT}/Weapon.hpp
    ${SRCROOT}/EntityType.hpp
    ${SRCROOT}/NetworkId.hpp
    ${SRCROOT}/Score.hpp
    PARENT_SCOPE
)

set(COMPONENTS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
