#include <iostream>
#include "Playlist.h"
#include <string>

using namespace std;

    PlaylistNode::PlaylistNode()
    {
        uniqueID = "none";
        songName = "none";
        artistName = "none";
        songLength = 0;
        nextNodePtr = nullptr;
    }

    PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength): uniqueID(uniqueID), songName(songName) ,artistName(artistName) , songLength(songLength) , nextNodePtr(nullptr)
    {} // initializer list for cleaner code

    void PlaylistNode::PrintPlaylistNode()
    {
        cout << "Unique ID: " << GetID() << endl;// helper function 
        cout << "Song Name: " << GetSongName() << endl;
        cout << "Artist Name: " << GetArtistName() << endl;
        cout << "Song Length (in seconds): " << GetSongLength() << endl;
    }

    int PlaylistNode::GetSongLength()
    {
        return songLength; // function for getting the song length for a PlayListNode object
    }

    string PlaylistNode::GetID()
    {
        return uniqueID; // function for getting the unique ID for a PlayListNode object
    }

    string PlaylistNode::GetSongName()
    {
        return songName; // function for getting the song name for a PlayListNode object
    }

    string PlaylistNode::GetArtistName()
    {
        return artistName; // function for getting the Artist Name for a PlayListNode object
    }
    void PlaylistNode::SetNext(PlaylistNode* song) // mutator, updates next node
    {
        nextNodePtr = song;
    }

    Playlist::Playlist(): head(nullptr) , tail(nullptr) // initializer list to set head and tail to nullptr in def constructor
    {} 

    void PlaylistNode::InsertAfter(PlaylistNode* newNode)
    {
        if (newNode == nullptr)
        {
            // Nothing to insert.
            return;
        }

        newNode->SetNext(this->GetNext()); // set the next pointer of newNode to the current node's next.

        this->SetNext(newNode); // set the current node's next to the newNode.
    }

	
    PlaylistNode* PlaylistNode::GetNext() 
    {
        return nextNodePtr;
    }

    void Playlist::addSong(PlaylistNode* newSong) 
    {
        if (isEmpty()) // if empty list
        {
            head = newSong; // then head and tail will point to the newSong
            tail = newSong;
        }
        else
        {
            tail->SetNext(newSong); // tail's next will point to the newSong. 
            tail = newSong; // tail will point to new song
        }
    }

    void Playlist::removeSong(string id)
    {
        if (isEmpty()) // first we wanna check if the list is empty
        {
            return; // if so we want to remove nothing
        }
        else
        {
            PlaylistNode* prev = nullptr; // use a 2 pointer approach so we can skip a node
            PlaylistNode *curr = head;
            while (curr != nullptr) // iterate till curr points to tail's next
            {
                if (curr->GetID() == id) // if we find that the curr node we are pointing at is the song to remove
                {
                    if (curr == tail) // if we find the node to remove and it happens to be a tail node we need to tackle this edge case
                    {
                        tail = prev; // change the tail pointer to point to the node before curr (the node we want to get rid of)
                        cout << '\"' << curr->GetSongName() << '"' << " removed." << endl;
                        delete curr;
                    }
                    else if (curr == head) // edge case to remove the first node. We use prev instead of curr it starts of by pointing to head's next pointer
                    {
                        head = curr->GetNext(); // make head pointer point to the 2nd node in the list
                        cout << '\"' << curr->GetSongName() << '"' << " removed." << endl;
                        delete curr; // deallocate the curr node from memory
                    }
                    else if (curr == head && curr == tail) // edge case in which there is only one node in the list
                    {
                        cout << '\"' << curr->GetSongName() << '"' << " removed." << endl;
                        delete curr; // deallocate the curr node from memory
                        head = tail = nullptr; // no nodes in the list so head and tail should point to nothing
                    }  
                    else
                    {
                        prev->SetNext(curr->GetNext()); // we need the previous pointer to point at the song to remove's next node, so we can skip it
                        prev = curr; // make prev point to the same node as current
                        cout << '\"' << curr->GetSongName() << '"' << " removed." << endl;
                        delete curr; // deallocate the curr node from memory
                    }
                }
                prev = curr;
                curr = curr->GetNext();  
            }
        }
    }


    void Playlist::changePos() {
    if (isEmpty()) { // check if the playlist is empty
        cout << "Playlist is empty." << endl;
        return;
    }

    int currentPos, newPos;
    cout << endl;
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    cin >> currentPos; // get the current position from the user
    cout << "Enter new position for song:";
    cin >> newPos; // get the new position from the user
    cout << endl;

    if (currentPos < 1) {
        currentPos = 1; // Ensure current position is at least 1 (the head)
    }

    int nodeCount = 0;
    PlaylistNode* currentNode = head;
    PlaylistNode* prevNode = nullptr;

    // Traverse the playlist to count nodes and locate the current node
    while (currentNode != nullptr) { // this is just traversing the list to count the number of nodes
        nodeCount++;

        if (nodeCount == currentPos) {
            break; // Found the current node
        }

        prevNode = currentNode; // iterate
        currentNode = currentNode->GetNext(); // iterate
    }

    if (currentPos > nodeCount) {
        currentPos = nodeCount; // ensure current position is at most the number of nodes (the tail)
    }

    if (currentPos == newPos) {
        cout << "\"" << currentNode->GetSongName() << "\" is already at position " << newPos << "." << endl;
        return; // Song is already at the desired position
    }

    if (prevNode != nullptr) {
        prevNode->SetNext(currentNode->GetNext()); // Remove currentNode from its current position
    } 
    else
    {
        head = currentNode->GetNext(); // update head if the current node is the head
    }

    // find the node that will be after the new position
    PlaylistNode* newNodeAfter = head;
    for (int i = 1; i < newPos - 1; i++) {
        newNodeAfter = newNodeAfter->GetNext();
    }

    if (newPos == 1) {
        currentNode->SetNext(head); // Set currentNode as the new head
        head = currentNode;
    } 
    else 
    {
        currentNode->SetNext(newNodeAfter->GetNext()); // set currentNode after the new position
        newNodeAfter->SetNext(currentNode);
    }

    if (newPos == nodeCount) {
        tail = currentNode; // update tail if the current node is the tail
    }

    cout << "\"" << currentNode->GetSongName() << "\" moved to position " << newPos << endl << endl;
}


    void Playlist::BySpecific(string artistName) 
    {
        int pos = 1; 
        PlaylistNode *curr = head;

        while (curr) // iterate while curr != nullptr
        {
            if (curr->GetArtistName() == artistName) // if the artist name passed in his equal to the node's artist name curr points to
            {
                cout << pos << "." << endl;
                curr->PrintPlaylistNode(); // output that node
                cout << endl;
            }
            pos++; // increment the position
            curr = curr->GetNext();
        }
        
    }

    void Playlist::totalTime() 
    {
        int totalTime = 0;
        PlaylistNode *curr = head; // we use this pointer to traverse this list
        if (isEmpty())
        {
            return; // if its empty we we return since there will be a total time of 0
        }
        else
        {
            while (curr) // iterate till the end of the linked list
            {
                totalTime += curr->GetSongLength(); // apend the song length to the total time
                curr = curr->GetNext();
            }
            cout << endl;
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            cout << "Total time: " << totalTime << " seconds" << endl << endl;
        }
    }
    void Playlist::fullPlaylist(string playlistTitle) 
    {
        cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl; // output this message by default
        if(isEmpty()) // use helper function to check if empty
        {
            cout << "Playlist is empty" << endl << endl; // if empty we display this to user
            return;
        }
        else
        {
            PlaylistNode *curr = head; // point to first node in the list
            int currIndex = 1; // start with first index
            while (curr) // this message allows us to interate till tail, tail points the null, then we are done
            {
                cout << currIndex << "." << endl; // output the index, starts at 1
                curr->PrintPlaylistNode(); //output the playlistnode object
                cout << endl;
                currIndex +=1; // update the index
                curr = curr->GetNext(); // get the next playlistnode object in the list
            }
        }
        return;
        
    }
    bool Playlist::isEmpty() //helper func
    {
        if (head == nullptr && tail == nullptr) // if head and tail are both null, there are no nodes in the list so it's empty
        {
            return true;
        }
        else 
        {
            return false;
        }
    } 


