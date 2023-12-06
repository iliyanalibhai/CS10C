#include <iostream>
#include "Tree.h"
#include <stdexcept>
using namespace std;


// constructor

Tree::Tree() {
    root = nullptr;
}

// deconstructor
Tree::~Tree( ){
    deconstructor(root);
} 

void Tree::deconstructor(Node *curr)
{
    if (curr == nullptr) {
        return; // empty tree
    }
    // otherwise recursivley delete node
    deconstructor(curr->left);
    deconstructor(curr->middle);
    deconstructor(curr->right);

    delete curr;
}

// public search function
bool Tree::search (const string &key) const {
    return search(key,root);
  }

// recursive search function
bool Tree::search(const string &key, const Node* curr) const {

    // base case
    if (curr == nullptr) {
        return false;
    }
    if (key == curr->small || key == curr->large) { // if the target key is equal to either the small or large key in a node return true
        return true;
    }
    else {
        if (key < curr->small) { // if the current key is smaller than the small value of the node
        return search(key,curr->left); // then we recursivley search the node's left child
        }
        else if (curr->keyCount == 2 && key < curr->large) { // if there are 2 keys in the node and the key is less than the large key and bigger than small
            return search(key,curr->middle); // search node's middle child
        }
        else { // if the key is greater than the curr's big key, we go right
            return search(key,curr->right);
        }
    }
}



void Tree::insert(const string &key) {
    if (root == nullptr) { // if the tree is empty
        Node* newNode = new Node(key);
        root = newNode;
    } 
    else { 
        insert(key, root); // if not empty call private helper
    }
}

void Tree::insert(const string &key, Node* curr) {
    if (curr == nullptr) { // base case 
        return;
    }

    if(key < curr->small){ // if key is smaller than curr's smaller key
        // check how many are in curr
        if(curr->keyCount == 1){ // if there is room
            if(curr->left == nullptr) { // if at leaf then insert as small key in curr
                curr->large = curr->small; // shift curr's small over to the large spot to prepare for insertion of key
                curr->small = key;
                ++curr->keyCount; 
            }
            else{
                insert(key, curr->left);
            }
        }
        else if(curr->keyCount == 2) { // if curr is full 
            if(curr->left != nullptr){ // if leftChild isnt empty then recursively call insert on curr->left
                insert(key,curr->left);
            }
            else{ // we are at leaf so split curr
                TreeSplit(curr, key);
            }
        }
        else { // else lost so split
            TreeSplit(curr, key); 
        }
    }
    else if(key > curr->small) { // when key either in between or bigger than curr
        //check how many are in curr
        if(curr->keyCount == 1) { 
            if(curr->right == nullptr){ // insert as large key in curr
                curr->large = key;
                ++curr->keyCount;
            }
            else{
                insert(key,curr->right); // else call to the right
            }
        }
        else if(curr->keyCount == 2 && key < curr->large){ // if key is in middle
            if(curr->middle != nullptr){ // recursively call insert to insert in the middle
                insert(key, curr->middle);
            }
            else{ // else lost so split
                TreeSplit(curr, key);
            }
        } 
        else{ // when key is bigger than both in curr 
            TreeSplit(curr, key); 
        }
    }
}


// private helper
void Tree::TreeSplit(Node* curr, const string &key) {
    Node *leftChild = nullptr;
    Node *rightChild = nullptr;
    string middleKey = "";

    if(curr->large == "") { //base case 
        return;
    }
    if(key == curr->small || key == curr->large) { // edge case for duplicates
        throw runtime_error("duplicate");
    }
    // setting the left, middle, and right to prepare for split
    if(key < curr->small) { // edge case for when the key is smaller than both keys in curr
        leftChild = new Node(key); // left child will point to the new key
        rightChild = new Node(curr->large); // it's right child will point to largest key or key B
        middleKey = curr->small;

        
    }
    else if(key > curr->large){ //edge case for when the key is larger than both keys in curr
        leftChild = new Node(curr->small); // make the left child point to the small
        middleKey = curr->large; // middle key wll point to the largest
        rightChild = new Node(key); // right will point to the new key to insert


    }
    else{ //when key is in between
        leftChild = new Node(curr->small);
        middleKey = key;
        rightChild = new Node(curr->large);

    }
    // making the current node a single key to prepare for split
    curr->large = "";
    --curr->keyCount;

    if(curr->parent != nullptr){ // edge case for when the node has parents
        //make mid key go up to parent
        curr->parent->large = middleKey;
        ++curr->parent->keyCount;
        // previous left and right child become middle and right child
        curr->parent->middle = leftChild;
        leftChild->parent = curr->parent;
        curr->parent->right = rightChild;
        rightChild->parent = curr->parent;
    }
    else{ 
        //making middleKey parent of leftchild and right child
        curr->small = middleKey;
        curr->left = leftChild;
        curr->right = rightChild;
        leftChild->parent = curr;
        rightChild->parent = curr;
    }
}

