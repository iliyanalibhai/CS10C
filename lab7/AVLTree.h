#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Node.h"


using namespace std;

class AVLTree {
    public:    
        AVLTree() : root(nullptr) {} // initialize an empty tree 
        void insert(const string &);
        int balanceFactor(Node* ); // returns balance factor of a given node
        void printBalanceFactors(); // Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.
        void visualizeTree(const string &);
    private:
        Node* root;
        void rotate(Node* ); // Implement four possible imbalance cases and update the parent of the given node
        void rotateLeft(Node *); // Rotate the subtree to left at the given node and returns the new subroot
        void rotateRight(Node *); // Rotate the subtree to right at the given node and returns the new subroot
        void setChild(Node *, const string &, Node* ); //private helper to set parameter's parent's left/right to its child 
        void replaceChild(Node* , Node* , Node* ); // private helper to replace the child of a parent 
        void printBalanceFactors(Node *);  
        int height(Node *);
        void visualizeTree(ofstream &, Node *);

        
};

#endif