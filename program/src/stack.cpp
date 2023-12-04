#include <stdio.h>
#include <stdexcept>
#include <iostream>

#include "stack.h"

using namespace std;

/*
    Stack.cpp contains all of the functions for the stack.
*/

// Stack constructor. Creates the array for the stack to use.
Stack::Stack()
{
    arr = new char[stacksize];
}


// Stack destructor. Deletes the allocated memory.
Stack::~Stack()
{
    delete[] arr;
}

// Check for empty stack.
bool Stack::isEmpty()
{
    return top == -1;
}

// Return current size of the stack.
int Stack::sizeOf()
{
    return top += 1;
}

// Check for full stack. Necessary to not run into array issues.
bool Stack::isFull()
{
    return top == stacksize - 1;
}

// Return the value at the top of the stack.
char Stack::peek()
{
    if(!isEmpty()) {
        return arr[top];
    }
    else {
        throw runtime_error("Attempted to peek at an empty stack.");
    }

}

// 'Pop' the top of the stack off.
void Stack::pop()
{
    if(!isEmpty()) {
        top -= 1;
    }
    else {
        throw runtime_error("Attempted to pop an empty stack.");
    }
}

// Push to the top of the stack
void Stack::push(char entry)
{
    if(!isFull()) {
        top += 1;
        arr[top] = entry;
    }
    else {
        throw runtime_error("Attempted to push to a full stack.");
    }
}
