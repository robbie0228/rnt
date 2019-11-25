#ifndef ENUMS_H
#define ENUMS_H

// Ability names
enum class Ability {
    Firewall,
    Download,
    Boost,
    Polarize,
    Scan

    // new ones: Uber, Whey, Cop
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
