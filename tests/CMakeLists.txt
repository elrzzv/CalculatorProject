add_executable(calculator_tests
        test_calculator.cpp
        test_expression_parser.cpp
        test_plugin_loader.cpp
)

target_sources(calculator_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src/utils/expression_parser.cpp
        ${CMAKE_SOURCE_DIR}/src/calculator/calculator.cpp
        ${CMAKE_SOURCE_DIR}/src/calculator/plugin_loader.cpp
)

target_include_directories(calculator_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

#Google Test
target_link_libraries(calculator_tests PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(calculator_tests
        DISCOVERY_MODE PRE_TEST
        TEST_PREFIX "TEST_"
        PROPERTIES LABELS "unit_tests"
)
set_target_properties(calculator_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/tests
)