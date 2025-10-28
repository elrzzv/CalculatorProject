#include "calculator.h"
#include <iostream>
#include <cmath>
#include <filesystem>


void Calculator::load_plugins(const std::string& plugins_dir) {

    plugin_loader.load_plugins(plugins_dir);

    auto functions = plugin_loader.get_functions();
    for (const auto& [name, func] : functions) {
        parser.register_function(name, func);
    }

    auto operators = plugin_loader.get_operators();
    for (const auto& [name, op_info] : operators) {
        parser.register_operator(name, op_info);
    }
}

double Calculator::calculate(const std::string& expression) {
    if (expression.empty()) {
        throw std::runtime_error("Empty expression");
    }
    return parser.parse(expression);
}

std::string Calculator::get_available_functions() const {
    const auto names = parser.get_all_functions_names();
    std::string total;
    if (names.empty()) return total;
    for (auto it= names.begin(); it != --names.end(); ++it) {
        total += (*it) + ", ";
    }
    total+= names.back();
    return total;
}

std::string Calculator::get_available_operators() const {
    const auto ops = parser.get_all_operators();
    std::string total;
    if (ops.empty()) return total;
    for (auto it= ops.begin(); it != --ops.end(); ++it) {
        total += (*it) + ", ";
    }
    total += ops.back();
    return total;
}

std::string Calculator::get_available_constants() const {
    const auto cnst = parser.get_all_constants();
    std::string total;
    if (cnst.empty()) return total;
    for (auto it= cnst.begin(); it != --cnst.end(); ++it) {
        total += (*it) + ", ";
    }
    total += cnst.back();
    return total;
}

void Calculator::register_function(const std::string& name, const std::function<double(double)> &func) {
    parser.register_function(name, func);
}