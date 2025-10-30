#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <functional>
#include "../utils/expression_parser.h"
#include "plugin_loader.h"

class Calculator {
public:
    Calculator() = default;
    ~Calculator() = default;

    double calculate(const std::string& expression);

    void load_plugins(const std::string& plugins_dir );

    std::string get_available_functions() const;

    std::string get_available_operators() const;

    std::string get_available_constants() const;

    void register_function(const std::string& name, const std::function<double(double)> &func);

private:
    ExpressionParser parser;
    PluginLoader plugin_loader;
};

#endif //CALCULATOR_H