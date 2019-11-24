#include "grid.h"
#include <vector>
#include "player.h"

class Game {
    Grid g;
    std::vector<Player> players;

    public:
        // Constructor for Game
        //   Instantiates a grid and a vector of players
        //   Uses link information from each player to instantiate grid
        Game();

        // Additional construction may go here
        void init();

        // Calls any type of Display to draw
        void print();

        // Moves Player player's Link-link, towards Direction d;
        void move(int player, int link, Direction d);
};
