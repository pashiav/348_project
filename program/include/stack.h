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
        void pop();  // Pop from stack.
        char peek();  // Peek at top of stack.
        int sizeOf();  // Return size of the stack currently.
        bool isEmpty();  // Check if the stack is empty.
        bool isFull();  // Check if the stack is full.

    private:
        char *arr;  // Pointer for the address of an array.
        int top = -1;  // Keeps track of the top in the array. Default is set to -1, for an empty stack.
        int stacksize = 99;  // How big the stack array is. The stack can hold up to 99 characters.
};

#endif // STACK_H
