#include <gtest/gtest.h>
#include "../src/calculator/calculator.h"

class CalculatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        calculator = std::make_unique<Calculator>();
    }

    void TearDown() override {
        calculator.reset();
    }

    std::unique_ptr<Calculator> calculator;
};

TEST_F(CalculatorTest, BasicCalculation) {
    EXPECT_DOUBLE_EQ(calculator->calculate("2 + 2"), 4.0);
    EXPECT_DOUBLE_EQ(calculator->calculate("3 * 4"), 12.0);
}

TEST_F(CalculatorTest, ComplexExpressions) {
    EXPECT_DOUBLE_EQ(calculator->calculate("(2 + 3) * 4"), 20.0);
    EXPECT_DOUBLE_EQ(calculator->calculate("2 + 3 * 4"), 14.0);
}

TEST_F(CalculatorTest, EmptyExpression) {
    EXPECT_THROW(calculator->calculate(""), std::runtime_error);
}