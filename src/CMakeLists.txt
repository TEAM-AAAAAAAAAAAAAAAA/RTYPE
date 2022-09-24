# Sources

set(INCROOT ${PROJECT_SOURCE_DIR}/src)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(INCDIRS ${INCROOT})

add_subdirectory(ecs)
# add_subdirectory(logger)
# add_subdirectory(script)
# add_subdirectory(util)
# add_subdirectory(game)

# Source groups are a feature in Visual Studio.
source_group("" FILES ${SRC})

# Targets
#
# The project is split into a static library containing most of the code,
# and an executable containing the main function.
# This enables unit-testing, since testing against an executable result in linking errors
# due to the main function being defined twice.
set(LIB_NAME librtype)
set(TARGET_NAME rtype)

include(CompilerFlags)

# target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
# target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})

add_executable(${TARGET_NAME} ${SRCROOT}/main.cpp)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(${TARGET_NAME} PRIVATE sfml-graphics sfml-audio)

add_custom_command(TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
