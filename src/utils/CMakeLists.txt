set(INCROOT ${PROJECT_SOURCE_DIR}/src/utils)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/utils)

set(UTILS_SRC
    ${SRCROOT}/Window.cpp
    ${SRCROOT}/Window.hpp
    ${SRCROOT}/Constant.hpp
    PARENT_SCOPE
)

set(UTILS_INCDIRS
    ${INCROOT}
    PARENT_SCOPE
)
