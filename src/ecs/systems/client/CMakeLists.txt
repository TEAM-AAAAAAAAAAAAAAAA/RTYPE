set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems/client)

set(SYSTEMS_SRC
    ${SRCROOT}/Draw.hpp
    ${SRCROOT}/ExecuteOnce.hpp
    ${SRCROOT}/HandleIncomingMessages.hpp
    ${SRCROOT}/PeriodicPing.hpp
    ${SRCROOT}/HandleSFMLEvents.hpp
    ${SRCROOT}/HandleSFMLKeys.hpp
    ${SRCROOT}/MenuSelect.hpp
    ${SRCROOT}/SendDirection.hpp
    ${SRCROOT}/HandleParallaxBounds.hpp
    ${SRCROOT}/Buttons.hpp
    PARENT_SCOPE
)

set(SYSTEMS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
