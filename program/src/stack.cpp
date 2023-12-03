#include "stack.h"

/*
    Stack.cpp contains all of the functions for the stack.
*/

// Stack constructor. Creates the array for the stack to use.
Stack::Stack()
{
    char arr[stacksize];
}


// Stack destructor. Deletes the allocated memory.
Stack::~Stack()
{
    delete[] arr;
}
