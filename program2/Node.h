#pragma once

#include <iostream>
using namespace std;


class Node {
 public:
    string data;
    int count;
    Node* left;
    Node* right;    
    Node(const string &newString): data(newString), count(1), left(nullptr), right(nullptr){} 


};

