set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/client)
set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/client)
#set(ECS_SRC ../ecs)

set(TARGET r-type_client)

set(SRC
    ${SRC_ROOT}/entrypoint.cpp
    ${SRC_ROOT}/Animation.cpp
    ${SRC_ROOT}/AssetLoader.cpp
    ${SRC_ROOT}/NetworkClient.cpp
    ${SRC_ROOT}/NetworkClient.hpp
)




add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} PRIVATE
    sfml-system sfml-network sfml-graphics sfml-window
    Boost::boost
)

target_include_directories(${TARGET}
        PRIVATE ${ECS_INCROOT}
)

target_include_directories(${TARGET} PRIVATE
    ${Boost_INCLUDE_DIRS}
)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_compile_definitions(CLIENT_COMPILATION_MODE)

install(TARGETS ${TARGET} DESTINATION bin)