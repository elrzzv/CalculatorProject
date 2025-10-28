#include <iostream>
#include <string>
#include "calculator/calculator.h"

int main() {

    Calculator calculator;
    calculator.load_plugins(".");

    std::cout << "======== Calculator ========" << std::endl;
    std::cout << "Available operations: " << calculator.get_available_operators()<< std::endl;
    std::cout << "Available functions: " << calculator.get_available_functions()<< std::endl;
    std::cout << "Available constants: " << calculator.get_available_constants()<< std::endl;
    std::cout << "Enter an expression or 'exit' to exit" << std::endl;
    std::cout << "============================" << std::endl;

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") break;
        if (input.empty()) continue;

        try {
            const double result = calculator.calculate(input);
            std::cout << "> " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}