set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems/client)

set(SYSTEMS_SRC
    ${SRCROOT}/Draw.hpp
    ${SRCROOT}/HandleSFMLEvents.hpp
    ${SRCROOT}/HandleSFMLKeys.hpp
    PARENT_SCOPE
)

set(SYSTEMS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
