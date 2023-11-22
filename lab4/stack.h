#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

const int MAX_SIZE = 20; // the maximum amount our stack can hold since this is a bounded stack
template <typename T>
class stack
{
private:
    T data[MAX_SIZE]; // array of type T that represents our stack
    int size; // active end size

public:
    // constructs an empty stack.
    
    // Copy Constructor
    stack(const stack<T>& other)
    {
        size = other.size;
        for (int i = 0; i < size; i++) 
        {
            data[i] = other.data[i];
        }
    }

    // Copy Assignment Operator
    stack<T>& operator=(const stack<T>& other)
    {
        if (this != &other)
        {
        size = other.size;
            for (int i = 0; i < size; i++) 
            {
            data[i] = other.data[i];
            }
        }
        return *this;
    }
    stack()
    {
        size = 0;
    }
    
    // Destructor
    ~stack() 
    {}

    // removes last element in stack in O(1) time
    void pop()
    {
        if (empty()) // if the stack is empty we need to account for underflow
        {                                                     
            throw out_of_range("Called pop on empty stack."); // throw an out of range error
        }
        else
        { // otherwise we want to decrement the size, which removes the last element
            size--;
        }
    }

    // removes the last two elements on top of the stack in O(1) time
    void pop_two()  // this is a void function since we have a top function that returns the top element
    {
        if (empty())
        { // if the size is 0 or 1 we want to throw an error since we cant pop 0 elements twice or pop one element twice
            throw out_of_range("Called pop_two on an empty stack.");
        }

        else if (size == 1) // if the size is 1 we want to throw an out of range error since we can't pop 2
        {
            throw out_of_range("Called pop_two on a stack of size 1.");
        }
        else // if it isn't any of those two cases we can pop two off the stack
        {
            pop(); // call pop once
            pop(); // call it twice since we want to remove the two elements at the top of the stack
        }
    }

    // returns the element at the top of the stack, last inserted element
    T top()
    {
        if (empty())
        {
            throw underflow_error("Called top on empty stack."); // throw underflow error
        }
        else
        {
            return data[size - 1]; // return the last element
        }
    }

    // function to check to see if stack is empty, helper function for range checking and throwing exceptions
    bool empty() const
    {
        return (size == 0); // this is converted to a boolean and returns true of size is 0
    }

    // inserts a value of type T to the top of the stack in O(1) time
    void push( const T& val)
    {
        if (size == MAX_SIZE)
        {                                                       // if the size is 20 we know there will be overflow
            throw overflow_error("Called push on full stack."); // throw and overflow_error exception message
        }
        else
        {
            data[size++] = val; // otherwise we increment the size of the array and at that index we insert val
        }
    }
};