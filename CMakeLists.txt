cmake_minimum_required(VERSION 3.20)
project(Calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)


#Google Test
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
    )

    #для Windows
    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
        set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    endif()

    FetchContent_MakeAvailable(googletest)
endif()


add_subdirectory(src)
add_subdirectory(plugins)

if(PLUGIN_TARGETS)
    add_dependencies(calc ${PLUGIN_TARGETS})
    message(STATUS "Plugin dependencies: ${PLUGIN_TARGETS}")
endif()

#google test
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
