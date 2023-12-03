#ifndef STACK_H
#define STACK_H

/*
    Header file for the stack. Contains all the function definitions and variable declarations.
    The stack is a data structure that uses an array to perform FILO based operations.
*/

class Stack
{
    public:
        Stack();  // Constructor
        ~Stack();  // Destructor

        void push(char);  // Push to stack.
        char pop();  // Pop from stack.
        char peek();  // Peek at top of stack.
        bool isEmpty();  // Check if the stack is empty.

    private:
        char *arr;  // Pointer for the address of an array.
        int top = -1;  // Keeps track of the top in the array. Default is set to -1, for an empty stack.
        int stacksize = 99;  // How big the stack array is. The stack can hold up to 99 characters.

};

#endif // STACK_H
