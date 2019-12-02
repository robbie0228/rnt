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

        // Override a Player's abilities for a command line initialization
        void overrideAbilities(vector<std::pair<Ability, bool>> cmdAbilities);

        // Construction of links for a Player
        std::vector<Link *> init();

        // Custom construction of links for a Player for a cmd line initialization
        std::vector<Link *> cmdInit(vector<Link> cmdLinks);

        // Returns true if the link specified by linkName is the player's
        bool isMyLink(char linkName);

        // Returns true if the link specified by linkName is the other player's
        bool isEnemyLink(char linkName);

        // Checks the current status of the Player
        PlayStatus checkStatus();

        // Print out the player's abilities, each with an ID number and a status
        //  of if it has been used
        void printAbilities(std::ostream& out) const;

        // returns the ability that is associated with the ID
        std::pair<Ability, bool> getAbility(int abilityID);

        // marks the ability specified as used
        Ability useAbility(int abilityID, vector<char> abilityInfo);

    private:
        // Notify called from cell
        void doNotify(Subject &whoFrom);
};

#endif
