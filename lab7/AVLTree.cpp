#include <iostream>
#include "AVLTree.h"
#include <ostream>
#include <fstream>


using namespace std;


int AVLTree::height(Node *curr){
    if(curr == nullptr) { // base case and case if empty
        return -1;
    }
    else { 
        int leftHeight = height(curr->left);
        int rightHeight = height(curr->right);
        // find which path is the longest and add 1 to the height
        if(leftHeight > rightHeight){ 
            return leftHeight + 1;
        }
        else{
            return rightHeight + 1;
        }
    }
}

int AVLTree::balanceFactor(Node* curr) {
    if (curr == nullptr) { // if we have a null node, it's height is -1
        return 0;
    }
    // otherwise we return the max of left height minus the right height and add 1 to that
    return height(curr->left) - height(curr->right);
}

void AVLTree::insert(const string &newString) {
    if (root == nullptr) { // if tree is empty
        root = new Node(newString); // set the root to point to the new node
        return;
    }
    Node *curr = root; // we create a pointer to the root, whcih will help us traverse the tree 

    while (true) {
        if (curr->data == newString) { // if duplicate we return or throw
            return;
            // throw runtime_error("duplicate payload")
        }
        if (newString < curr->data) { // traverse left
            if (curr->left == nullptr) { // if there is no left child we insert
                curr->left = new Node(newString); // set curr's left to point to new node
                curr->left->parent = curr; // the parent will be curr
                break;
            }
            curr = curr->left; // otherwise we keep going left if not null
        }
        else { // if the newString is bigger than curr payload we go right
            if (curr->right == nullptr) { // if right child is empty then we do an insert
                curr->right = new Node(newString); // insert
                curr->right->parent = curr; // update parent pointer
                break;
                }
                curr = curr->right; // otherwise if not null we traverse left
        }
    }
    while (curr) {
        if (balanceFactor(curr) > 1 || balanceFactor(curr) < -1 ) {
            rotate(curr);
        }
        curr = curr->parent; // access to a parent pointer allows us to traverse tree to see if there is an imbalance
    }
}


void AVLTree::rotate(Node* curr) {
    if (balanceFactor(curr) == 2) { // if tree is unbalanced left
        if (balanceFactor(curr->left) == -1) { // edge case where we need to double rotate
            rotateLeft(curr->left);
        }
        rotateRight(curr);
    }
    else if (balanceFactor(curr) == -2) { // if tree is unbalanced right
        if (balanceFactor(curr->right) == 1) { // edge case where we need to double rotate
            rotateRight(curr->right);
        }
        rotateLeft(curr);
    }
}

void AVLTree::setChild(Node* parent, const string& location, Node* child) {
    if (location != "left" && location != "right") { // if location isn't left or right
        throw runtime_error("invalid location");
    }
    if (location == "left") { // if location for child to be set is left
        parent->left = child; // set parent's left to child
    }
    else { // otherwise if location is right
        parent->right = child; //  set parent's right to child
    }
    if (child != nullptr) { // update child's parent
        child->parent = parent;
    }
}

// private helper
void AVLTree::printBalanceFactors(){
    printBalanceFactors(root); //call private helper from root
}

// public member 
// print in order. Go left all the way, print, then go right
void AVLTree::printBalanceFactors(Node* curr) {
    if(curr != nullptr){
        printBalanceFactors(curr->left);
        cout << curr->data << "(" << balanceFactor(curr) << ")" << ", ";
        printBalanceFactors(curr->right);
    }
    else { // if curr is null we have an emptry tree
        // throw runtime_error("printing empty root");
        return; 
    }
}


void AVLTree::rotateLeft(Node* curr) {
    Node* rightLeftChild = curr->right->left; 
    if (curr->parent != nullptr) { // if not at root
        replaceChild(curr->parent, curr, curr->right);
    }
    else { // edge case for root
        root = curr->right;
        root->parent = nullptr;
    }
    // fix curr left and right
    setChild(curr->right, "left", curr);
    setChild(curr, "right", rightLeftChild);
}

void AVLTree::rotateRight(Node *curr){
    Node* leftRightChild = curr->left->right;
    if(curr->parent != nullptr){ // if not currently root, then replaceChild by swapping curr and curr's left
        replaceChild(curr->parent, curr, curr->left);
    }
    else{ //edge case for root
        root = curr->left;
        root->parent = nullptr;
    }
    // fix curr's left and right
    setChild(curr->left, "right", curr);
    setChild(curr, "left", leftRightChild);
}


void AVLTree::replaceChild(Node* parent, Node* childToReplace, Node* desiredChild) {
    if (parent->left == childToReplace) { // if parent's left is the child to be replace
        setChild(parent, "left", desiredChild);
    }
    else { // else parent's right is the child to be replaced
        setChild(parent, "right", desiredChild);
    }
}