cmake_minimum_required(VERSION 3.22.1)
project(mads VERSION 1.0.0)

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(${PROJECT_NAME} ${SOURCES})

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DMADS_STATIC_DEFINE)
endif ()

generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_NAME}_export.h")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}
    ARCHIVE  DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(EXPORT ${PROJECT_NAME}
    FILE "${PROJECT_NAME}-targets.cmake"
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION "lib/cmake/${PROJECT_NAME}")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION include FILES_MATCHING PATTERN "*.h")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h DESTINATION include)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    DESTINATION
    lib/cmake/${PROJECT_NAME})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION
    lib/cmake/${PROJECT_NAME})

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    DESTINATION
    lib/cmake/${PROJECT_NAME})


get_target_property(type ${PROJECT_NAME} TYPE)
if(${type} STREQUAL "SHARED_LIBRARY")
    set(BUILD_TYPE "-shared")
else()
    set(BUILD_TYPE "-static")
endif()

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}${BUILD_TYPE}")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP")

include(CPack)