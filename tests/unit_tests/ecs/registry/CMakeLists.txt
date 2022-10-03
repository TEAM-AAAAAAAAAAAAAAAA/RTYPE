set (INCLUDE_TEST_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/registry)
set (SRC_TEST_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/registry)
set (SRC_ROOT ../../../../src/ecs)
set (INC_ROOT ../../../../src/ecs)

set(SOURCES
        ${SRC_TEST_ROOT}/registryTests.cpp
        ${SRC_ROOT}/Registry.hpp
        )

create_test(
        TEST_NAME registry_test
        TEST_SRC ${SOURCES}
)