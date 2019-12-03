#include "cell.h"
#include <cstdlib>
#include <iostream>

using namespace std;

//helper function

void setStateAndNotify(Cell &cell,
                       int downloadingPlayer, 
                       char downloadingLinkName, 
                       LinkType downloadingLinkType, 
                       bool downloadingLinkIsRevealed, 
                       bool linkIsRevealed, 
                       int playerUsingAbility) {
    cell.setState(StateType{downloadingPlayer,
                        downloadingLinkName,
                        downloadingLinkType,
                        downloadingLinkIsRevealed,
                        linkIsRevealed,
                        playerUsingAbility});
    cell.notifyObservers();
}

int getPlayerNumFromLink(Link *link) {
    return link->getName() < 'a' ? 2 : 1;
}

// implementations

Cell::Cell(int row, int col, Link *link, int serverPort):
    link{link}, row{row}, col{col}, firewall{0}, serverPort{serverPort} {}

bool Cell::moveCellHere(Cell &cell) {
    Link *otherLink = cell.getLink();
    if (otherLink == nullptr) {
        throw "Cannot move empty cell, must move your own link";
    }

    int attackPlayer = getPlayerNumFromLink(otherLink);
    int defensePlayer = (attackPlayer % 2) + 1;

    if (serverPort) {
        if (serverPort == defensePlayer) {
            setStateAndNotify(*this,
                              defensePlayer,
                              otherLink->getName(),
                              otherLink->getType(),
                              true, false, -1);
            return true;
        } else {
            throw "Invalid move";
        }
    } else if (firewall) {
        if (firewall == defensePlayer) {
            link = otherLink;
            setStateAndNotify(*this, -1, '.', LinkType::NoType,
                              false, true, -1);
            if (otherLink->getType() == LinkType::Virus) {
                link = nullptr;
                setStateAndNotify(*this,
                                  attackPlayer,
                                  otherLink->getName(),
                                  otherLink->getType(),
                                  false, false, -1);
                return true;
            } else {
                return false;
            }
        } else {
            link = otherLink;
            setStateAndNotify(*this, -1, '.', LinkType::NoType,
                          false, false, -1);
            return false;
        }
    } else if (link == nullptr) {
        link = cell.getLink();
        setStateAndNotify(*this, -1, '.', LinkType::NoType,
                          false, false, -1);
        return false;
    } else {
        if (abs(otherLink->getName() - link->getName()) < NUMLINKS) {
            throw "Cannot move a link onto another of your links";
        }
        if (otherLink->getStrength() >= link->getStrength()) {
            char downloadLinkName = link->getName();
            LinkType downloadLinkType = link->getType();
            link = otherLink;
            setStateAndNotify(*this,
                              attackPlayer,
                              downloadLinkName,
                              downloadLinkType,
                              true, true, -1);
            return false;
        } else {
            setStateAndNotify(*this,
                              defensePlayer,
                              otherLink->getName(),
                              otherLink->getType(),
                              true, true, -1);
            return true;
        }
    }
}

char Cell::getName() const{
    if (link != nullptr) {
        return link->getName();
    } else if (serverPort != 0) {
        return 'S';
    } else if (firewall != 0) {
        return firewall == 1 ? 'm' : 'w';
    } else {
        return '.';
    }
}

Link *Cell::getLink() const{
    return link;
}

void Cell::useAbility(Ability abilityName, int user) {
    switch (abilityName) {
        case Ability::Boost :
        {
            int currSpeed = this->link->getSpeed();
            this->link->setSpeed(1 + currSpeed);
            setStateAndNotify(*this, -1, '.', LinkType::NoType, false,
                              false, user);
            break;
        }
        case Ability::Polarize :
        {
            LinkType currType = this->link->getType();
            if (currType == LinkType::Data) {
                this->link->setType(LinkType::Virus);
            } else {
                this->link->setType(LinkType::Data);
            }
            setStateAndNotify(*this, -1, '.', LinkType::NoType, false,
                              false, user);
            break;
        }
        case Ability::Download :
        {
            this->removeAndDownload(user, user);
            break;
        }
        case Ability::Firewall : 
        {
            if (this->getName() != '.') {
                throw "Cell is not empty, cannot place Firewall!";
            }
            this->firewall = user;
            setStateAndNotify(*this, -1, '.', LinkType::NoType, false,
                              false, user);
            break;
        }
        case Ability::Scan :
        {
            setStateAndNotify(*this, -1, '.', LinkType::NoType, false,
                              true, user);
            break;
        }
        case Ability::Whey :
        {
            int currStrength = this->link->getStrength();
            this->link->setStrength(1 + currStrength);
            setStateAndNotify(*this, -1, '.', LinkType::NoType, false,
                              false, user);
            break;
        }
        default :
        {
            setStateAndNotify(*this, -1, '.', LinkType::NoType, false,
                              false, user);
            break;
        }
    }
}

void Cell::removeLink() {
    link = nullptr;
    setStateAndNotify(*this, -1, '.', LinkType::NoType,
                      false, false, -1);
}

void Cell::removeAndDownload(int downloadingPlayer, int playerUsingAbility) {
    char linkName = link->getName();
    LinkType linkType = link->getType();
    link = nullptr;
    setStateAndNotify(*this, downloadingPlayer,
                      linkName,
                      linkType,
                      false, false, playerUsingAbility);
}

void Cell::setLink(Link *newLink) {
    link = newLink;
}

InfoType Cell::getInfo() const{
    return {row, col, getName(),
            (link == nullptr ? LinkType::NoType : link->getType()),
            (link == nullptr ? -1 : link->getStrength())};
}