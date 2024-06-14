cmake_minimum_required(VERSION 3.22.1)

project(mads VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

include(FetchContent)

include(cmake/cmocka.cmake)

enable_testing()

add_subdirectory(lib)

add_subdirectory(tests)