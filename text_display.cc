#include "text_display.h"
using namespace std;

TextDisplay::TextDisplay(vector<vector<char>> grid, 
                         vector<vector<pair<char, string>>> links,
                         int currentPlayer) {
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

    this->currentPlayer = currentPlayer;
}

void TextDisplay::notify(Subject&) {
    // Subject/Observer
}

ostream& operator<< (ostream& out, TextDisplay& display) {
    out << "Player 1:" << endl
        << "Downloaded: " << display.downloadedCounts[0].first << "D, " 
                          << display.downloadedCounts[0].second << "V" << endl
        << "Abilities: " << display.abilityRemainingCounts[0] << endl;

    if (display.currentPlayer == 1) {
        for (int i = 0; i < 3; ++i) {
            out << display.links[0][i].first << ": " 
                << display.links[0][i].second << "   ";
        }
        out << display.links[0][3].first << ": "
            << display.links[0][3].second << endl;
        for (int i = 4; i < 7; ++i) {
            out << display.links[0][i].first << ": " 
                << display.links[0][i].second << "   ";
        }
        out << display.links[0][7].first << ": "
            << display.links[0][7].second << endl;
    }
    else if (display.currentPlayer == 2) {
        for (int i = 0; i < 3; ++i) {
            out << display.links[0][i].first << ": ";
            if (display.knownLinks[1][i]) {   
                out << display.links[0][i].second << "   ";
            }
            else {
                out << "?    ";
            }
        }
        out << display.links[0][3].first << ": ";
        if (display.knownLinks[1][3]) {   
                out << display.links[0][3].second << endl;
            }
        else {
            out << "?" << endl;
        }
        for (int i = 4; i < 6; ++i) {
            out << display.links[0][i].first << ": ";
            if (display.knownLinks[1][i]) {   
                out << display.links[0][i].second << "   ";
            }
            else {
                out << "?    ";
            }
        }
        out << display.links[0][7].first << ": ";
        if (display.knownLinks[1][7]) {   
                out << display.links[0][7].second << endl;
            }
        else {
            out << "?" << endl;
        }
    }
    else {
        throw "this player does not exist";
    }

    out << string(8, '=') << endl;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            out << display.grid[row][col];
        }
        out << endl;
    }

    out << string(8, '=') << endl;

     out << "Player 2:" << endl
        << "Downloaded: " << display.downloadedCounts[1].first << "D, " 
                          << display.downloadedCounts[1].second << "V" << endl
        << "Abilities: " << display.abilityRemainingCounts[1] << endl;

    if (display.currentPlayer == 2) {
        for (int i = 0; i < 3; ++i) {
            out << display.links[1][i].first << ": " 
                << display.links[1][i].second << "   ";
        }
        out << display.links[1][3].first << ": "
            << display.links[1][3].second << endl;
        for (int i = 4; i < 7; ++i) {
            out << display.links[1][i].first << ": " 
                << display.links[1][i].second << "   ";
        }
        out << display.links[1][7].first << ": "
            << display.links[1][7].second << endl;
    }
    else if (display.currentPlayer == 1) {
        for (int i = 0; i < 3; ++i) {
            out << display.links[1][i].first << ": ";
            if (display.knownLinks[0][i]) {   
                out << display.links[1][i].second << "   ";
            }
            else {
                out << "?    ";
            }
        }
        out << display.links[1][3].first << ": ";
        if (display.knownLinks[0][3]) {   
                out << display.links[1][3].second << endl;
            }
        else {
            out << "?" << endl;
        }
        for (int i = 4; i < 6; ++i) {
            out << display.links[1][i].first << ": ";
            if (display.knownLinks[0][i]) {   
                out << display.links[1][i].second << "   ";
            }
            else {
                out << "?    ";
            }
        }
        out << display.links[1][7].first << ": ";
        if (display.knownLinks[0][7]) {   
                out << display.links[1][7].second << endl;
            }
        else {
            out << "?" << endl;
        }
    }
    else {
        throw "this player does not exist";
    }

    return out;
}

