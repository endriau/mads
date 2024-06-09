cmake_minimum_required(VERSION 3.28.1)

project(mads VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

include(cmake/cmocka.cmake)

enable_testing()

add_subdirectory(lib)
add_subdirectory(tests)
