#ifndef ENUMS_H
#define ENUMS_H

// Constants
const int GRIDSIZE = 8;  // Board side length
const int NUMPLAYERS = 2; // Number of players

// Ability names
enum class Ability {
    Firewall,
    Download,
    Boost,
    Scan,
    Polarize,

    Uber, 
    Whey, 
    Cop,

    NotAvailable
};

// Types of a Link
enum class LinkType {
    Virus,
    Data
};

// Directions of movement
enum class Direction {
    Up,
    Down,
    Left,
    Right
}; 

// Status of a Player
enum class Status {
    Win, 
    Lose, 
    InPlay
};

#endif
