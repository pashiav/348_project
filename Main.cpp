#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

#include "MyInfixCalculator.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    string str;

    // Prompt the user to enter an equation
    cout << "Enter an equation to be solved: "; 
    cin >> str; 

    // Create an instance of MyInfixCalculator
    MyInfixCalculator infix_calculator;
    
    // Calculate the result of the infix equation
    double result = infix_calculator.calculate(str);

    // Set precision for displaying the result
    std::cout.precision(3);

    // Display the calculated result
    cout << std::fixed << "Result: " << result << endl;

    return 0;
}
