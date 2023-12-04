#ifndef INFIXCALCULATOR_H
#define INFIXCALCULATOR_H

#include <string>

/*
    Header file for the infix calculator. Contains all the function definitions and variable declarations.
    The infix calculator converts the user's input to postfix before solving the equation.
*/

class InfixCalculator
{
    public:
        InfixCalculator(); // Constructor
        ~InfixCalculator();  // Deconstructor

    private:
        int operatorPrec(string opr);  // Operator precedence.
        void infixToPostfix(string ifin);  // Convert infix to postfix.
        double postfixCalc(string pfin);  // Calculate using postfix notation.

};

#endif // INFIXCALCULATOR_H
