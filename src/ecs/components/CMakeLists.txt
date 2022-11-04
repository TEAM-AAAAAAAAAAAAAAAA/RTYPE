set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components)

set(COMPONENTS_SRC
    ${SRCROOT}/Dead.hpp
    ${SRCROOT}/Direction.hpp
    ${SRCROOT}/EntityAI.hpp
    ${SRCROOT}/EntityAI.cpp
    ${SRCROOT}/Faction.hpp
    ${SRCROOT}/Health.hpp
    ${SRCROOT}/Position.hpp
    ${SRCROOT}/Size.hpp
    ${SRCROOT}/Velocity.hpp
    ${SRCROOT}/Weapon.hpp
    ${SRCROOT}/EntityType.hpp
    ${SRCROOT}/EntityLife.hpp
    ${SRCROOT}/NetworkId.hpp
    PARENT_SCOPE
)

set(COMPONENTS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
