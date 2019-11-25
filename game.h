#include <vector>
#include <iostream>
#include "grid.h"
#include "player.h"

class Game {
        Grid grid;     // grid is the Grid that the game takes place in
        std::vector<Player> players;    // a vector of two Player's
        int currentPlayer; // an integer that holds info on the current Player

    public:
        // Constructor for a Game
        //   Instantiates a grid and a vector of players
        //   Uses link information from each player to instantiate grid
        Game();

        // Additional construction may go here if necessary
        void init();

        // Moves Link-link towards Direction dir;
        //   Parses link and calls Grid's move() with parsed information
        void move(char link, Direction dir);

        friend std::ostream &operator<<(std::ostream &out, const Game &g);
};


