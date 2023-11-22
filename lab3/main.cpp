#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>

using namespace std;

// function template declaration
template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index);
template <typename T>
void selection_sort(vector<T> &vals);
template <typename T>
T getElement(vector<T> &vals, int index);
vector<char> createVector();

int main()
{
    // testing with a vector of ints
    vector<int> nums;
    nums.push_back(8);
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(6);
    nums.push_back(10);
    nums.push_back(5);

    unsigned vectorResult = min_index(nums, 0);

    cout << "The minimum value of a vector of Ints is at index: " << vectorResult << endl;

    // testing with a vector of chars
    vector<char> chars;
    chars.push_back('c');
    chars.push_back('e');
    chars.push_back('f');
    chars.push_back('o');
    chars.push_back('b');
    chars.push_back('t');

    unsigned charResult = min_index(chars, 0);
    
    cout << "The minimum value of a vector of Ints is at index: " << charResult << endl;

    cout << "The unsorted vector of <ints> is" << endl;
    for (unsigned i = 0; i < nums.size(); i++)
    {
        cout << nums.at(i) << " ";
    }
    cout << endl;
    cout << "Sorted vector of <ints>" << endl;
    selection_sort(nums);
    for (unsigned i = 0; i < nums.size(); i++)
    {
        cout << nums.at(i) << " ";
    }
    return 0;
}

// finding the min value's index starting at index passed in
template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index)
{

    if (vals.empty()) // use the vector classes empty function to check if the vector passed in was empty
    {
        throw runtime_error("Vector is empty"); // if it is empty we throw the following exception
    }

    unsigned min = index; // variable to store the index passed in

    for (unsigned i = index; i < vals.size(); i++) // iterate from the index passed in till the end of val
    {
        if (vals[i] < vals[min]) // if the value at index i is less than the value at the min
        {
            min = i; // then the min is the index at i
        }
    }

    return min;
}

// selection sort to sort the vector using the min_index function as a helper function
template <typename T>
void selection_sort(vector<T> &vals)
{
    try
    {
        if (vals.empty()) // if vals is empty we want to throw an error
        {
            throw runtime_error("Vector is empty");
        }
        // selection sort algorithim
        // elements to the left of i are sorted
        for (unsigned i = 0; i < vals.size() - 1; ++i) // iterate until the 2nd to last element
        {
            unsigned smallestIndex = min_index(vals, i); // we start with the smallest index and start comparing to that index
            T placeHolder = vals[smallestIndex]; // placeholder holds the value of the smallest index
            vals[smallestIndex] = vals[i]; 
            vals[i] = placeHolder;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

// function to getElemeent of a vector in O(1) time
template <typename T>
T getElement(vector<T> &vals, int index)
{
    if (index < 0 || unsigned(index) > vals.size()) // if index passed in is less than 0, or greater than size, we throw an error message
    {
        throw out_of_range("out of range exception occured");
        cout << endl;
    }

    return vals.at(index);
}

// function to create a vector of a random size up to 26 to help with the testing of getElement()
vector<char> createVector() 
{
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for (int i = 0; i < vecSize; i++) // iterate till the end of the random size
    {
        vals.push_back(c); // pushback values in the vector
        c++; // iterate the char to get the next char
    }
    return vals; // return the vector
}
