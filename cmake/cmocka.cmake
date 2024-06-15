find_package(cmocka QUIET)
if (NOT cmocka_FOUND)
    set(FETCHCONTENT_QUIET FALSE)
    FetchContent_Declare(
        cmocka
        GIT_REPOSITORY https://github.com/clibs/cmocka.git
        GIT_TAG cmocka-1.1.5
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL)
    set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)
    set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
    set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
    set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
    set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)
    FetchContent_MakeAvailable(cmocka)
    if (BUILD_SHARED_LIBS)
        set(CMOCKA_LIBRARY cmocka)
    else ()
        set(CMOCKA_LIBRARY cmocka-static)
    endif ()
endif ()