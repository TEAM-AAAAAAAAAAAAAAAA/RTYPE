set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/sparse_array)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/sparse_array)

set(TEST_SRC_ROOT
        ${SRC_ROOT}/sparse_array_tests.cpp
        )

create_test(
        TEST_NAME sparse_array_test
        TEST_SRC ${TEST_SRC_ROOT}
)