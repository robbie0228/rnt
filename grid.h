#include <vector>
#include <utility>
#include "cell.h"

enum class Direction {Up, Down, Left, Right}; // directions of movement

class Link;

class Grid {
    std::vector<std::vector<Cell>> theGrid;
    std::vector<std::vector<std::pair<int, int>>> linkLocations;

    public:
        // Constructor for a Grid
        //   Instantiates cells with the vector of links in a 
        //   size x size grid
        Grid(int size, std::vector<Link *> links);

        // move(int, int, int, Direction) 
        //   Moves player p's link l by d spaces in the direction dir
        void move(int p, int l, int d, Direction dir);

        // prints the grid
        void print();
};
