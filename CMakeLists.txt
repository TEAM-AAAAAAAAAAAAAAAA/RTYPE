cmake_minimum_required(VERSION 3.16.0)

project(rtype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_TEST_SUITE OFF)
option(ENABLE_CODE_COVERAGE OFF)

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
     set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()


# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# add_subdirectory(dependencies)
include(DetectCompiler)

add_subdirectory(src)
# find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)