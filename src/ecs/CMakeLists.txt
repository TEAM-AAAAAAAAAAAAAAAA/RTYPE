set(ECS_INCROOT ${PROJECT_SOURCE_DIR}/src/ecs PARENT_SCOPE)
set(ECS_SRCROOT ${PROJECT_SOURCE_DIR}/src/ecs)

set(TARGET ${PROJECT_NAME}_ecs)

add_subdirectory(components)
add_subdirectory(systems)
add_subdirectory(utils)

set(ECS_SRC
    ${COMPONENTS_SRC}
    ${SYSTEMS_SRC}
    ${ECS_SRCROOT}/Constant.hpp
    ${ECS_SRCROOT}/Engine.hpp
    ${ECS_SRCROOT}/Entity.hpp
    ${ECS_SRCROOT}/Event.hpp
    ${ECS_SRCROOT}/Registry.hpp
    ${ECS_SRCROOT}/SparseArray.hpp
    ${ECS_SRCROOT}/World.hpp
)

set(ECS_INCDIRS
    ${ECS_INCROOT}
    ${COMPONENTS_INCDIRS}
    ${SYSTEMS_INCDIRS}
)


add_library(${TARGET} SHARED ${ECS_SRC})

include(GenerateExportHeader)

generate_export_header(${TARGET})

target_include_directories(${TARGET}
                      PUBLIC ${INCROOT}
                      PRIVATE ${ECS_INCDIRS}
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)