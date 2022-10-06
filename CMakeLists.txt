cmake_minimum_required(VERSION 3.20.0)

project(rtype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_TEST_SUITE OFF)
option(ENABLE_CODE_COVERAGE OFF)

set(SFML_DIR ${PROJECT_SOURCE_DIR}/cmake)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(Boost REQUIRED)

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
     set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()

option(BUILD_TEST_SUITE OFF)

include(CompilerFlags)
include(DetectCompiler)

# add_subdirectory(dependencies)

add_subdirectory(src)
if (BUILD_TEST_SUITE)
     enable_testing()
     add_subdirectory(tests)
endif()
