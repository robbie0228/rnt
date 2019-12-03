#include "link.h"

Link::Link(LinkType type, int strength, char name)
    : type{type}, speed{1}, strength{strength}, name{name} {}

LinkType Link::getType() const
{
    return type;
}

void Link::setType(LinkType newType)
{
    type = newType;
}

int Link::getSpeed() const
{
    return speed;
}

void Link::setSpeed(int newSpeed)
{
    speed = newSpeed;
}

int Link::getStrength() const
{
    return strength;
}

void Link::setStrength(int newStrength)
{
    strength = newStrength;
}

char Link::getName() const
{
    return name;
}
