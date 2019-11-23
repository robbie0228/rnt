#include "grid.h"
#include <vector>
#include "player.h"

class Game {
    Grid g;
    std::vector<Player> players;

    public:
        // Constructor for Game
        //  Instantiates a grid and a vector of players
        //  Uses link information from each player to instantiate grid
        Game();

        void print();

        // move (int, int , int, Direction)
        // return type: void
        //
        // // moves the player p's vector-l by d, towards direction d;
        void move(int p, int l, int d, Direction d);
};
