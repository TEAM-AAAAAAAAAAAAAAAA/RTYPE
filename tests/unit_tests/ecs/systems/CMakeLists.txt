set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/systems)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/systems)

set(TEST_SRC_ROOT
        ${SRC_ROOT}/systems_tests.cpp
        )

create_test(
        TEST_NAME systems_test
        TEST_SRC ${TEST_SRC_ROOT}
)