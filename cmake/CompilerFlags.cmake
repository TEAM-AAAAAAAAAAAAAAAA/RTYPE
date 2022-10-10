# Platform-specific compilation options

macro(get_WIN32_WINNT version)
    if (WIN32 AND CMAKE_SYSTEM_VERSION)
        set(WIN_VER ${CMAKE_SYSTEM_VERSION})
        string(REPLACE "." "" WIN_VER ${WIN_VER})
        string(REGEX REPLACE "([0-9])" "0\\1" WIN_VER ${WIN_VER})
        set (${version} "Ox${WIN_VER}")
    endif()
endmacro()

# Enable Warnings
if(COMPILER_TYPE MATCHES "msvc")
    message(STATUS "Enabling MSVC-specific options")

    add_compile_options(
        "/W4"
        "/WX"
    )
    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
elseif(COMPILER_TYPE MATCHES "gcc")
    message(STATUS "Enabling GCC-specific options")

    add_compile_options(
        "-Wall" "-Wextra" "-Wshadow" "-pedantic" "-Wpointer-arith"
        "-Wsuggest-override"
        "-Wno-unknown-pragmas"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )

    if(ENABLE_TEST_COVERAGE)
        add_compile_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
        add_link_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    endif()
elseif(COMPILER_TYPE MATCHES "clang")
    message(STATUS "Enabling Clang-specific options")

    add_compile_options(
        "-Wall" "-Wextra" "-Wshadow"
        "-Wno-unknown-pragmas"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_definitions(RELEASE=1)
endif()
