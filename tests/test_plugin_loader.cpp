#include <gtest/gtest.h>
#include "../src/calculator/plugin_loader.h"

class PluginLoaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        loader = std::make_unique<PluginLoader>();
    }

    void TearDown() override {
        loader->unload_all_plugins();
        loader.reset();
    }

    std::unique_ptr<PluginLoader> loader;
};

TEST_F(PluginLoaderTest, LoadNonExistentDirectory) {
    EXPECT_NO_THROW(loader->load_plugins("non_existent_directory"));
}

TEST_F(PluginLoaderTest, RegisterAndGetFunctions) {
    // Тест регистрации функций
    auto test_func = [](const double x) { return x * 2; };
    loader->register_function("test_double", test_func);
    
    auto functions = loader->get_functions();
    EXPECT_TRUE(functions.contains("test_double"));
    EXPECT_DOUBLE_EQ(functions["test_double"](5.0), 10.0);
}