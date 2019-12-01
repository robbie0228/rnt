#ifndef PLAYER_H
#define PLAYER_H
#include "subject.h"
#include "enums.h"
#include <iostream>
#include <vector>

class Link;

class Player : public Observer {
        int downloadedDataCount;
        int downloadedVirusCount;

        int playerNumber;

        std::vector<Link> links;

        std::vector<std::pair<Ability, bool>> abilities;

    public:
        // Constructor for a Player
        Player(int playerNumber);

        // Initialize custom abilities for the Player
        void cmdInitAbilities(string abilities);

        // Initialize custom link positions for the Player
        void cmdInitLinks(string links);

        // Additional construction may go here if necessary
        std::vector<Link *> init();

        // Returns true if the link specified by linkName is the player's
        bool isMyLink(char linkName);

        // Returns true if the link specified by linkName is the other player's
        bool isEnemyLink(char linkName);

        // Checks the current status of the Player
        Status checkStatus();

        // Print out the player's abilities, each with an ID number and a status
        //  of if it has been used
        void printAbilities(std::ostream& out) const;

        // returns the ability that is associated with the ID
        std::pair<Ability, bool> getAbility(int abilityID);

        // marks the ability specified as used
        Ability useAbility(int abilityID, vector<char> abilityInfo);

        void notify(Subject &whoFrom);
};

#endif
