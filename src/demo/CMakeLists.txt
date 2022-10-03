set(INCROOT ${PROJECT_SOURCE_DIR}/src/demo)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/demo)

set(TARGET rtype_demo)

set(SRC
    ${SRCROOT}/Demo.cpp
)

add_executable(${TARGET} ${SRC})

set(INCDIRS
    ${INCROOT}
    PARENT_SCOPE)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
