set (INCLUDE_TEST_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/sparse_array)
set (SRC_TEST_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/sparse_array)
set (INC_ROOT ${PROJECT_SOURCE_DIR}/ecs)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/ecs)

set (SOURCES
        ${SRC_TEST_ROOT}/sparseArrayTests.cpp
        ${SRC_ROOT}/SparseArray.hpp
        )

create_test(
        TEST_NAME sparse_array_test
        TEST_SRC ${SOURCES}
)