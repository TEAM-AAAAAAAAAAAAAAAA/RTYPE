set(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)

cmake_minimum_required(VERSION 3.20.0)

project(rtype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

option(BUILD_TEST_SUITE OFF)
option(ENABLE_CODE_COVERAGE OFF)

set(SFML_DIR ${PROJECT_SOURCE_DIR}/vcpkg/installed/x64-linux-dynamic/share/sfml)

#if (COMPILER_TYPE MATCHES "msvc")
#     message(STATUS "Using static SFML libraries")
#     set(SFML_STATIC_LIBRARIES TRUE)
#endif()

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


find_package(SFML COMPONENTS graphics window audio system CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()

option(BUILD_TEST_SUITE OFF)

include(CompilerFlags)
include(DetectCompiler)

set(VCPKG_TARGET_TRIPLET x64-linux-dynamic)

add_subdirectory(src)
if (BUILD_TEST_SUITE)
    enable_testing()
    add_subdirectory(tests)
endif()

if (CLIENT_COMPILATION_MODE)
    add_compile_definitions(CLIENT_COMPILATION_MODE)
endif()

install(DIRECTORY assets DESTINATION bin)

SET(RTYPE_MAJOR_VERSION 0)
SET(RTYPE_MINOR_VERSION 1)

set(CPACK_WIX_LICENSE_RTF ${PROJECT_SOURCE_DIR}/misc/windows/wix_licence.txt)

message(STATUS "Registering DEB package infos")
set(CPACK_DEBIAN_PACKAGE_NAME "r-thaaaaaai")
set(CPACK_DEBIAN_PACKAGE_VERSION "${RTYPE_MAJOR_VERSION}.${RTYPE_MINOR_VERSION}")
set(CPACK_DEBIAN_PACKAGE_CONTACT "constant.vigneron@epitech.eu")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "TEAM-AAAAAAAAAAAAAAAA")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsfml-dev, libboost-dev")


set(CPACK_GENERATOR "DEB;RPM;TGZ")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${RTYPE_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${RTYPE_MINOR_VERSION}")
include(CPack)

