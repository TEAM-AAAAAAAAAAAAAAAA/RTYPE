set(INCROOT ${PROJECT_SOURCE_DIR}/src/ecs)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)

set(TARGET ${PROJECT_NAME}_ecs)

add_subdirectory(components)
add_subdirectory(systems)


set(ECS_SRC
    ${COMPONENTS_SRC}
    ${SYSTEMS_SRC}
    ${SRCROOT}/Constant.hpp
    ${SRCROOT}/Engine.hpp
    ${SRCROOT}/Entity.hpp
    ${SRCROOT}/Event.hpp
    ${SRCROOT}/Registry.hpp
    ${SRCROOT}/SparseArray.hpp
    ${SRCROOT}/World.hpp
)

set(ECS_INCDIRS
    ${INCROOT}
    ${COMPONENTS_INCDIRS}
    ${SYSTEMS_INCDIRS}
)

add_library(${TARGET} STATIC ${ECS_SRC})

target_include_directories(${TARGET}
                      PUBLIC ${INCROOT}
                      PRIVATE ${ECS_INCDIRS}
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)