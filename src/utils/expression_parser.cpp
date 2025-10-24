#include "expression_parser.h"

#include <cmath>
#include <sstream>
#include <cctype>
#include <stack>
#include <stdexcept>

ExpressionParser::ExpressionParser() {
    operator_priority["+"] = 1;
    operator_priority["-"] = 1;
    operator_priority["*"] = 2;
    operator_priority["/"] = 2;
    operator_priority["^"] = 3;

    //базовые функции
    functions["sqrt"] = [](const double x) -> double {
        if (x < 0) throw std::runtime_error("Square root of negative number");
        return sqrt(x);
    };
    functions["abs"] = [](const double x) -> double { return std::abs(x); };
}

void ExpressionParser::register_function(const std::string& name, const std::function<double(double)> &func) {
    functions[name] = func;
}

std::vector<Token> ExpressionParser::tokenize(const std::string& expression) const {
    std::vector<Token> tokens;
    std::stringstream ss(expression);
    char c;
    size_t pos = 0;

    while (ss >> c) {
        if (std::isspace(c)) {
            pos++;
            continue;
        }

        if (std::isdigit(c) || c == '.' || (c == '-' && is_unary_minus(tokens, pos, expression))) {
            //число
            std::string number_str;
            number_str += c;
            while (ss.peek() != EOF && (std::isdigit(ss.peek()) || ss.peek() == '.')) {
                number_str += static_cast<char>(ss.get());
            }
            tokens.emplace_back(std::stod(number_str));
        }
        else if (std::isalpha(c)) {
            //функция
            std::string name;
            name += c;
            while (ss.peek() != EOF && std::isalpha(ss.peek())) {
                name += static_cast<char>(ss.get());
            }
            tokens.emplace_back(Token::FUNCTION, name);
        }
        else if (c == '(') {
            tokens.emplace_back(Token::LEFT_PAREN, "(");
        }
        else if (c == ')') {
            tokens.emplace_back(Token::RIGHT_PAREN, ")");
        }
        else if (c == ',') {
            tokens.emplace_back(Token::COMMA, ",");
        }
        else if (is_operator(c)) {
            //оператор
            tokens.emplace_back(Token::OPERATOR, std::string(1, c));
        }

    }

    return tokens;
}

std::vector<Token> ExpressionParser::infix_to_rpn(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::stack<Token> stack;

    for (const auto& token : tokens) {
        switch (token.type) {
            case Token::NUMBER:
                output.push_back(token);
                break;

            case Token::FUNCTION:
                stack.push(token);
                break;

            case Token::OPERATOR: {
                while (!stack.empty() &&
                       stack.top().type == Token::OPERATOR &&
                       operator_priority[stack.top().value] >= operator_priority[token.value]) {
                    output.push_back(stack.top());
                    stack.pop();
                }
                stack.push(token);
                break;
            }

            case Token::LEFT_PAREN:
                stack.push(token);
                break;

            case Token::RIGHT_PAREN:
                while (!stack.empty() && stack.top().type != Token::LEFT_PAREN) {
                    output.push_back(stack.top());
                    stack.pop();
                }
                if (stack.empty()) throw std::runtime_error("Mismatched parentheses");
                stack.pop(); //убираем левую скобку
                if (!stack.empty() && stack.top().type == Token::FUNCTION) {
                    output.push_back(stack.top());
                    stack.pop();
                }
                break;

            case Token::COMMA:
                while (!stack.empty() && stack.top().type != Token::LEFT_PAREN) {
                    output.push_back(stack.top());
                    stack.pop();
                }
                if (stack.empty()) throw std::runtime_error("Misplaced comma");
                break;
        }
    }

    while (!stack.empty()) {
        if (stack.top().type == Token::LEFT_PAREN) {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(stack.top());
        stack.pop();
    }

    return output;
}

double ExpressionParser::evaluate_rpn(const std::vector<Token>& tokens) {
    std::stack<double> stack;

    for (const auto& token : tokens) {
        switch (token.type) {
            case Token::NUMBER:
                stack.push(token.number_value);
                break;

            case Token::OPERATOR: {
                if (stack.size() < 2) throw std::runtime_error("Not enough operands");
                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();

                if (token.value == "+") stack.push(a + b);
                else if (token.value == "-") stack.push(a - b);
                else if (token.value == "*") stack.push(a * b);
                else if (token.value == "/") {
                    if (b == 0) throw std::runtime_error("Division by zero");
                    stack.push(a / b);
                }
                else if (token.value == "^") stack.push(std::pow(a, b));
                break;
            }

            case Token::FUNCTION: {
                if (stack.empty()) throw std::runtime_error("No argument for function");
                const double arg = stack.top(); stack.pop();

                if (!functions.contains(token.value)) {
                    throw std::runtime_error("Unknown function: " + token.value);
                }
                stack.push(functions[token.value](arg));
                break;
            }

            default:
                throw std::runtime_error("Invalid token in evaluation");
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return stack.top();
}

double ExpressionParser::parse(const std::string& expression) {
    const auto tokens = tokenize(expression);
    const auto rpn = infix_to_rpn(tokens);
    return evaluate_rpn(rpn);
}

bool ExpressionParser::is_operator(const char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool ExpressionParser::is_function(const std::string& str) const {
    return functions.contains(str);
}

bool ExpressionParser::is_unary_minus(const std::vector<Token> &tokens, size_t pos, const std::string &expression) const {
    //минус унарный, если
    //1)это первый токен в выражении
    if (tokens.empty()) return true;

    //2)предыдущий токен - оператор или левая скобка
    const Token& last_token = tokens.back();
    return last_token.type == Token::OPERATOR ||
           last_token.type == Token::LEFT_PAREN ||
           last_token.type == Token::COMMA;
}


std::string ExpressionParser::get_all_functions_names() const {
    std::string total;
    for (auto it= functions.begin(); it != --functions.end(); ++it) {
        total += it->first + ", ";
    }
    total+= (--functions.end())->first;
    return total;
}
