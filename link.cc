#include "link.h"

Link::Link(LinkType type, int strength, char name): 
    type{type}, strength{strength}, name{name} {}

LinkType Link::getType() {
    return type;
}

void Link::setType(LinkType newType) {
    type = newType;
}

int Link::getStrength() {
    return strength;
}

void Link::setStrength(int newStrength) {
    strength = newStrength;
}

char Link::getName() {
    return name;
}
