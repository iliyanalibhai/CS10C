#include <iostream>
#include "Node.h"
#include "BSTree.h"
#include<stdexcept>

using namespace std;

using namespace std;
    

    // DECONSTRUCTOR
    BSTree::~BSTree() {
        Destructor(root); // calls private helper function
    }

    // private Destructor helper function
    void BSTree::Destructor(Node* curr) {
        if (curr == nullptr) { // edge case if tree is empty
            return;
        }
        Destructor(curr->left);
        Destructor(curr->right);
        delete curr;
    }
    // public memeber insert function
    void BSTree::insert(const string &newString) {
        insert(root,newString); // we first start with a recursive call starting with the root
        return;
    }

    // recursive private hleper function for insert
    void BSTree::insert(Node *&curr, const string &newString) { 
        if (!curr) {
        curr = new Node(newString);
        return;
        }

        if (curr->data < newString) { // if the current string we are looking at is less than the newString
            insert(curr->right,newString); // then we fix up current's right pointer and start looking at right subtree
        }
        else if (curr->data > newString) { // if the current string we are looking at is greater than the new string
            insert(curr->left, newString); // then we fix up the curr node's left child and start looking in the left subtree
        }
        else { // if the curr node's string and the newString are of the same value we just increment the count
            curr->count += 1;
        } 
    }

  
    bool BSTree::search(const string &key) const {
        if (root == nullptr) { // if the root node is empty 
            return false; // we return false since the key won't be in an empty tree
        }
        else { // other wise we start our recursive step
            return search(root,key);
        }
    }

    bool BSTree::search(const Node *curr, const string &key) const {
        
        if (curr ==  nullptr) {
            return false;
        }
        if (curr->data == key) { // if the node's string is equal to the string we are searching for 
            return true; // we return true
        }
        else if (curr->data > key) { // if the current node we are looking at is greater than the key we want to recursively search left
            return search(curr->left, key); // keep searching left
        }
        else { // if the current node we are looking at is less than the key, we want to recursivley search right
            return search(curr->right,key); // keep searching right
        }
        
    }
    
    void BSTree::remove(const string &newString) {
        root = remove(root, newString); //call recursive helper
    }
    Node* BSTree::remove(Node* curr, const string &key){
        if(curr == nullptr){ // base case
            return nullptr; 
        }

        if(key > curr->data){   // recursively remove the node from the right subtree
            curr->right = remove(curr->right, key);
            return curr;
        }
        else if(key < curr->data){ // recursively remove the node from the left subtree
            curr->left = remove(curr->left, key);
            return curr;
            
        }
        else{
            if(curr->count > 1){ // if there is a duplicate we decerement 
                curr->count -= 1; // decrement count
                return curr;
            }
            else{ 
                if(curr->left == nullptr && curr->right == nullptr){ // if the node has no children, delete the node
                    delete curr;   
                    return nullptr;
                }
                else if(curr->left == nullptr){ // // if the node only has a right child, replace the node with the right child
                    if(curr->data == "alpha") { // special case 
                        Node* victim = curr->right;
                        while(victim->left != nullptr){ // find the smallest node in the right subtree to replace the node
                            victim = victim->left;
                            }
                            curr->data = victim->data;
                            curr->count = victim->count;
                            curr->right = remove(curr->right, curr->data); // recursively call to delete if children
                            return curr;
                    }
                    Node *rightChild = curr->right;
                    delete curr;
                    return rightChild;
                }
                else{ // case where there is two children
                    // find the largest 
                    Node* victim = curr->left;
                    while(victim->right != nullptr){ // find the smallest node in the right subtree to replace the root node
                        victim = victim->right;
                    }
                    curr->data = victim->data; // swap payloads
                    curr->count = victim->count; // swap count
                    curr->left = remove(curr->left, curr->data); // recursively call to delete the duplicate
                    return curr;
                }
            }
        }
        
    }

    Node * BSTree::biggestInLeft(Node *curr) {
        while (curr->right) { // traverse right while not null
            curr = curr->right; // traverse right to find biggest node aka precessor
        }
        return curr;
    }
    
    // this function is a helper function for remove and returns the smallest node in right subtree
    Node * BSTree::smallestInRight(Node *curr) {
        while (curr->left) { // traverse while not null
            curr = curr->left; // we want to go left to find the smallest node
        }
        return curr; // return a pointer to the smallest node
    }



    // find the largest node (right most node in BST)
    string BSTree::largest() const {
        if (root == nullptr) { // if the tree is empty we return an empty string
            return ""; // empty string
        }
        else {
            return largest(root);
        }
    }
    // private helper function to find the rightmost node
    string BSTree::largest(const Node *curr) const {
        if (curr->right ==  nullptr) { // base case, if curr's right child is null we want to return curr since it was the right most node
            return curr->data; // return curr's data
        }
        else { // if there are still more right children we want to keep recursivley searching
            return largest(curr->right); // recursivley traverse right
        }
    }

    // find the smallest node in BST (left most node)
    string BSTree::smallest() const {
        if (root ==  nullptr) { // if the tree is empty we return an empty string
            return ""; // empty string
        }
        else { // otherwise we recursivley search right
            return smallest(root);
        }
    }

    // private helper function to find smallest node
    string BSTree::smallest(const Node *curr) const {
        if (curr->left == nullptr) { // if curr's left child is nullptr we have hit the base case and found smallest node
            return curr->data; // we return curr's payload since this is the right most node
        }
        else { // if there are still more left children
            return smallest(curr->left); // we recursivley traverse left to keep finding the left most node
        }
    }


    // Recursive height function
    int BSTree::height(const string &key) const{
        if(search(key)){ // If the key is found, calculate its height.
            const Node* target = searchNode(key,root); // Find the node with the given key.
            return height(target) - 1; // Return the height of the node minus one, since the height of a leaf node is zero.
        }
        else{ // If the key is not found, return -1.
            return -1;
        }
    }
    int BSTree::height(const Node* root) const{
        if(root == nullptr){ // If the node is null, its height is zero.
            return 0;
        }
        else{ // If the node is not null, recursively calculate the height of its left and right subtrees.
            int leftHeight = height(root->left);
            int rightHeight = height(root->right);

            if(leftHeight > rightHeight){ // Return the height of the taller subtree plus one.
                return (leftHeight + 1);
            }
            else{
                return (rightHeight + 1);
            }
        }
    }
    // this function returns a pointer to the node we find based on the key
    const Node* BSTree::searchNode(const string &key,const Node* root) const {
        if(key == root->data){ // if the key matches the data of the current node, return the pointer to that node.
            return root;
        }
        else if(key > root->data){ // if the key is greater than the data of the current node we traverse right
            return searchNode(key, root->right);
        }
        else{ // otherwise we search left
            return searchNode(key, root->left);
        }
    }

    // public inOrder
    void BSTree::inOrder() const{ 
        if(root == nullptr){
            return;
        }
        else{
            inOrder(root);
        }
    }

    // recursive inOrder function
    void BSTree::inOrder(Node* curr) const {
        if (curr) {
            inOrder(curr->left);
            cout << curr->data << "(" << curr->count << "), ";
            inOrder(curr->right);
        }
    }
    
    // public preorder
    void BSTree::preOrder() const {
        preOrder(root);
    }

    // recursive preOrder function
    void BSTree::preOrder(Node* curr) const {
        if (curr) {
            cout << curr->data << "(" << curr->count << "), ";
            preOrder(curr->left);
            preOrder(curr->right);
        }
    }

    // public post order
    void BSTree::postOrder() const {
        postOrder(root);
    }

// Recursive postOrder function
    void BSTree::postOrder(Node* curr) const {
        if (curr) {
            postOrder(curr->left);
            postOrder(curr->right);
            cout << curr->data << "(" << curr->count << "), ";
        }
    }







