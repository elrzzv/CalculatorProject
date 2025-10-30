#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <functional>

struct Token {
    enum Type { NUMBER, OPERATOR, FUNCTION, LEFT_PAREN, RIGHT_PAREN, COMMA, CONSTANT };
    Type type;
    std::string value;
    double number_value;

    explicit Token(const Type t, const std::string& v = "") : type(t), value(v), number_value(0) {}
    explicit Token(const double num) : type(NUMBER), number_value(num) {}
    explicit Token(const Type t, const std::string& name, const double val) : type(t), value(name), number_value(val) {}
};

struct OperatorInfo {
    std::function<double(double, double)> function;
    int priority;
    bool is_right_associative;
};

class ExpressionParser {
    std::map<std::string, std::function<double(double)>> functions;
    std::map<std::string, OperatorInfo> operators;
    std::map<std::string, double> constants;

    std::vector<Token> tokenize(const std::string& expression) const;
    std::vector<Token> infix_to_rpn(const std::vector<Token>& tokens);
    double evaluate_rpn(const std::vector<Token>& tokens);
    bool is_operator(char c) const;
    bool is_constant(const std::string& name) const;
    bool is_function(const std::string& str) const;
    bool is_unary_minus(const std::vector<Token>&tokens, size_t pos, const std::string& expression) const;

    int get_operator_priority(const std::string& op)const;
    bool is_right_associative(const std::string& op)const;

    double get_constant_value(const std::string& name)const;

public:
    ExpressionParser();

    double parse(const std::string& expression);
    void register_function(const std::string& name, const std::function<double(double)> &func);
    void register_operator(const std::string& op, const OperatorInfo& op_info);
    void register_constant(const std::string& name, const double value);

    std::vector<std::string> get_all_functions_names() const;
    std::vector<std::string> get_all_operators() const;
    std::vector<std::string> get_all_constants() const;
};

#endif //EXPRESSION_PARSER_H