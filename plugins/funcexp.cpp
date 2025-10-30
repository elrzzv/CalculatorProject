#include <cmath>

extern "C" {
    __declspec(dllexport) double execute(const double x) {
        return std::exp(x);
    }
    
    __declspec(dllexport) const char* get_function_name() {
        return "exp";
    }
}