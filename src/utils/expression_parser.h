#ifndef NAUKA_PROG_EXPRESSION_PARSER_H
#define NAUKA_PROG_EXPRESSION_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <functional>

struct Token {
    enum Type { NUMBER, OPERATOR, FUNCTION, LEFT_PAREN, RIGHT_PAREN, COMMA };
    Type type;
    std::string value;
    double number_value;

    explicit Token(const Type t, const std::string& v = "") : type(t), value(v), number_value(0) {}
    explicit Token(const double num) : type(NUMBER), number_value(num) {}
};

class ExpressionParser {
public:
    ExpressionParser();

    double parse(const std::string& expression);
    void register_function(const std::string& name, const std::function<double(double)> &func);
    std::string get_all_functions_names() const;

private:
    std::vector<Token> tokenize(const std::string& expression) const;
    std::vector<Token> infix_to_rpn(const std::vector<Token>& tokens);
    double evaluate_rpn(const std::vector<Token>& tokens);

    std::map<std::string, std::function<double(double)>> functions;
    std::map<std::string, int> operator_priority;

    bool is_operator(char c) const;
    bool is_function(const std::string& str) const;
    bool is_unary_minus(const std::vector<Token>&tokens, size_t pos, const std::string& expression) const;
};

#endif //NAUKA_PROG_EXPRESSION_PARSER_H