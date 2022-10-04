set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems)

set(SYSTEMS_SRC
    ${SRCROOT}/Movement.hpp
    ${SRCROOT}/PositionLogger.hpp
    PARENT_SCOPE
)

set(SYSTEMS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
