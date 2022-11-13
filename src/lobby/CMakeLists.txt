set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/lobby)
set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/lobby)
#set(ECS_SRC ../ecs)

set(TARGET r-type_lobby)

set(SRC
    ${SRC_ROOT}/../server/Server.cpp
    ${SRC_ROOT}/HubServer.hpp
    ${SRC_ROOT}/entrypoint.cpp
)

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} PRIVATE
    ${Boost_LIBRARIES}

)

target_include_directories(${TARGET}
        PRIVATE ${ECS_INCROOT}
)

target_include_directories(${TARGET} PRIVATE
    ${Boost_INCLUDE_DIRS}
)

install(TARGETS ${TARGET} DESTINATION bin)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

