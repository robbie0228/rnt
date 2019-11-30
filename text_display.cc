#include "text_display.h"
using namespace std;

TextDisplay::TextDisplay(vector<vector<char>> grid, 
                         vector<vector<pair<char, string>>> links) {
    this->grid = grid;
    this->links = links;

    knownLinks = vector<vector<bool>>(2, vector<bool>(8, false));

    /*this->knownLinks = 
              {
                {true, true, true, true, true, true, true, true,
                 false, false, false, false, false, false, false, false},
                {false, false, false, false, false, false, false, false,
                 true, true, true, true, true, true, true, true}
              };*/

    downloadedCounts = vector<pair<int, int>>(2, pair<int, int>(0, 0));

    abilityRemainingCounts = vector<int>(2, 0);
}

void TextDisplay::notify(Subject&) {
    // Subject/Observer
}

//ostream& operator<< (ostream& out, TextDisplay& display) {
void TextDisplay::draw(int currentPlayer) {
    cout << "Player 1:" << endl
        << "Downloaded: " << downloadedCounts[0].first << "D, " 
                          << downloadedCounts[0].second << "V" << endl
        << "Abilities: " << abilityRemainingCounts[0] << endl;

    if (currentPlayer == 0) {
        for (int i = 0; i < 3; ++i) {
            cout << links[0][i].first << ": " 
                << links[0][i].second << "   ";
        }
        cout << links[0][3].first << ": "
            << links[0][3].second << endl;
        for (int i = 4; i < 7; ++i) {
            cout << links[0][i].first << ": " 
                << links[0][i].second << "   ";
        }
        cout << links[0][7].first << ": "
            << links[0][7].second << endl;
    }
    else if (currentPlayer == 1) {
        for (int i = 0; i < 3; ++i) {
            cout << links[0][i].first << ": ";
            if (knownLinks[1][i]) {   
                cout << links[0][i].second << "   ";
            }
            else {
                cout << "?    ";
            }
        }
        cout << links[0][3].first << ": ";
        if (knownLinks[1][3]) {   
                cout << links[0][3].second << endl;
            }
        else {
            cout << "?" << endl;
        }
        for (int i = 4; i < 7; ++i) {
            cout << links[0][i].first << ": ";
            if (knownLinks[1][i]) {   
                cout << links[0][i].second << "   ";
            }
            else {
                cout << "?    ";
            }
        }
        cout << links[0][7].first << ": ";
        if (knownLinks[1][7]) {   
                cout << links[0][7].second << endl;
            }
        else {
            cout << "?" << endl;
        }
    }
    else {
        throw "this player does not exist";
    }

    cout << string(8, '=') << endl;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            cout << grid[row][col];
        }
        cout << endl;
    }

    cout << string(8, '=') << endl;

     cout << "Player 2:" << endl
        << "Downloaded: " << downloadedCounts[1].first << "D, " 
                          << downloadedCounts[1].second << "V" << endl
        << "Abilities: " << abilityRemainingCounts[1] << endl;

    if (currentPlayer == 1) {
        for (int i = 0; i < 3; ++i) {
            cout << links[1][i].first << ": " 
                << links[1][i].second << "   ";
        }
        cout << links[1][3].first << ": "
            << links[1][3].second << endl;
        for (int i = 4; i < 7; ++i) {
            cout << links[1][i].first << ": " 
                << links[1][i].second << "   ";
        }
        cout << links[1][7].first << ": "
            << links[1][7].second << endl;
    }
    else if (currentPlayer == 0) {
        for (int i = 0; i < 3; ++i) {
            cout << links[1][i].first << ": ";
            if (knownLinks[0][i]) {   
                cout << links[1][i].second << "   ";
            }
            else {
                cout << "?    ";
            }
        }
        cout << links[1][3].first << ": ";
        if (knownLinks[0][3]) {   
                cout << links[1][3].second << endl;
            }
        else {
            cout << "?" << endl;
        }
        for (int i = 4; i < 7; ++i) {
            cout << links[1][i].first << ": ";
            if (knownLinks[0][i]) {   
                cout << links[1][i].second << "   ";
            }
            else {
                cout << "?    ";
            }
        }
        cout << links[1][7].first << ": ";
        if (knownLinks[0][7]) {   
                cout << links[1][7].second << endl;
            }
        else {
            cout << "?" << endl;
        }
    }
    else {
        throw "this player does not exist";
    }

    //return out;
}

