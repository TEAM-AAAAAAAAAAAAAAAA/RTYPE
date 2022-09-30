set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/registry)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/registry)

set(TEST_SRC_ROOT
        ${SRC_ROOT}/registry_tests.cpp
        )

create_test(
        TEST_NAME registry_test
        TEST_SRC ${TEST_SRC_ROOT}
)