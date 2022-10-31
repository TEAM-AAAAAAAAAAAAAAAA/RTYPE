set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/server)
set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/server)
#set(ECS_SRC ../ecs)

set(TARGET r-type_server)

set(SRC
    ${SRC_ROOT}/Server.cpp
    ${SRC_ROOT}/Server.hpp
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

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

install(TARGETS ${TARGET} DESTINATION bin)