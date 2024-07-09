# Try to find the cmocka package in quiet mode.
find_package(cmocka QUIET)

# If cmocka cannot be found then we need to download
# it from it's repository and make it available.
if (NOT cmocka_FOUND)
    # Output all steps from download to configuration.
    set(FETCHCONTENT_QUIET FALSE)

    # Populate the cmocka content at configuration.
    FetchContent_Declare(
        cmocka
        GIT_REPOSITORY https://github.com/clibs/cmocka.git
        GIT_TAG cmocka-1.1.5
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL)

    # Enable cmocka static build.
    set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)

    # Disable cmockery support for cmocka.
    set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)

    # Don't build cmocka examples.
    set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)

    # Don't build cmocka unit tests.
    set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)

    # Disable picky developer options.
    set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)

    # Make cmocka available to the project.
    FetchContent_MakeAvailable(cmocka)


    # Make an alias for the cmocka and cmocka-static based on build type
    # to be compatible when cmocka already exists in the system path
    # instead being fetched.
    if (BUILD_SHARED_LIBS)
        set(CMOCKA_LIBRARY cmocka)
    else ()
        set(CMOCKA_LIBRARY cmocka-static)
    endif ()
endif ()