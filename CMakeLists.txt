cmake_minimum_required(VERSION 3.20.0)

project(rtype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_TEST_SUITE OFF)
option(ENABLE_CODE_COVERAGE OFF)

if (COMPILER_TYPE MATCHES "msvc")
     message(STATUS "Using static SFML libraries")
     set(SFML_STATIC_LIBRARIES TRUE)
endif()

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

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

if (CLIENT_COMPILATION_MODE)
     add_compile_definitions(CLIENT_COMPILATION_MODE)
endif()

SET(RTYPE_MAJOR_VERSION 0)
SET(RTYPE_MINOR_VERSION 1)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${RTYPE_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${RTYPE_MINOR_VERSION}")
include(CPack)

