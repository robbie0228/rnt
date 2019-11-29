#ifndef LINK_H
#define LINK_H
#include "enums.h"

class Link {
        LinkType type;  // LinkType of Link
        int speed;
        int strength;   // strength of Link
        char name;      // 'a-h' for Player 1
                        // 'A-H' for Player 2

    public:
        // Constructor for a Link
        //   The Link has given type, strength and name
        Link(LinkType type, int strength, char name);

        // Accessor/setter for type
        LinkType getType();
        void setType(LinkType newType);

        // Accessor/setter for speed;
        int getSpeed();
        void setSpeed(int newSpeed);

        // Accessor/setter for strength
        int getStrength();
        void setStrength(int newStrength);

        // Accessor for name
        char getName();
};

#endif
