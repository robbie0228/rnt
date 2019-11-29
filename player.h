#ifndef PLAYER_H
#define PLAYER_H
#include "link.h"
#include "subject.h"
#include <iostream>
#include <vector>

class Player : public Observer {
        int downloadedDataCount;
        int downloadedVirusCount;

        int playerNumber;

        std::vector<std::pair<Ability, bool>> ability;

    public:
        // Constructor for a Player
        Player(int playerNumber);

        // Additional construction may go here if necessary
        void init();

        // Checks the current status of the Player
        Status checkStatus();

        // Print out the player's abilities, each with an ID number and a status
        //  of if it has been used
        void printAbilities(std::ostream& out);

        //////// FOR TESTING ////////
        void print();

        // returns the ability that is associated with the ID
        std::pair<Ability, bool> getAbility(int abilityID);

        // marks the ability specified as used
        Ability useAbility(int abilityID);

        void notify(Subject &whoFrom);
};

#endif
