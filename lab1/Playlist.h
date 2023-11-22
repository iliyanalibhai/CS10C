#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
using namespace std;

class PlaylistNode {
    private:
        string uniqueID; //  Initialized to "none" in default constructor
        string songName;  // Initialized to "none" in default constructor
        string artistName; // Initialized to "none" in default constructor
        int songLength;  // Initialized to 0 in default constructor
        PlaylistNode* nextNodePtr; // - Initialized to 0 in default constructor
    public:
        PlaylistNode(); // default constructor
        PlaylistNode(string uniqueID, string songName, string artistName, int songLength); //  param constructor for PlayListNode Object
        void InsertAfter(PlaylistNode*);
        void SetNext(PlaylistNode*); // mutator, updates next node
        int GetSongLength();
        string GetID();
        string GetSongName();
	    string GetArtistName();
	    PlaylistNode* GetNext(); // get next node in playlist
        void PrintPlaylistNode();
};

class Playlist {
    private:
        PlaylistNode *head;
        PlaylistNode *tail;
    public:
        void addSong(PlaylistNode* song);
        void removeSong(string id);
        void changePos();
        void BySpecific(string artistName);
        void totalTime();
        void fullPlaylist(string playlistTitle);
        bool isEmpty(); // helper function incase playlist is empty
        Playlist();



};

















#endif