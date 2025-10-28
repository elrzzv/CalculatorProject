#include "plugin_loader.h"
#include <iostream>
#include <filesystem>

using ExecuteFunc = double (*)(double);
using GetNameFunc = const char* (*)();

using ExecuteOperatorFunc = double (*)(double, double);
using GetPriorityFunc = int (*)();
using IsRightAssociativeFunc = bool (*)();

PluginLoader::~PluginLoader() {
    unload_all_plugins();
}

void PluginLoader::load_plugins(const std::string& plugins_dir) {
    if (!directory_exists(plugins_dir)) {
        std::cout << "Plugins directory not found: " << plugins_dir << std::endl;
        return;
    }

    std::cout << "Loading plugins from: " << plugins_dir << std::endl;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(plugins_dir)) {
            if (entry.path().extension() == ".dll") {
                load_single_plugin(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    std::cout << "Loaded " << loaded_functions.size() << " functions and "
                  << loaded_operators.size() << " operators" << std::endl;}

void PluginLoader::load_single_plugin(const std::string& dll_path) {
    const HINSTANCE dll_handle = LoadLibraryA(dll_path.c_str());
    if (!dll_handle) {
        std::cerr << "Cannot load DLL: " << dll_path << " (Error: " << GetLastError() << ")" << std::endl;
        return;
    }

    //указатели из DLL
    //пробуем загрузить как функцию
    const auto get_func_name = reinterpret_cast<GetNameFunc>(GetProcAddress(dll_handle, "get_function_name"));
    const auto execute_func = reinterpret_cast<ExecuteFunc>(GetProcAddress(dll_handle, "execute"));
    //пробуем загрузить как оператор
    const auto get_operator_name = reinterpret_cast<GetNameFunc>(GetProcAddress(dll_handle, "get_operator_name"));
    const auto execute_operator = reinterpret_cast<ExecuteOperatorFunc>(GetProcAddress(dll_handle, "execute_operator"));
    const auto get_priority = reinterpret_cast<GetPriorityFunc>(GetProcAddress(dll_handle, "get_priority"));
    const auto is_right_associative = reinterpret_cast<IsRightAssociativeFunc>(GetProcAddress(dll_handle, "is_right_associative"));

    if (get_func_name && execute_func) {
        //это функция
        try {
            const std::string func_name = get_func_name();
            register_function(func_name, execute_func);
            loaded_libraries[func_name] = dll_handle;
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading function from " << dll_path << ": " << e.what() << std::endl;
            FreeLibrary(dll_handle);
        }
    }
    else if (get_operator_name && execute_operator && get_priority) {
        //это оператор
        try {
            std::string op_name = get_operator_name();
            int priority = get_priority();
            bool is_right_assoc = is_right_associative();
            register_operator(op_name, execute_operator, priority, is_right_assoc);
            loaded_libraries[op_name] = dll_handle;
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading operator from " << dll_path << ": " << e.what() << std::endl;
            FreeLibrary(dll_handle);
        }
    }
    else{
        std::cerr << "Invalid plugin (missing required functions): " << dll_path << std::endl;
        FreeLibrary(dll_handle);
    }
}

void PluginLoader::register_function(const std::string& name, std::function<double(double)> func) {
    if (loaded_functions.contains(name)) {
        std::cout << "Warning: Function '" << name << "' already exists, replacing..." << std::endl;
    }
    loaded_functions[name] = func;
}

void PluginLoader::register_operator(const std::string& name, const std::function<double(double, double)> &func,
                                   const int precedence, const bool is_right_associative) {
    if (loaded_operators.contains(name)) {
        std::cout << "Warning: Operator '" << name << "' already exists, replacing..." << std::endl;
    }
    loaded_operators[name] = {func, precedence, is_right_associative};
}

std::map<std::string, std::function<double(double)>> PluginLoader::get_functions() const {
    return loaded_functions;
}

std::map<std::string, OperatorInfo> PluginLoader::get_operators() const {
    return loaded_operators;
}

void PluginLoader::unload_all_plugins() {
    std::cout << "Unloading all plugins..." << std::endl;
    for (auto& [name, handle] : loaded_libraries) {
        if (handle) {
            FreeLibrary(handle);
            std::cout << "Unloaded: " << name << std::endl;
        }
    }
    loaded_libraries.clear();
    loaded_functions.clear();
    loaded_operators.clear();
}

bool PluginLoader::directory_exists(const std::string& path) {
    const DWORD attrib = GetFileAttributesA(path.c_str());
    return (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY));
}