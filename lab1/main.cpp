#include <iostream>
#include <string>
#include "Playlist.h"
using namespace std;

void PrintMenu(string playlistTitle);
Playlist *playlistPtr; // this will be a Playlist ptr to access member functions of playlist class (global scope)
int main()
{
    string playlistTitle;
    cout << "Enter playlist's title:" << endl;
    getline(cin,playlistTitle);
    cout << endl;
    playlistPtr = new Playlist();
    PrintMenu(playlistTitle);
    
return 0;
}

void PrintMenu(string playlistTitle) // outputs menu
    {
        cout << playlistTitle << " PLAYLIST MENU" << endl;
        cout << "a - Add song" << endl;
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl;
        cout << "s - Output songs by specific artist" << endl;
        cout << "t - Output total time of playlist (in seconds)" << endl;
        cout << "o - Output full playlist" << endl;
        cout << "q - Quit" << endl; 
        cout << endl;
        cout << "Choose an option:";
        // PrintMenu(playlistTitle);
        char op; // this is for the user's choice to pick an option  
        cin >> op;
        cin.ignore(); // ensure newline character left in the input buffer after reading op is cleared before you proceed to read additional input. (searched this up)
        // cout << endl;
        // string playlistName;  
        // cout << "Enter playlist's title:" << endl;
        // getline(cin,playlistName); // added getline incase user has a space for name
        cout << endl;
        string id, songName, artistName;
        int songLength = 0;
    // while(op!='q')
    // {
        if (op == 'q') 
        {
            return;
        } 
        else if (op == 'a') 
        {
            // AddSong();
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:";
            // cin.ignore();
            getline(cin, id); 
            cout << endl;
            cout << "Enter song's name:";
            getline(cin, songName); // use getline for instances like this if it has spaces
            cout << endl;
            cout << "Enter artist's name:";
            getline(cin, artistName);
            cout << endl;
            cout << "Enter song's length (in seconds):";
            cin >> songLength;
            cout << endl << endl;
            PlaylistNode *newSong = new PlaylistNode(id,songName,artistName,songLength);
            playlistPtr->addSong(newSong); // use the playlistPtr to access the addSong func
            PrintMenu(playlistTitle);
        } 
        else if (op == 'd') 
        {
            // RemoveSong();
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:";
            getline(cin,id);
            cout << endl;
            playlistPtr->removeSong(id);
            cout << endl;
            PrintMenu(playlistTitle);


        } 
        else if (op == 'c') 
        {
            playlistPtr->changePos();
            PrintMenu(playlistTitle);
        }
         else if (op == 's') 
        {
            // BySpecific()
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:";
            getline(cin,artistName);
            cout << endl;
            cout << endl;
            playlistPtr->BySpecific(artistName);
            PrintMenu(playlistTitle);

        } 
        else if (op == 't') 
        {
            playlistPtr->totalTime();
            PrintMenu(playlistTitle);
        } 
        else if (op == 'o') 
        {
           playlistPtr->fullPlaylist(playlistTitle);
           PrintMenu(playlistTitle);
        //    cout << endl;
        }
    }