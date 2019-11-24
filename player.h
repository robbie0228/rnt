#include "link.h"
#include <vector>

enum class Status {Win, Lose, InPlay};

class Player {
        int downloadedDataCount;
        int downloadedVirusCount;

    public:
        // Constructor for a Player
        Player();

        // Additional construction may go here if necessary
        void init();

        //////// FOR TESTING ////////
        void print();
};
