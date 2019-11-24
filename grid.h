#include <vector>
#include <utility>
#include "cell.h"

const int SIZE = 8;  // Sets board side length constant

enum class Direction {Up, Down, Left, Right};  // Directions of movement

class Link;

class Grid {
        std::vector<std::vector<Cell>> cells;
        std::vector<std::vector<std::pair<int, int>>> locationOfLinks;
        
    public:
        // Constructor for a Grid
        //   Instantiates Cells with the vector of Links in a size*size Grid
        Grid(int size, std::vector<Link *> links);

        // Additional construction may go here if necessary
        void init();

        // Moves Player player's Link-link, towards Direction dir
        void move(int player, int link, Direction dir);

        // Calls any type of Display to draw
        void print();
};
