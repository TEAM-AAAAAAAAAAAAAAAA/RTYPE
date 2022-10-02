source_group("" FILES ${SRC})

add_subdirectory(client)
add_subdirectory(ecs)
add_subdirectory(game)
add_subdirectory(server)
add_subdirectory(utils)

# set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
