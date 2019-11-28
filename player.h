#ifndef PLAYER_H
#define PLAYER_H
#include "link.h"
#include <vector>
#include "observer.h"

class Player : public Observer {
        int downloadedDataCount;
        int downloadedVirusCount;

    public:
        // Constructor for a Player
        Player();

        // Additional construction may go here if necessary
        void init();

        // Checks the current status of the Player
        Status checkStatus();

        //////// FOR TESTING ////////
        void print();

        void notify(Subject &whoFrom);
};

#endif
