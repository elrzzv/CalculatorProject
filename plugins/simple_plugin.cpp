
#include <cmath>

// Простейшая функция - квадрат числа
extern "C" {
    __declspec(dllexport) double execute(double x) {
        return x * x;
    }

    __declspec(dllexport) const char* get_function_name() {
        return "square";
    }
}