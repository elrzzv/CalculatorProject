#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <windows.h>

// Простейший калькулятор пока без плагинов
class SimpleCalculator {
public:
    SimpleCalculator() {
        // Базовые операции
        functions["+"] = [](const double a, const double b) { return a + b; };
        functions["-"] = [](const double a, const double b) { return a - b; };
        functions["*"] = [](const double a, const double b) { return a * b; };
        functions["/"] = [](const double a, const double b) {
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        };
    }

    double calculate(const std::string& expression) {
        // Пока просто эмулируем вычисление 2+2
        std::cout << "Calculating: " << expression << std::endl;
        return 4.0; // Заглушка
    }

private:
    std::map<std::string, std::function<double(double, double)>> functions;
};

int main() {
    SimpleCalculator calc;
    std::string input;

    std::cout << "The calculator is running! Enter an expression or 'exit' to exit." << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        try {
            double result = calc.calculate(input);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}