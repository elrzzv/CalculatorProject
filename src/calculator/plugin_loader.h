#ifndef PLUGIN_LOADER_H
#define PLUGIN_LOADER_H

#include <string>
#include <map>
#include <functional>
#include <windows.h>
#include "utils/expression_parser.h"

class PluginLoader {
public:
    PluginLoader() = default;
    ~PluginLoader();

    void load_plugins(const std::string& plugins_dir);
    void register_function(const std::string& name, std::function<double(double)> func);
    void register_operator(const std::string& name, const std::function<double(double, double)> &func,
                          int precedence, bool is_right_associative = false);

    std::map<std::string, std::function<double(double)>> get_functions() const;
    std::map<std::string, OperatorInfo> get_operators() const;

    void unload_all_plugins();

private:
    void load_single_plugin(const std::string& dll_path);
    bool directory_exists(const std::string& path);

    std::map<std::string, std::function<double(double)>> loaded_functions;
    std::map<std::string, OperatorInfo> loaded_operators;
    std::map<std::string, HINSTANCE> loaded_libraries;
};


#endif //PLUGIN_LOADER_H