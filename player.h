#include "link.h"
#include <vector>

enum class Status {Win, Lose, InPlay};

class Player {
    vector<Link>links; // List of links that the player owns

    public:
        Player(); // Constructs the object 
        vector<Link *> init();  // Initializes all of the links the player owns
                                // returns pointers to the links;
}
