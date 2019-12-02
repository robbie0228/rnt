#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <memory>
#include "grid.h"
#include "player.h"
#include "enums.h"
using std::pair;
using std::vector;

class Game {
        // grid is the Grid that the game takes place in
        std::unique_ptr<Grid> grid;
        // a vector of two Player's
        vector<Player> players;
        // an integer that holds info on the current Player
        int currentPlayer;
        // the number of abilities the current player has used in the turn
        int abilityUsedCount;

    public:
        // Constructor for a Game
        //   Instantiates a grid and a vector of players
        //   Uses link information from each player to instantiate grid
        Game(vector<pair<int, vector<pair<Ability, bool>>>> cmdAllAbilities,
             vector<pair<int, vector<Link>>> cmdAllLinks);

        // Moves Link-link towards Direction dir;
        //   Parses link and calls Grid's move() with parsed information
        void move(char link, Direction dir);

        // Verifies if the player has the specified ability, and returns
        //   how many chars of information the ability requires
        std::pair<int, bool> verifyAbility(int abilityID);

        // Player consumes an ability
        void useAbility(int abilityID, vector<char> useAbilityInfo);

        // Calls current player's printAbilities()
        void printAbilities(std::ostream& out);

        void printBoard();
};

#endif
