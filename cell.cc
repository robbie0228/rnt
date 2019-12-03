#include <cstdlib>
#include "cell.h"
using namespace std;

// Helper function
void setStateAndNotify(Cell &cell,
                       int downloadingPlayer = -1,
                       char downloadingLinkName = '.',
                       LinkType downloadingLinkType = LinkType::NoType,
                       bool linkIsRevealed = false,
                       int playerUsingAbility = -1)
{
    cell.setState(StateType{downloadingPlayer,
                            downloadingLinkName,
                            downloadingLinkType,
                            linkIsRevealed,
                            playerUsingAbility});
    cell.notifyObservers();
}

// Helper function
int getPlayerNumFromLink(Link *link)
{
    return link->getName() < 'a' ? 2 : 1;
}

Cell::Cell(int row, int col, Link *link, int serverPort)
    : link{link}, row{row}, col{col}, firewall{0}, serverPort{serverPort} {}

bool Cell::moveCellHere(Cell &cell)
{
    Link *otherLink = cell.getLink();
    if (otherLink == nullptr)
    {
        throw "Cannot move an empty cell, move your own link!";
    }

    int attackerNumber = getPlayerNumFromLink(otherLink);
    int defenderNumber = (attackerNumber % 2) + 1;
    if (serverPort)
    {
        if (serverPort == defenderNumber)
        {
            setStateAndNotify(*this,
                              defenderNumber,
                              otherLink->getName(),
                              otherLink->getType());
            return true;
        }
        else
        {
            throw "Cannot move into your own server ports!";
        }
    }
    else if (firewall)
    {
        if (firewall == defenderNumber)
        {
            Link *tempLink = link;
            link = otherLink;
            setStateAndNotify(*this, -1, '.', LinkType::NoType, true);
            if (otherLink->getType() == LinkType::Virus)
            {
                link = tempLink;
                setStateAndNotify(*this,
                                  attackerNumber,
                                  otherLink->getName(),
                                  otherLink->getType());
                return true;
            }
            link = tempLink;
        }
    }
    if (link == nullptr)
    {
        link = cell.getLink();
        setStateAndNotify(*this);
        return false;
    }
    else
    {
        if (abs(otherLink->getName() - link->getName()) < NUMLINKS)
        {
            throw "Cannot move a link onto another of your links!";
        }
        if (otherLink->getStrength() >= link->getStrength())
        {
            char downloadLinkName = link->getName();
            LinkType downloadLinkType = link->getType();
            link = otherLink;
            setStateAndNotify(*this,
                              attackerNumber,
                              downloadLinkName,
                              downloadLinkType,
                              true);
            return false;
        }
        else
        {
            setStateAndNotify(*this,
                              defenderNumber,
                              otherLink->getName(),
                              otherLink->getType(),
                              true);
            return true;
        }
    }
}

char Cell::getName() const
{
    if (link != nullptr)
    {
        return link->getName();
    }
    else if (serverPort != 0)
    {
        return 'S';
    }
    else if (firewall != 0)
    {
        return firewall == 1 ? 'm' : 'w';
    }
    else
    {
        return '.';
    }
}

Link *Cell::getLink() const
{
    return link;
}

void Cell::useAbility(Ability abilityName, int user)
{
    switch (abilityName)
    {
    case Ability::Boost:
    {
        int currSpeed = this->link->getSpeed();
        this->link->setSpeed(1 + currSpeed);
        setStateAndNotify(*this, -1, '.', LinkType::NoType, false, user);
        break;
    }
    case Ability::Polarize:
    {
        LinkType currType = this->link->getType();
        if (currType == LinkType::Data)
        {
            this->link->setType(LinkType::Virus);
            if (firewall == (getPlayerNumFromLink(link) % 2) + 1)
            {
                removeAndDownload(getPlayerNumFromLink(link), -1);
            }
        }
        else
        {
            this->link->setType(LinkType::Data);
        }
        setStateAndNotify(*this, -1, '.', LinkType::NoType, false, user);
        break;
    }
    case Ability::Download:
    {
        this->removeAndDownload(user, user);
        break;
    }
    case Ability::Firewall:
    {
        if (this->getName() != '.')
        {
            throw "Cell is not empty, cannot place Firewall!";
        }
        this->firewall = user;
        setStateAndNotify(*this, -1, '.', LinkType::NoType, false, user);
        break;
    }
    case Ability::Scan:
    {
        setStateAndNotify(*this, -1, '.', LinkType::NoType, true, user);
        break;
    }
    case Ability::Whey:
    {
        int currStrength = this->link->getStrength();
        this->link->setStrength(1 + currStrength);
        setStateAndNotify(*this, -1, '.', LinkType::NoType, false, user);
        break;
    }
    default:
    {
        setStateAndNotify(*this, -1, '.', LinkType::NoType, false, user);
        break;
    }
    }
}

void Cell::removeLink()
{
    link = nullptr;
    setStateAndNotify(*this);
}

void Cell::removeAndDownload(int downloadingPlayer, int playerUsingAbility)
{
    char linkName = link->getName();
    LinkType linkType = link->getType();
    link = nullptr;
    setStateAndNotify(*this, downloadingPlayer,
                      linkName,
                      linkType,
                      false, playerUsingAbility);
}

void Cell::setLink(Link *newLink)
{
    link = newLink;
}

InfoType Cell::doGetInfo() const
{
    return {row, col, getName(),
            (link == nullptr ? LinkType::NoType : link->getType()),
            (link == nullptr ? -1 : link->getStrength())};
}
