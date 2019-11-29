#include "text_display.h"
using namespace std;

TextDisplay::TextDisplay(vector<vector<char>> grid, 
                         vector<vector<pair<char, string>>> links) {
    this->grid = grid;
    this->links = links;
    
    knownLinks = vector<vector<bool>>(2, vector<bool>(8, false));
}

void TextDisplay::notify(Subject&) {
    return;
}

ostream& operator<< (ostream& out, TextDisplay& display) {
    return out;
}

