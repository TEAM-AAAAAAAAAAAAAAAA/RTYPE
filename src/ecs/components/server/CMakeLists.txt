set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components/server)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs/components/server)

set(COMPONENTS_SRC
    ${SRCROOT}/AttackAI.hpp
    ${SRCROOT}/AttackAI.cpp
    PARENT_SCOPE
)

set(COMPONENTS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
