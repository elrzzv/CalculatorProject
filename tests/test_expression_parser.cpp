#include <cmath>
#include <gtest/gtest.h>
#include "../src/utils/expression_parser.h"

class ExpressionParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        parser = std::make_unique<ExpressionParser>();

        //регистрируем функции и оператор для тестов
        parser->register_function("sin", [](const double x) { return std::sin(x); });
        parser->register_function("cos", [](const double x) { return std::cos(x); });
        parser->register_function("ln", [](const double x) {
            if (x <= 0) throw std::runtime_error("Logarithm of non-positive number");
            return std::log(x);
        });

        parser->register_function("sqrt", [](const double x) {
            if (x < 0) throw std::runtime_error("Square root of negative number");
            return std::sqrt(x);
        });

        parser->register_function("exp", [](const double x) {return std::exp(x); });
        parser->register_function("abs", [](const double x) {return std::abs(x); });

        parser->register_operator("^", {
            [](const double x, const double y) { return std::pow(x, y);},
                3, true
        });
    }

    void TearDown() override {
        parser.reset();
    }

    std::unique_ptr<ExpressionParser> parser;
};

//тест базовых операций
TEST_F(ExpressionParserTest, BasicOperations) {
    EXPECT_DOUBLE_EQ(parser->parse("2 + 3"), 5.0);
    EXPECT_DOUBLE_EQ(parser->parse("5 - 3"), 2.0);
    EXPECT_DOUBLE_EQ(parser->parse("2 * 3"), 6.0);
    EXPECT_DOUBLE_EQ(parser->parse("6 / 3"), 2.0);
    EXPECT_DOUBLE_EQ(parser->parse("2 ^ 3"), 8.0);
}

//тест приоритета операторов
TEST_F(ExpressionParserTest, OperatorPrecedence) {
    EXPECT_DOUBLE_EQ(parser->parse("2 + 3 * 4"), 14.0);
    EXPECT_DOUBLE_EQ(parser->parse("(2 + 3) * 4"), 20.0);
    EXPECT_DOUBLE_EQ(parser->parse("2 ^ 2 ^ 2 + 3"), 19.0);
}

//тест функций
TEST_F(ExpressionParserTest, Functions) {
    EXPECT_NEAR(parser->parse("sin(0)"), 0.0, 1e-10);
    EXPECT_NEAR(parser->parse("cos(0)"), 1.0, 1e-10);
    EXPECT_NEAR(parser->parse("ln(1)"), 0.0, 1e-10);
    EXPECT_NEAR(parser->parse("sqrt(9)"), 3.0, 1e-10);
    EXPECT_NEAR(parser->parse("exp(0)"), 1.0, 1e-10);
    EXPECT_NEAR(parser->parse("abs(-1)"), 1.0, 1e-10);
}

//тест констант
TEST_F(ExpressionParserTest, Constants) {
    EXPECT_NEAR(parser->parse("sin(PI)"), 0.0, 1e-10);
    EXPECT_NEAR(parser->parse("cos(PI)"), -1.0, 1e-10);
    EXPECT_DOUBLE_EQ(parser->parse("2 * PI"), 2 * 3.14159265358979323846);
}

//тест ошибок
TEST_F(ExpressionParserTest, ErrorHandling) {
    EXPECT_THROW(parser->parse("2 / 0"), std::runtime_error);
    EXPECT_THROW(parser->parse("ln(0)"), std::runtime_error);
    EXPECT_THROW(parser->parse("sqrt(-1)"), std::runtime_error);
    EXPECT_THROW(parser->parse("unknown_func(5)"), std::runtime_error);
    EXPECT_THROW(parser->parse("2 + "), std::runtime_error);
}