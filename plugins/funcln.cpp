#include <cmath>
#include <stdexcept>

extern "C" {
    __declspec(dllexport) double execute(double x) {
        if (x <= 0) {
            throw std::runtime_error("Natural logarithm of non-positive number");
        }
        return std::log(x);
    }
    
    __declspec(dllexport) const char* get_function_name() {
        return "ln";
    }
}
