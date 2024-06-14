find_package(cmocka QUIET)
if (NOT cmocka_FOUND)
    set(FETCHCONTENT_QUIET FALSE)
    FetchContent_Declare(
        cmocka
        GIT_REPOSITORY https://github.com/clibs/cmocka.git
        GIT_TAG cmocka-1.1.5
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL)
    set(WITH_STATIC_LIB ON)
    set(WITH_CMOCKERY_SUPPORT OFF)
    set(WITH_EXAMPLES OFF)
    set(UNIT_TESTING OFF)
    set(PICKY_DEVELOPER OFF)
    FetchContent_MakeAvailable(cmocka)
    if (BUILD_SHARED_LIBS)
        set(CMOCKA_LIBRARY cmocka)
    else ()
        set(CMOCKA_LIBRARY cmocka-static)
    endif ()
endif ()