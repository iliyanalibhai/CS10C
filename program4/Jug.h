#ifndef JUG_H
#define JUG_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Jug {
    public:
        Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string& solution); 
    private:
        // I used a priority queue since I wanted to retrieve the node with the lowest cost with a sorted order where lowest cost is always in the front                  
        // this contains the different states of the jugs
        struct State {
            int A; // jug A
            int B; // jug B
            int cost;  
            string steps;

            // Constructor
            State(int a, int b, int c, const string& s) : A(a), B(b), cost(c), steps(s) {}

            // overload the < for min heap properties
            bool operator<(const State& other) const {
                return cost > other.cost; 
            }
        };
        // need a way to keep track of visited, storedin this vector
        vector<string> visited; 
        int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
        
        // boolean to check if we have reached target
        bool isTarget(int a, int b) const;

        // function to add to a priority queue
        void priorityEnqueue(priority_queue<State>& pq, int a, int b, int c, const string& s);
};





#endif   