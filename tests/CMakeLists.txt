cmake_minimum_required(VERSION 3.22.1)

project(mads_tests)

set(CMAKE_C_STANDARD 23)

# Unit testing for sort.h algorithm.
add_cmocka_test(sort_test
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/mads/algorithms/sort_test.c"
    COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
    LINK_OPTIONS ${DEFAULT_LINK_FLAGS}
    LINK_LIBRARIES ${CMOCKA_LIBRARY} mads)

# Unit testing for array.h data structure.
add_cmocka_test(array_test
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/mads/data_structures/array_test.c"
    COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS} "-fno-strict-aliasing"
    LINK_OPTIONS ${DEFAULT_LINK_OPTIONS}
    LINK_LIBRARIES ${CMOCKA_LIBRARY} mads)

add_cmocka_test(hash_table_test
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/mads/data_structures/hash_table_test.c"
    COMPILE_OPTIONS ${DEFAULT_C_COMPILER_FLAGS}
    LINK_OPTIONS ${DEFAULT_LINK_OPTIONS}
    LINK_LIBRARIES ${CMOCKA_LIBRARY} mads)

if (BUILD_SHARED_LIBS)
    list(APPEND TEST_TARGETS "sort_test;array_test;hash_table_test")
    foreach (TEST_TARGET IN LISTS TEST_TARGETS)
        add_custom_command(TARGET ${TEST_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t
            $<TARGET_FILE_DIR:${TEST_TARGET}>
            $<TARGET_RUNTIME_DLLS:${TEST_TARGET}>
            COMMAND_EXPAND_LISTS)
    endforeach ()
endif ()