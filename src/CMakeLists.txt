source_group("" FILES ${SRC})

set(TARGET test_main)

add_subdirectory(ecs)
add_subdirectory(server)
add_subdirectory(client)

add_executable(${TARGET} ${PROJECT_SOURCE_DIR}/src/main.cpp)

set_property(TARGET ${TARGET} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
