#include "Heap.h"
#include <iostream>
#include <algorithm>
using namespace std;



// constructing an empty heap
Heap::Heap() {
	numItems = 0;
}

// Destructor
Heap::~Heap() {
    while (numItems > 0) {
        delete arr[numItems - 1];
        --numItems;
    }
}

// Copy constructor
Heap::Heap(const Heap& other) {
    numItems = other.numItems;
    for (int i = 0; i < numItems; ++i) {
        arr[i] = new PrintJob(*other.arr[i]);
    }
}

// Copy assignment operator
Heap& Heap::operator=(const Heap& other) {
    if (this != &other) { // Check for self-assignment
        // Delete existing items in the array
        for (int i = 0; i < numItems; ++i) {
            delete arr[i];
        }

        // Copy the number of items
        numItems = other.numItems;

        // Copy each PrintJob using its copy constructor
        for (int i = 0; i < numItems; ++i) {
            arr[i] = new PrintJob(*other.arr[i]);
        }
    }
    return *this;
}


void Heap::percolateUp(int nodeIndex, PrintJob* heapArray[]) { // referenced zybooks algorithim
    while (nodeIndex > 0) {
        int parentIndex = (nodeIndex - 1) / 2;
        // check if the priority of the current node is less than or equal to its parent's priority
        if(heapArray[nodeIndex]->getPriority() <= heapArray[parentIndex]->getPriority()){ 
            // if it is, the max-heap property is not violated, so we can stop here
            return;
        }
        else{
             // if the current node has a higher priority than its parent, we need to swap them
        swap(heapArray[nodeIndex],heapArray[parentIndex]);
        // Update the current node index to its new position (the former parent index)
        nodeIndex = parentIndex;
        }
   }
}
// prints the heap based on highest priority
void Heap::print(){
    //if heap is empty
    if(numItems <= 0){
        throw runtime_error("empty"); // throw runtime error 
    }
    else{ // otherwise we want to print based on priority
   
        cout << "Priority: " << highest()->getPriority() << ", "
            << "Job Number: " << highest()->getJobNumber() << ", "
            << "Number of Pages: " << highest()->getPages() << endl;
    }
}

// Inserts a PrintJob to the heap without violating max-heap properties.
void Heap::enqueue (PrintJob* itemToAdd){
    if(numItems >= MAX_HEAP_SIZE){ // if we are going to cause overflow, we must handle it
        // throw runtime_error("out of range");
    }
    else{
        // add item in the array and then call percolate up private helper to fix order of priority
        arr[numItems] = itemToAdd;
        percolateUp(numItems, arr);
        ++numItems;
    }
} 


PrintJob* Heap::highest() const{
    if(numItems > 0){ //if more than 0 items return the first
        return arr[0];
    }
    else{ //edge case
        return nullptr;
    }
}


void Heap::trickleDown(int nodeIndex){ // referenced zybooks trickleDown algorithim
    int childIndex = 2 * nodeIndex + 1;
    PrintJob* value = arr[nodeIndex];

    while (childIndex < numItems) {
        // Find the max among the node and all the node's children
        PrintJob* maxValue = value;
        int maxIndex = -1;
        for (int i = 0; i < 2 && i + childIndex < numItems; i++) {
            if (arr[i + childIndex] > maxValue) {
                maxValue = arr[i + childIndex];
                maxIndex = i + childIndex;
            }
        }
        //exit if already sorted
        if (maxValue == value) {
            return;
        }
        //otherwise swap to maintain max heap property
        else {
            swap (arr[nodeIndex],arr[maxIndex]);
            nodeIndex = maxIndex;
            childIndex = 2 * nodeIndex + 1;
        }
    }

}

void Heap::dequeue(){
    if(numItems < 1 ){ // if there are no items we can't dequeue anything
        // throw runtime_error("attempting to remove less than 1 item");
    }
    if(numItems == 1){// if there is only one item it will be the first item in the array
        arr[0] = nullptr; // set to null
        --numItems; // decrement the size
    }
    if(numItems > 1){ //more than one
        int lastIndex = numItems - 1; 
        swap(arr[0], arr[lastIndex]);  // swap first and last element
        --numItems;  // decrement size
        trickleDown(0); // fix the order with private helper
    }
}