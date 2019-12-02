#ifndef GRID_H
#define GRID_H

#include <vector>
#include <utility>
#include <iostream>
#include <memory>
#include <string>
#include "cell.h"
#include "text_display.h"
#include "graphics_display.h"
#include "enums.h"
using std::vector;

class Cell;
class Link;
class Player;

class Grid
{
    // 8*8 2D array of Cell's
    vector<vector<Cell>> cells;

    // Every Player's each of the 8 Links have a row-col coordianate pair.
    //   If a Link perishes its coordianate pair is set to <-1, -1>
    vector<vector<std::pair<int, int>>> locationOfLinks;

    // A pointer to the text-style display
    std::unique_ptr<TextDisplay> textDisplay;

    // A pointer to the graphic-style display
    std::unique_ptr<GraphicsDisplay> graphicsDisplay;

    // An interpretation from the command line argument
    //  true means graphic-style display is enabled
    bool useGraphics;

public:
    // Constructor for a Grid
    //   Instantiates Cells in a size*size Grid
    Grid(vector<Player *> players,
         vector<vector<Link *>> linkPointers,
         bool useGraphics);

    // Moves Player (player + 1)'s Link (link + 1), towards Direction dir
    void move(int player, int link, Direction dir);

    // Uses ability
    void useAbility(Ability a, vector<char> v, int user);

    // Calls any type of Display to draw
    void printBoard(int currentPlayer);
};

#endif
