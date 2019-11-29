#ifndef TEXT_H
#define TEXT_H
#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include "subject.h"
using std::vector;
using std::ostream;

class TextDisplay {
        // 8*8 2D array of (. a-h A-H S m w)
        vector<vector<char>> grid; 
        
        // 2 player's 8 of pair(a-hA-H, D/V1-8)
        //   note that steal 2 to have 4 steroids makes a max strength of 8
        vector<vector<std::pair<char, std::string>>> links;

        // 2 player's 8 of the other player's links' reveal status
        //   true means revealed to this player
        vector<vector<bool>> knownLinks;
        
    public:
        TextDisplay(vector<vector<char>> grid, 
                    vector<vector<std::pair<char, std::string>>> links);
        void notify(Subject& subject);
        friend ostream& operator<< (ostream& out, TextDisplay& display);
};


#endif
