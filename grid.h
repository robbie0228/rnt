#include <vector>
#include <utility>
#include "cell.h"
using std::vector;

const int SIZE = 8;  // Sets board side length constant

enum class Direction {Up, Down, Left, Right};  // Directions of movement

class Link;

class Grid {
        // 8*8 2D array of Cell's
        vector<vector<Cell>> cells;

        // Every Player's each of the 8 Links have a row-col coordianate pair.
        //   If a Link perishes its coordianate pair is set to <-1, -1>
        vector<vector<std::pair<int, int>>> locationOfLinks;

    public:
        // Constructor for a Grid
        //   Instantiates Cells with the vector of Links in a size*size Grid
        Grid(int size, vector<Link *> links);

        // Additional construction may go here if necessary
        void init();

        // Moves Player player's Link link, towards Direction dir
        void move(int player, int link, Direction dir);

        // Calls any type of Display to draw
        void print();
};
