set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems)

set(SYSTEMS_SRC
        ${SRCROOT}/Draw.hpp
        ${SRCROOT}/HandleSFMLEvents.hpp
        ${SRCROOT}/HandleSFMLKeys.hpp
        ${SRCROOT}/ManageClientEvents.hpp
        ${SRCROOT}/Movement.hpp
        ${SRCROOT}/PositionLogger.hpp
        ${SRCROOT}/ProjectileCollision.hpp
        ${SRCROOT}/ServerPush.hpp
        ${SRCROOT}/PositionUpdate.hpp
        ${SRCROOT}/DeathUpdate.hpp
        ${SRCROOT}/ShowHitBox.hpp
        PARENT_SCOPE
        )

set(SYSTEMS_INCDIRS
        ${INCROOT}
        PARENT_SCOPE
        )
