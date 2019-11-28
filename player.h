#ifndef PLAYER_H
#define PLAYER_H
#include "link.h"
#include <vector>

class Player {
        int downloadedDataCount;
        int downloadedVirusCount;

        std::vector<std::pair<Ability, bool>> ability;

    public:
        // Constructor for a Player
        Player();

        // Additional construction may go here if necessary
        void init();

        // Checks the current status of the Player
        Status checkStatus();

        // Print out the player's abilities, each with an ID number and a status
        //  of if it has been used
        void printAbilities(ostream& out);

        //////// FOR TESTING ////////
        void print();

        Ability useAbility(int abilityID);
};

#endif
