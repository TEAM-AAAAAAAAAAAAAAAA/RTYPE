set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/client)
set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/client)

set(TARGET rtype_client)

set(SRC
    ${SRC_ROOT}/entrypoint.cpp
)

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} PRIVATE
    sfml-system sfml-network sfml-graphics sfml-window
    Boost::boost
)

target_include_directories(${TARGET} PRIVATE
    ${Boost_INCLUDE_DIRS}
)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})