// public remove
void Tree::remove(const string &key){

    remove(key, root);
}

void Tree::remove(const string &key, Node* curr){
    if(curr == nullptr){
        return;
    }
    //check if node exists
    if(search(key, curr)){
        //find the node containing key
        curr = searchNode(key, curr); // use node pointer search function
        // if node is root
        if(curr->parent == nullptr){
            // if leaf
            if(curr->left == nullptr && curr->right == nullptr){
                //if there is only 1 key in node
                if(curr->keyCount == 1){
                    delete curr;
                    root = nullptr;
                }
                //more than 1 key
                else{
                    //check to see which key is the key we are trying to remove
                    if(curr->small == key){
                        curr->small = curr->large;
                        curr->large = "";
                        --curr->keyCount;
                    }
                    else if(curr->large == key){
                        curr->large = "";
                        --curr->keyCount;
                    }
                }
            }
            else{ //node has children
                curr->small = curr->left->small;
                curr->large = curr->right->small;
                ++curr->keyCount;
                delete curr->right;
                delete curr->left;
                curr->right = nullptr;
                curr->left = nullptr;

            }
        }
        else{ //node is not root
            if(curr->keyCount == 1){ // node has one key
                Node *par = curr->parent;
                if(par->right == curr){  //node is right child of parent
                    par->large = par->small;
                    par->small = par->left->small;
                }
                else if(par->left == curr){ //node is left child
                    par->large = par->right->small;
                }
                ++par->keyCount;
                delete par->left;
                delete par->right;
                par->left = nullptr;
                par->right = nullptr;
            }
            else{ // more than one key
                if(curr->small == key){ //in case the small field
                    curr->small = curr->large;
                }
                --curr->keyCount;
                curr->large = "";         
            }
        }
    }
}

void Tree::preOrder() const{
    preOrder(root);
}
void Tree::preOrder(Node *curr) const{
    if(curr == nullptr){
        return;
    }
    else{
        if(curr->keyCount == 1){ //if only one key
        //then output then recurisvely traverse left then right
            cout << curr->small << ", ";
            preOrder(curr->left);
            preOrder(curr->right);
        }
        else if(curr->keyCount == 2){ // edge case for two keys in a node
        //output small key first then traverse left and print same node large key 
            cout << curr->small << ", ";
            preOrder(curr->left);
            cout << curr->large << ", ";
            preOrder(curr->middle);
            preOrder(curr->right);
        }
    }
}
void Tree::inOrder() const{
    inOrder(root);
}
void Tree::inOrder(Node *curr) const{
    if(curr == nullptr){
        return;
    }
    else{
        if(curr->keyCount == 1){ //edge case for 1 key in node
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->right);
        }
        else if(curr->keyCount == 2){ //edge case for 2 keys in node
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->middle);
            cout << curr->large << ", ";
            inOrder(curr->right);
        }
    }
}

void Tree::postOrder() const{
    postOrder(root);
}
void Tree::postOrder(Node *curr) const{
    if(curr == nullptr){
        return;
    }
    else{
        if(curr->keyCount == 1){ //edge case for 1 key in node
        //travel to last then start outputting
            postOrder(curr->left);
            postOrder(curr->right);
            cout << curr->small << ", ";
        }
        else if(curr->keyCount == 2){ //edge case for 2 keys in node
        //traverse to middle first then start outputting
            postOrder(curr->left);
            postOrder(curr->middle);
            cout << curr->small << ", ";
            postOrder(curr->right);
            cout << curr->large << ", ";
        }
    }
}

// return a ref to Node found
Node* Tree::searchNode(const string &key, Node* curr) {
    if(curr == nullptr){ // empty tree
        return nullptr;
    }
    if(curr->small == key || curr->large == key){ //if we find the key return it's adress
        return curr;
    }
    else{
        if(key < curr->small){
            return searchNode(key, curr->left); // go left
        }
        else if(curr->keyCount == 2 && key < curr->large){
            return searchNode(key, curr->middle); // go middle
        }
        else{
            return searchNode(key, curr->right); // go right
        }
    }
}
