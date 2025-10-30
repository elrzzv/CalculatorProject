add_executable(calc
        main.cpp
        calculator/calculator.cpp
        calculator/plugin_loader.cpp
        utils/expression_parser.cpp
)


target_include_directories(calc PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)