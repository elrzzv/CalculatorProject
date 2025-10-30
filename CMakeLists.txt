cmake_minimum_required(VERSION 3.20)
project(Calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Google Test
add_subdirectory(${CMAKE_BINARY_DIR}/googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_subdirectory(src)
add_subdirectory(plugins)

if(PLUGIN_TARGETS)
    add_dependencies(calc ${PLUGIN_TARGETS})
    message(STATUS "Plugin dependencies: ${PLUGIN_TARGETS}")
endif()

#google test
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
