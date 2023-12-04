#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

#include "MyInfixCalculator.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Introduction paragraph
    cout << "Welcome to M.A.R.C.O.!\n"
         << "M.A.R.C.O. is a terminal calculator that can handle simple maths.\n"
         << "It can use +, -, *, \\, and % operators, as well as parentheses, and calculates using PEMDAS.\n"
         << "For more detailed instructions, please look at the user manual in the docs folder.\n\n";

    string str;

    while (1) { // While loop for continual use.
        // Prompt the user to enter an equation
        cout << "Enter an equation to be solved: ";
        getline(cin, str);

        // Create an instance of MyInfixCalculator
        MyInfixCalculator infix_calculator;

        // Calculate the result of the infix equation
        double result = infix_calculator.calculate(str);

        // Set precision for displaying the result
        cout.precision(3);

        // Display the calculated result
        cout << fixed << "Result: " << result << endl;
    }

    return 0;
}
