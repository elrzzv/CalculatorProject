#include <cmath>

extern "C" {
    //бинарная операция: a ^ b
    __declspec(dllexport) double execute_operator(double a, double b) {
        return std::pow(a, b);
    }
    
    __declspec(dllexport) const char* get_operator_name() {
        return "^";
    }
    
    __declspec(dllexport) int get_priority() {
        return 3;
    }
    
    __declspec(dllexport) bool is_right_associative() {
        return true;
    }
}