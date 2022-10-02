set (INCLUDE_TEST_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/systems)
set (SRC_TEST_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/ecs/systems)
#set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems)
#set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/ecs/systems)

set(SOURCES
        ${SRC_TEST_ROOT}/systemsTests.cpp
        )

create_test(
        TEST_NAME systems_test
        TEST_SRC ${SOURCES}
)