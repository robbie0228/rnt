#include <vector>
#include "grid.h"
#include "player.h"

const int numOfPlayers = 2;

class Game {
        Grid grid;     // grid is the Grid that the game takes place in
        std::vector<Player> players;    // a vector of two Player's

    public:
        // Constructor for a Game
        //   Instantiates a grid and a vector of players
        //   Uses link information from each player to instantiate grid
        Game();

        // Additional construction may go here if necessary
        void init();

        // Calls Grid's print()
        void print();

        // Moves Link-link towards Direction dir;
        //   Parses link and calls Grid's move() with parsed information
        void move(char link, Direction dir);
};
