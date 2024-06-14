cmake_minimum_required(VERSION 3.22.1)

project(mads_tests)

set(CMAKE_C_STANDARD 23)

# Unit testing for sort.h algorithm.
add_cmocka_test(sort_test
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/mads/algorithms/sort_test.c"
    COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
    LINK_OPTIONS ${DEFAULT_LINK_FLAGS}
    LINK_LIBRARIES ${CMOCKA_LIBRARIES} mads)

# Unit testing for array.h data structure.
add_cmocka_test(array_test
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/mads/data_structures/array_test.c"
    COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
    LINK_OPTIONS ${DEFAULT_LINK_OPTIONS}
    LINK_LIBRARIES ${CMOCKA_LIBRARIES} mads)


#if (BUILD_SHARED_LIBS)
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy -t
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>
#        $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
#        COMMAND_EXPAND_LISTS)
#endif ()