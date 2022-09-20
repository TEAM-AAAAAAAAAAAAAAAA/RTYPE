include(FetchContent)

set (SFML_VERSION "2.5.1")

if (NOT (SFML_OS_IOS OR SFML_OS_WINDOWS))
    set(BUILD_SHARED_LIBS TRUE "Building SFML in static mode")
endif()

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "${SFML_VERSION}"
)

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()
