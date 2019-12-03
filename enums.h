#ifndef ENUMS_H
#define ENUMS_H

// Constants
const int GRIDSIZE = 8;       // Board side length
const int NUMPLAYERS = 2;     // Number of players
const int NUMLINKS = 8;       // Number of links per player
const int NUMABILITIES = 5;   // Number of abilities per player
const int MAXABILITYUSE = 1;  // Limit of ability use per turn
const int MAXCMDLINEARGS = 9; // Limit of command line arguments

// Names for an Ability
enum class Ability
{
    Firewall,
    Download,
    Boost, // Full name: Link Boost; note at cmd line, first letter is L
    Scan,
    Polarize,

    Uber, 
    Whey, 
    Ambush,

    NoAbility
};

// Types of a Link
enum class LinkType
{
    Virus,
    Data,

    NoType
};

// Directions of movement
enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

// Status of a Player
enum class PlayStatus
{
    Win,
    Lose,
    InPlay
};

#endif
