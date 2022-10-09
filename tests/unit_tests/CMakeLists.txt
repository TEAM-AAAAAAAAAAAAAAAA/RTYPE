set (INCLUDE_TEST_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests)
set (SRC_TEST_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests)
set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/ecs)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/ecs)

function (create_test)
    set (test_name TEST_NAME)
    set (test_src TEST_SRC TEST_DEPS)
    cmake_parse_arguments(create_test "" "${test_name}" "${test_src}" ${ARGN})

    if (NOT DEFINED create_test_TEST_NAME)
        message (FATAL_ERROR "create_test: TEST_NAME not defined")
    endif()
    if (NOT DEFINED create_test_TEST_SRC)
        message (FATAL_ERROR "create_test: TEST_SRC not defined")
    endif()

    set (SRC "${create_test_TEST_SRC}")
    set (TEST_NAME "${create_test_TEST_NAME}")
    set (TEST_DEPS "${create_test_TEST_DEPS}")
    add_executable(${TEST_NAME} ${SRC})
    target_link_libraries(${TEST_NAME} ${TEST_DEPS} criterion)
    target_include_directories(${TEST_NAME} PRIVATE
            ${SRC_ROOT}
            )
    add_test(${TEST_NAME} ${TEST_NAME})
endfunction()
add_subdirectory(ecs)