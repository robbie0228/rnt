#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include "subject.h"
using std::vector;

class TextDisplay : public Observer
{
    // 8*8 2D array of (. a-h A-H S m w)
    vector<vector<char>> grid;

    // 2 player's 8 of pair(a-hA-H, D/V1-8)
    //   note that Copping 2 to have 4 steroids makes a max strength of 8
    vector<vector<std::pair<char, std::string>>> links;

    // 2 player's 8 of the other player's links' reveal status
    //   true means revealed to this player
    vector<vector<bool>> knownLinks;

    // 2 player's pair(downloaded data, downloaded virus)
    vector<std::pair<int, int>> downloadedCounts;

    // Remaining Ability counters for all players
    vector<int> abilityRemainingCounts;

public:
    // Constructor
    TextDisplay(vector<vector<char>> grid,
                vector<vector<std::pair<char, std::string>>> links);
    // Being notified
    void notify(Subject &whoFrom);
    // Commence cout sequence 
    void draw(int currentPlayer);
};

#endif
