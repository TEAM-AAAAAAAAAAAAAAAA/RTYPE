set(DEMO_SRC ${PROJECT_SOURCE_DIR}/src/demo/)
source_group("" FILES ${SRC})

add_subdirectory(ecs)
add_subdirectory(client)
add_subdirectory(server)
