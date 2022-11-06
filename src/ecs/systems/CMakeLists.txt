set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems)

set(SYSTEMS_SRC
    ${SRCROOT}/ManageClientEvents.hpp
    ${SRCROOT}/Movement.hpp
    ${SRCROOT}/PositionLogger.hpp
    ${SRCROOT}/RunAI.hpp
    ${SRCROOT}/ServerPush.hpp
    PARENT_SCOPE
)

set(SYSTEMS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
