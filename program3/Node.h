#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

  friend class Tree;

public: 
  Node(const string &_small) : small(_small), large(""), keyCount(1), // small represents the A key, large represents B key. Always insert at small        
                               left(nullptr), right(nullptr), parent(nullptr)
                          
  { 
  }

private:
  string small;
  string large;
  int keyCount;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

};

#endif