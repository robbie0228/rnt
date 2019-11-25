#include "link.h"
#include <vector>

class Player {
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
};
