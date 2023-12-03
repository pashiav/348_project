#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*

This is the main file that executes the function. It displays a description of the program before
running the calculation portion, allowing for the user to input an expression to be solved.

*/

int main() {
    string str;  // Define the input string.

    // Introduction paragraph
    cout << "Welcome to M.A.R.C.O.!" << endl
         << "M.A.R.C.O. is a terminal calculator that can handle simple maths." << endl
         << "It can use +, -, *, \\, and % operators, as well as parentheses, and calculates using PEMDAS." << endl
         << "For more detailed instructions, please look at the user manual in the docs folder." << endl << endl;

    // Beginning of program.
    while (1) {
        // Prompt the user to enter an equation
        cout << "Enter an equation to be solved: ";
        getline(cin, str);

        // TODO: Solve the equation.
    }

    // End of program.
    return 0;
}
