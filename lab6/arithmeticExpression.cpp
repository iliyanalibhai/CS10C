#include <iostream>
#include "arithmeticExpression.h"
#include <sstream>
#include <stack>
#include<stdexcept>

using namespace std;

    
    // deconstructor
    arithmeticExpression::~arithmeticExpression() {
        Destructor(root);
    }
     void arithmeticExpression::Destructor(TreeNode* curr) {
        if (curr == nullptr) { // edge case if tree is empty
            return;
        }
        Destructor(curr->left);
        Destructor(curr->right);
        delete curr;
     }
    
    /* Initializes an empty tree and sets the infixExpression
    to the value of parameter passed in. */
    
    arithmeticExpression::arithmeticExpression(const string &expression) {
        root = nullptr; // set the root to be null 
        infixExpression = expression; // initialize the expression to be the expression passed in
    }

    /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */

    void arithmeticExpression::buildTree() {
        infixExpression = infix_to_postfix(); // convert the infix expression to post fix ex: a b c * +
        stack<TreeNode*> stack; // we want to implement a stack so we can easily store operators and operands
        // now we want to iterate over the expression
        for (unsigned i = 0; i < infixExpression.size(); i++) {
            // allocate a new node at each iteration, the objects data will be the expression at that index
            // the key will be a letter and it starts at 'a'
            TreeNode *node =  new TreeNode(infixExpression.at(i), 'a'+i);
            if (priority(infixExpression[i]) == 0) { // if the priority of the char of the expression is not a +,-, or ()
                stack.push(node); // then we can just push the char onto the stack regularly
            }
            else { // otherwise if it is an operator
                node->right = stack.top(); // the right child will be the 2nd operand, a + b, the + will point to node b
                stack.pop();
                node->left = stack.top(); // the left child will be the 1st operand, a + b, the + will point to node a
                stack.pop();
                stack.push(node); // push the operator onto the stack
            } 
        }
        // we need to update the root of the tree
        root = stack.top(); // root will point to the top of the stack and will be the root of the expression tree
    }

    void arithmeticExpression::infix() {
        if (root == nullptr) { // if root is null we want to throw since the expression tree is empty
            throw runtime_error("Empty Expression Tree, can't print");
        }
        infix(root); // if tree isn't empty we want to call the recursive function to print in order (infix)
    }


    // private recursive inOrder function for printing expression in infix
    void arithmeticExpression::infix(TreeNode *curr) {
        
        if (curr != nullptr) {
            // the paranthesis is the first thing that gets printed and also the last thing
            if (curr->left != nullptr) { 
                cout << "(";
            }
            infix(curr->left); // go left all the way till null
            cout << curr->data; // output the data when at left most node
            infix(curr->right); // after printing go right
            // end the expression with a paranthesis
            if(curr->right != nullptr) {
                cout << ")";
            }
        }
    }

    // prefix is *+ab-cd, visits node first then traverses left, then right
    void arithmeticExpression::prefix() {
        
        if (root == nullptr) { // if tree is empty we throw
            throw runtime_error("Tree is empty, can't print in preorder");
        }
        prefix(root);
    }

    // recursive private helper to print in prefix (preorder) notation
    void arithmeticExpression::prefix(TreeNode *curr) {
        
        if (curr != nullptr) { // base case
            cout << curr->data; // print first
            prefix(curr->left); // traverse left
            prefix(curr->right); // traverse right
        }
    }
    // postfix is abc*+de*f+g*-
    void arithmeticExpression::postfix() {
        if (root == nullptr) {
            throw runtime_error("Tree is empty, can't print in post order");
        }
        postfix(root);
    }

    void arithmeticExpression::postfix(TreeNode *curr) {
        if (curr != nullptr) { // base case
            postfix(curr->left);
            postfix(curr->right);
            cout << curr->data;
        }
    }

    void arithmeticExpression::visualizeTree(const string &) {}


    


    void arithmeticExpression::visualizeTree(ofstream &, TreeNode *) {}


    int arithmeticExpression::priority(char op){
        int priority = 0;
        if(op == '('){
            priority =  3;
        }
        else if(op == '*' || op == '/'){
            priority = 2;
        }
        else if(op == '+' || op == '-'){
            priority = 1;
        }
        return priority;
    }

    string arithmeticExpression::infix_to_postfix(){
        stack<char> s;
        ostringstream oss;
        char c;
        for(unsigned i = 0; i< infixExpression.size();++i){
            c = infixExpression.at(i);
            if(c == ' '){
                continue;
            }
            if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
                if( c == '('){
                    s.push(c);
                }
                else if(c == ')'){
                    while(s.top() != '('){
                        oss << s.top();
                        s.pop();
                    }
                    s.pop();
                }
                else{
                    while(!s.empty() && priority(c) <= priority(s.top())){
                        if(s.top() == '('){
                            break;
                        }
                        oss << s.top();
                        s.pop();
                    }
                    s.push(c);
                }
            }
            else{ //c is an operand
                oss << c;
            }
        }
        while(!s.empty()){
            oss << s.top();
            s.pop();
        }
        return oss.str();
    }

    // void arithmeticExpression::visualizeTree(const string &outputFilename){
    //     ofstream outFS(outputFilename.c_str());
    //     if(!outFS.is_open()){
    //         cout<<"Error opening "<< outputFilename<<endl;
    //         return;
    //     }
    //     outFS<<"digraph G {"<<endl;
    //     visualizeTree(outFS,root);
    //     outFS<<"}";
    //     outFS.close();
    //     string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    //     string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    //     system(command.c_str());
    // }