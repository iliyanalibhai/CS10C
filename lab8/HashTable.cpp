#include "HashTable.h"
#include "WordEntry.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
	size = s; // s is size of array (slots)
    hashTable = new list<WordEntry>[size];
}

// deconstructor
HashTable::~HashTable () {
  delete[] hashTable;
}



/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
	int sum = 0;

    for(unsigned int i = 0; i < s.size(); ++i) { // add ascii values of each char
        sum += s.at(i); 
    }
    return sum % size; // return the sum of all the ascii values in the string and mod it by the size to create a unqiue hash
}



/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
    // Figure out the slot that we belong to (we call the hash function for this key and modulo)
    int slot = computeHash(s) % size;

    if (contains(s)) { // if string passed in is already in hash table we need a collision strategy
        // create an interator that can iterate through the linked list (chaining)
        list<WordEntry>::iterator i; // standard library iterator 

        // start at the beggining of the hash given by compute hash
        for (i = hashTable[slot].begin(); i != hashTable[slot].end(); ++i) {
            if (i->getWord() == s) { // if the word at i is the same as the word s
                // then addNewAppearance
                i->addNewAppearance(score);
            }
        }
  }
  else { // otherwise if s not in table
    WordEntry newEntry = WordEntry(s,score); // create a new Entry and push in the front of list
    hashTable[slot].push_front(newEntry); // access the correct bucket, then push new word onto list
  }

}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
	if (contains(s)) { // if s is in the table
		list<WordEntry>::iterator i; // iterator
		for (i = hashTable[computeHash(s)].begin(); i != hashTable[computeHash(s)].end(); ++i) { // traverse through linked list
			if (i->getWord() == s) { // if found
				return i->getAverage();
			}
		}
	} 
	return 2.0; // default result
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {

    for(list<WordEntry>::iterator itr = hashTable[computeHash(s)].begin(); itr != hashTable[computeHash(s)].end(); ++itr){
        if(itr->getWord() == s) { // if word at itr == the word passed in
            return true; // return true
        }
    }
    return false; // otherwise if not found return false
}



#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
	// declare a few needed variables for inputing the data
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	//create hash table
	HashTable table(20071);
	
	while (!myfile.eof()) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score); // insert string with the score
	    }
	}
	
	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}