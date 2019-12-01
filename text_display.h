#ifndef TEXT_H
#define TEXT_H
#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include "subject.h"
using std::vector;

class TextDisplay : public Observer {
        // 8*8 2D array of (. a-h A-H S m w)
        vector<vector<char>> grid; 
        
        // 2 player's 8 of pair(a-hA-H, D/V1-8)
        //   note that steal 2 to have 4 steroids makes a max strength of 8
        vector<vector<std::pair<char, std::string>>> links;

        // 2 player's 8 of the other player's links' reveal status
        //   true means revealed to this player
        vector<vector<bool>> knownLinks;

        /*// 2 player's 16 of all player's links' reveal status
        // true means revealed to this player
        // player 1's 8 pieces' status are followed by player 2's
        vector<vector<bool>> knownLinks;*/

        // 2 player's pair(downloaded data, downloaded virus)
        vector<std::pair<int, int>> downloadedCounts;

        // remaining ability counters for all players
        vector<int> abilityRemainingCounts;
        
    public:
        TextDisplay(vector<vector<char>> grid, 
                    vector<vector<std::pair<char, std::string>>> links);
        void notify(Subject &whoFrom);
        void draw(int currentPlayer);
};

#endif
