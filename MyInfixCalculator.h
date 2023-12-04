#ifndef MY_INFIX_CALCULATOR_H
#define MY_INFIX_CALCULATOR_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <stdexcept>

#include "MyStack.h"
#include "MyVector.h"

class MyInfixCalculator {
public:
    MyInfixCalculator() {}

    ~MyInfixCalculator() {}

    double calculate(const std::string &s) {
        if (s.empty()) {
            throw std::invalid_argument("Empty input string.");
        }
        MyVector<std::string> infix_tokens;
        MyVector<std::string> postfix_tokens;
        tokenize(s, infix_tokens);
        infixToPostfix(infix_tokens, postfix_tokens);
        return calPostfix(postfix_tokens);
    }

private:
    int operatorPrec(const std::string &op) const {
        if (op == "^" || op == "**")
            return 1;
        else if (op == "*" || op == "/" || op == "%")
            return 2;
        else if (op == "+" || op == "-")
            return 3;
        else
            return -1; // invalid operator
    }

    bool isValidParenthesis(const char c) const {
        return (c == '(' || c == ')');
    }

    bool isDigit(const char c) const {
        return (c >= '0' && c <= '9');
    }

    double computeBinaryOperation(const double o1, const double o2, const std::string &opt) const {
        if (opt == "^" || opt == "**")
            return std::pow(o1, o2);
        else if (opt == "*")
            return o1 * o2;
        else if (opt == "/") {
            if (o2 == 0) {
                throw std::invalid_argument("Division by zero.");
            }
            return o1 / o2;
        } else if (opt == "%") {
            if (o2 == 0) {
                throw std::invalid_argument("Modulo by zero.");
            }
            return std::fmod(o1, o2);
        } else if (opt == "+")
            return o1 + o2;
        else if (opt == "-")
            return o1 - o2;
        else {
            throw std::invalid_argument("Unrecognized operator.");
        }
    }

    void tokenize(const std::string &s, MyVector<std::string> &tokens) {
    std::string current_token = "";
    bool expecting_operator = false;

    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];

        // Handle digits and decimals
        if (isDigit(c) || (c == '.' && !current_token.empty() && isDigit(current_token.back()))) {
                current_token += c;
            }
        // Handle parentheses
        else if (isValidParenthesis(c)) {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token = "";
            }

            // Handle implicit multiplication and negative sign before parentheses
            if ((expecting_operator && c == '(') || (c == '(' && i > 0 && s[i - 1] == '-')) {
                tokens.push_back("*");
            }

            // Handle the negative sign before parentheses
            if (c == '(' && i > 0 && s[i - 1] == '-') {
                tokens.push_back("0");
                tokens.push_back("-");
                tokens.push_back("1");
                tokens.push_back("*");
            }

            expecting_operator = (c == '(');
        }
        // Handle '**' as an exponentiation operator
        else if (c == '*' && i < s.size() - 1 && s[i + 1] == '*') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token = "";
            }
            tokens.push_back("**");
            expecting_operator = true;
            i++; // skip the next character
        }
        // Handle whitespace
        else if (c == ' ') {
            continue;
        }
        // Handle other operators
        else {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token = "";
            }

            // Handle the negative sign as part of a number
                if (c == '-' && (i == 0 || (!isDigit(s[i-1]) && s[i-1] != ')'))) {  // CHANGES; negatives fix
                    current_token += '0';
                    tokens.push_back(current_token);
                    current_token = "";
                }


            tokens.push_back(std::string(1, c));
            expecting_operator = true;
        }
    }

    // Add the last token if not empty
    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }
}



    void infixToPostfix(MyVector<std::string> &infix_tokens, MyVector<std::string> &postfix_tokens) {
        MyStack<std::string> operator_stack;
        for (const auto &token : infix_tokens) {
            if (isDigit(token[0])) {
                postfix_tokens.push_back(token);
            } else if (token == "(") {
                operator_stack.push(token);
            } else if (token == ")") {
                while (!operator_stack.empty() && operator_stack.top() != "(") {
                    postfix_tokens.push_back(operator_stack.top());
                    operator_stack.pop();
                }
                operator_stack.pop();
            } else {
                while (!operator_stack.empty() && operatorPrec(operator_stack.top()) <= operatorPrec(token)) {
                    postfix_tokens.push_back(operator_stack.top());
                    operator_stack.pop();
                }
                operator_stack.push(token);
            }
        }
        while (!operator_stack.empty()) {
            postfix_tokens.push_back(operator_stack.top());
            operator_stack.pop();
        }
    }

    double calPostfix(const MyVector<std::string> &postfix_tokens) const {
        MyStack<double> operand_stack;
        for (const auto &token : postfix_tokens) {
            if (isDigit(token[0])) {
                operand_stack.push(std::stod(token));
            } else {
                double o2 = operand_stack.top();
                operand_stack.pop();
                double o1 = operand_stack.top();
                operand_stack.pop();
                operand_stack.push(computeBinaryOperation(o1, o2, token));
            }
        }
        return operand_stack.top();
    }
};

#endif // MY_INFIX_CALCULATOR_H