#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node
{
    string payload;
    Node *next;
};

// construct a new node to get the next node in a circular linked list
Node *newNode(string payload)
{
    Node *node = new Node; // create a new node
    node->payload = payload; // assign it the payload passed in
    node->next = nullptr; // initialize its next to nullptr
    return node; // return the node so we can use it in the load game function
}

Node *loadGame(int n, vector<string> names)
{ // n represents the number of sides, vector of names represents the people playing the game
    Node *head = nullptr; // intialize to nullptr
    Node *prev = nullptr; // initialize to nullptr
    string name; // names of the players in game

    for (int i = 0; i < n; ++i) // i iterates through n players playing the game
    { 
        name = names.at(i);
        if (head == nullptr) // if the head is nullptr then the list is empty
        {                         // list will always start off as empty so we set prev and head to the newNode
            head = newNode(name); // initialize head specially
            prev = head;          // since theres only one node, prev and head point to the same node
        }
        else
        {                               // this excutes if list is not empty
            prev->next = newNode(name); //  creates a new Node object with the payload name and sets the next pointer of prev to point to this new node adds a new node to the list.
            prev = prev->next;          // prev pointer to point to the newly added node
        }
    }

    if (prev != nullptr)
    {                      // make circular
        prev->next = head; // theres no tail pointer in this, so prev's next will point back to head
    }
    return head;
}

void print(Node *start)
{ // prints list
    Node *curr = start;
    while (curr != nullptr)
    {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start)
        {
            break; // exit circular list
        }
    }
}

Node *runGame(Node *start, int k)
{ // josephus w circular list, k = num skips
    Node *curr = start;
    Node *prev = curr;
    while (curr->next != curr) // exit condition, last person standing, if curr's next pointer is it self, or basically prev->next is curr it is the last one standing
    { 
        for (int i = 0; i < k; ++i) // iterate till k so we can find the kth node which is the node we want to delete
        { 
            prev = curr;
            curr = curr->next; // loop stops at curr which kth node. prev is the k-1 node
        }
        // delete kth node
        Node *kthNode = curr; // kthNode pointer to not lose curr adresss since we still need it in the loop
        prev->next = curr->next;   // skip the kth node
        curr = curr->next;         // move curr since we still need to use it for the while loop
        delete kthNode; // delete the kth node, we go back into the while loop if curr->next != curr
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main()
{
    int n = 1, k = 1, max; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".")
    {
        names.push_back(name);
    } // EOF or . ends input

    // initialize and run game
    Node *startPerson = loadGame(n, names);
    Node *lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr)
    {
        cout << lastPerson->payload << " wins!" << endl; // output payload of curr
    }
    else
    {
        cout << "error: null game" << endl;
    }

    return 0;
}
