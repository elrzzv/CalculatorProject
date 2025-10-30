#include <cmath>

extern "C" {
    __declspec(dllexport) double execute(double x) {
        return std::cos(x);
    }
    
    __declspec(dllexport) const char* get_function_name() {
        return "cos";
    }
}