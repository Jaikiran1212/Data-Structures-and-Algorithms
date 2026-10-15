#include <iostream>
#include <string>
#include <stack>

using namespace std;

// A single song in the playlist. The playlist is a doubly linked list
// of these nodes so we can move forward (skip) and backward (go back).
class SongNode{
public:
    string title;
    int playCount;
    SongNode* next;
    SongNode* prev;

    SongNode(string title){
        this->title = title;
        playCount = 0;
        next = nullptr;
        prev = nullptr;
    }
};

class Player {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* current;
    stack<SongNode*> undoStack;   // previous "current" songs
    stack<SongNode*> redoStack;   // undone moves, for redo
    SongNode* favouriteSong;
    int maxPlayCount;

public:

    Player(){
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        favouriteSong = nullptr;
        maxPlayCount = 0;
    }

    // Appends a new song to the end of the playlist.
    void addSong(string title){
        SongNode* newNode = new SongNode(title);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            current = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Added: " << title << endl;
    }

    // Plays the current song and updates the favourite song if needed.
    void play() {
        if (current == nullptr) {
            cout << "Playlist is empty !!" << endl;
            return;
        }
        current->playCount++;

        if (current->playCount > maxPlayCount) {
            maxPlayCount = current->playCount;
            favouriteSong = current;
        }
        cout << "Now Playing: " << current->title << endl;
    }

    // Moves to the next song in the playlist.
    void skip() {
        if (current == nullptr || current->next == nullptr) {
            cout << "No next song to skip to." << endl;
            return;
        }
        undoStack.push(current);
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        current = current->next;
        cout << "Skipped to: " << current->title << endl;
    }

    // Moves to the previous song in the playlist.
    void goBack() {
        if (current == nullptr || current->prev == nullptr) {
            cout << "No previous song to go back to." << endl;
            return;
        }
        undoStack.push(current);
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        current = current->prev;
        cout << "Went back to: " << current->title << endl;
    }

    // Undoes the last skip/goBack action.
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo." << endl;
            return;
        }
        redoStack.push(current);
        current = undoStack.top();
        undoStack.pop();
        cout << "Undo: Back to: " << current->title << endl;
    }

    // Redoes the last undone action.
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo." << endl;
            return;
        }
        undoStack.push(current);
        current = redoStack.top();
        redoStack.pop();
        cout << "Redo: Forward to: " << current->title << endl;
    }

    // Reports the song with the highest play count so far.
    void findFavourite() {
        if (favouriteSong == nullptr || maxPlayCount == 0){
            cout << "No favourite song played yet." << endl;
        }
        else {
            cout << "Favourite song: "<< favouriteSong->title<< " (Play count: "<< maxPlayCount<< ")" << endl;
        }
    }
};

// Reads commands from stdin, one per line, until EOF:
//   A, <song name>  -> add a song
//   P                -> play current song
//   S / N            -> skip to next song
//   G                -> go back to previous song
//   U                -> undo last move
//   R                -> redo last undone move
//   F                -> show favourite song
int main(){
    Player p;
    string line;
    while(getline(cin, line)) {

        if(line.empty()){
            continue;
        }
        if(line.rfind("A, ", 0) == 0) {
            string songName = line.substr(3);
            p.addSong(songName);
        }
        else if(line == "P" || line == "p"){
            p.play();
        }
        else if(line == "S" || line == "s"){
            p.skip();
        }

        else if(line == "N" || line == "n"){
            p.skip();
        }

        else if(line == "G" || line == "g"){
            p.goBack();
        }
        else if(line == "U" || line == "u"){
            p.undo();
        }
        else if(line == "R" || line == "r"){
            p.redo();
        }
        else if(line == "F" || line == "f"){
            p.findFavourite();
        }
    }
    return 0;
}
