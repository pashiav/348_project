#ifndef MY_INFIX_CALCULATOR_H
#define MY_INFIX_CALCULATOR_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <stdexcept>

#include "MyStack.h"
#include "MyVector.h"

using namespace std;

/*
The infix calculator is the main program. An instance is created when the program is run.
All calculations are done within this program, with the help of MyStack and MyVector.

The infix calculator works by taking the user input, turning it into postfix notation and then calculating using postfix.
*/

class MyInfixCalculator {
public:
    MyInfixCalculator() {}

    ~MyInfixCalculator() {}

    // Calculate the result of the given input.
    double calculate(const string &s) {
        if (s.empty()) {
            throw invalid_argument("Empty input string."); // Empty string error
        }
        MyVector<string> infix_tokens;  // Creates a string for the raw user input
        MyVector<string> postfix_tokens;  // Creates the postfix string for proper handling
        tokenize(s, infix_tokens);  // Create tokens for the infix
        infixToPostfix(infix_tokens, postfix_tokens);  // Turn it into postfix tokens
        return calPostfix(postfix_tokens);  // Calculate using the postfix
    }

private:
    // Operator precedence.
    int operatorPrec(const string &op) const {
        if (op == "^" || op == "**")
            return 1;
        else if (op == "*" || op == "/" || op == "%")
            return 2;
        else if (op == "+" || op == "-")
            return 3;
        else
            return -1; // invalid operator
    }

    // Checks for valid parentheses.
    bool isValidParenthesis(const char c) const {
        return (c == '(' || c == ')');
    }

    // Validates whether something is/isn't a digit (0-9).
    bool isDigit(const char c) const {
        return (c >= '0' && c <= '9');
    }

    // Does the base computations.
    double computeBinaryOperation(const double o1, const double o2, const string &opt) const {
        cout << "o1: " << o1 << "; operator: " << opt << "; o2: " << o2 << endl; // TODO: remove. here for validation.

        if (opt == "^" || opt == "**")  // Exponent
            return pow(o1, o2);
        else if (opt == "*")  // Multiplication
            return o1 * o2;
        else if (opt == "/") {  // Division
            if (o2 == 0) {
                throw invalid_argument("Division by zero.");
            }
            return o1 / o2;
        } else if (opt == "%") { // Modulo
            if (o2 == 0) {
                throw invalid_argument("Modulo by zero.");
            }
            return fmod(o1, o2);
        } else if (opt == "+") {  // Addition
            return o1 + o2;
        }
        else if (opt == "-") {  // Subtraction
            return o1 - o2;
        }
        else {
            throw invalid_argument("Unrecognized operator.");  // TODO: Need to add a validation for non-digit nor operand characters + if possible, print what the unrecognized operator was.
        }
    }

    // Tokenizes the user input, pushing it into a vector (TODO: Unsure about this explanation; SWE please adjust this comment so it's more descriptive)
    void tokenize(const string &s, MyVector<string> &tokens) {
        string current_token = "";
        bool expecting_operator = false;

        // For loop to iterate over the string.
        for (size_t i = 0; i < s.size(); i++) {
            char c = s[i];  // Keeps the character in the string we're currently on.

            // Handle digits and decimals
            if (isDigit(c) || (c == '.' && !current_token.empty() && isDigit(current_token.back()))) {
                printf("In digits\n");
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
                    tokens.push_back("-1");
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

                tokens.push_back(string(1, c));
                expecting_operator = true;
            }
        }

        // Add the last token if not empty
        if (!current_token.empty()) {
            tokens.push_back(current_token);
        }
    }

    // Converts the infix input to postfix.
    void infixToPostfix(MyVector<string> &infix_tokens, MyVector<string> &postfix_tokens) {
        MyStack<string> operator_stack;
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

    // Calculates the result using postfix notation.
    double calPostfix(const MyVector<string> &postfix_tokens) const {
        MyStack<double> operand_stack;
        for (const auto &token : postfix_tokens) {
            if (isDigit(token[0])) {
                operand_stack.push(stod(token));
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
