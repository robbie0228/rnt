#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "subject.h"

class Link;

class Player : public Observer
{
    // As denoted by the variable name
    int downloadedDataCount;
    int downloadedVirusCount;

    // 1 or 2
    int playerNumber;

    // The Player's 8 Links
    std::vector<Link> links;

    // The Player's 5 pairs of <abilityName, notUsed?>
    std::vector<std::pair<Ability, bool>> abilities;

    int abilityActivated;

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
    bool isMyLink(char linkName) const;

    // Returns true if the link specified by linkName is the other player's
    bool isEnemyLink(char linkName) const;

    // Checks the current status of the Player
    PlayStatus checkStatus() const;

    // Print out the player's abilities, each with an ID number and a status
    //  of if it has been used
    void printAbilities(std::ostream &out) const;

    // returns the ability that is associated with the ID
    std::pair<Ability, bool> getAbility(int abilityID) const;

    // Marks the ability specified as used
    Ability useAbility(int abilityID, vector<char> abilityInfo);

private:
    // Player gets notified by a Subject
    void doNotify(Subject &whoFrom);
};

#endif
