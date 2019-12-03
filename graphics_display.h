#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include "subject.h"
#include "enums.h"
#include "window.h"
using std::vector;

class GraphicsDisplay : public Observer
{
    // Reference to Xwindow
    std::unique_ptr<Xwindow> win;

    // 8*8 2D array of (. a-h A-H S m w)
    vector<vector<char>> grid;

    // 2 player's 8 of pair(a-hA-H, D/V1-8)
    //   note that steal 2 to have 4 steroids makes a max strength of 8
    vector<vector<std::pair<char, std::string>>> links;

    // 2 player's 8 of the other player's links' reveal status
    //   true means revealed to this player
    vector<vector<bool>> knownLinks;

    // 2 player's pair(downloaded data, downloaded virus)
    vector<std::pair<int, int>> downloadedCounts;

    // Remaining ability counters for all players
    vector<int> abilityRemainingCounts;

public:
    GraphicsDisplay(vector<vector<char>> grid,
                    vector<vector<std::pair<char, std::string>>> links);
    void draw(int currentPlayer);
private:
   // Notify function called from cell
    void doNotify(Subject &whoFrom);
};

#endif
