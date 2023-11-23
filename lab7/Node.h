#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

struct Node {
    string data;
    Node *parent;
    Node *left;
    Node *right;
    // constructor
    Node (const string& value) : data(value), parent(nullptr), left(nullptr), right(nullptr) {}
};

#endif