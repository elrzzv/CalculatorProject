#include <iostream>
#include <string>
#include "utils/expression_parser.h"

int main() {
    ExpressionParser parser;

    std::cout << "The calculator is ready! Enter an expression or 'exit' to exit." << std::endl;
    std::cout << "Available functions: " << parser.get_all_functions_names() << std::endl;

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") break;
        if (input.empty()) continue;

        try {
            const double result = parser.parse(input);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}