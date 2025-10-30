#include <cmath>
#include <stdexcept>

extern "C" {
    __declspec(dllexport) double execute(const double x) {
        if (x < 0) {
            throw std::runtime_error("Square root of negative number");
        }
        return std::sqrt(x);
    }
    
    __declspec(dllexport) const char* get_function_name() {
        return "sqrt";
    }
}