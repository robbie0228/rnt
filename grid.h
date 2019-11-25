#include <vector>
#include <utility>
#include <iostream>
#include "cell.h"
#include "enums.h"
using std::vector;

class Link;

class Grid {
        // Every Player's each of the 8 links;
        vector<vector<Link>> links;

        // 8*8 2D array of Cell's
        vector<vector<Cell>> cells;

        // Every Player's each of the 8 Links have a row-col coordianate pair.
        //   If a Link perishes its coordianate pair is set to <-1, -1>
        vector<vector<std::pair<int, int>>> locationOfLinks;

    public:
        // Constructor for a Grid
        //   Instantiates Cells in a size*size Grid
        Grid(int size = GRIDSIZE);

        // Moves Player (player + 1)'s Link (link + 1), towards Direction dir
        void move(int player, int link, Direction dir);

        // Calls any type of Display to draw
        friend std::ostream &operator<<(std::ostream &out, const Grid &grid);
};
