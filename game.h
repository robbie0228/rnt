#include "grid.h"
#include <vector>
#include "player.h"

class Game {
        Grid g;
        std::vector<Player> players;

    public:
        // Constructor for a Game
        //   Instantiates a grid and a vector of players
        //   Uses link information from each player to instantiate grid
        Game();

        // Additional construction may go here if necessary
        void init();

        // Calls Grid's print()
        void print();

        // Moves Link link towards Direction dir;
        //   Parses link and calls Grid's move() with parsed information
        void move(char link, Direction dir);
};
