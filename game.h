#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "player.h"
using std::pair;
using std::vector;

class Game
{
    // grid is the Grid that the game takes place in
    std::unique_ptr<Grid> grid;
    // A vector of two Player's
    vector<Player> players;
    // An integer that holds info on the current Player
    int currentPlayer;
    // The number of abilities the current player has used in the turn
    int abilityUsedCount;

public:
    // Constructor for a Game
    //   Instantiates a grid and a vector of players
    //   Uses link information from each player to instantiate grid
    Game(vector<pair<int, vector<pair<Ability, bool>>>> cmdAllAbilities,
         vector<pair<int, vector<Link>>> cmdAllLinks, bool useGraphics);

    // Moves Link-link towards Direction dir
    // Parses link and calls Grid's move() with parsed information
    void move(char link, Direction dir);

    // Verifies if the player has the specified ability, and returns
    //  how many chars of information the ability requires
    pair<int, bool> verifyAbility(int abilityID) const;

    // Player consumes an ability
    void useAbility(int abilityID, vector<char> useAbilityInfo);

    // Calls current player's printAbilities()
    void printAbilities(std::ostream &out) const;

    // Prints all information about the game at that current time
    void printBoard(std::ostream &out) const;

    // Checks the status of all players to see if anyone won/lost
    // Returns the player that won or -1 if still in play
    int checkStatus() const;
};

#endif
