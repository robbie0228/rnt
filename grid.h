#include <vector>
#include <utility>
#include <iostream>
#include "cell.h"
#include "enums.h"
using std::vector;

const int SIZE = 8;  // Sets board side length constant

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
        Grid(int size = SIZE);

        // Additional construction may go here if necessary
        void init();

        // Moves Player player's Link link, towards Direction dir
        void move(int player, int link, Direction dir);

        // Calls any type of Display to draw
        friend std::ostream &operator<<(std::ostream &out, const Grid &grid);
};
