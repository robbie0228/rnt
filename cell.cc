#include "cell.h"
#include <cstdlib>

using namespace std;

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

Cell::Cell(int row, int col, Link *link, int serverPort):
    link{link}, row{row}, col{col}, firewall{0}, serverPort{serverPort} {}

bool Cell::moveCellHere(Cell &cell) {
    Link *otherLink = cell.getLink();
    if (otherLink == nullptr) {
        throw "Cannot move empty cell, must move your own link";
    }
    if (serverPort) {
        setStateAndNotify(*this,
                          getPlayerNumFromLink(otherLink),
                          otherLink->getName(),
                          otherLink->getType(),
                          true, false, -1);
        return true;
    } else if (link == nullptr) {
        link = cell.getLink();
        setStateAndNotify(*this, -1, '.', LinkType::NoType,
                          false, false, -1);
        return false;
    } else {
        if (abs(otherLink->getName() - link->getName()) < 8) {
            throw "Cannot move a link onto another of your links";
        }
        if (otherLink->getStrength() >= link->getStrength()) {
            link = otherLink;
            setStateAndNotify(*this,
                              getPlayerNumFromLink(link),
                              otherLink->getName(),
                              otherLink->getType(),
                              true, true, -1);
            notifyObservers();
            return false;
        } else {
            setStateAndNotify(*this,
                              getPlayerNumFromLink(link),
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

void Cell::useAbility(Ability a, int player) {
    switch (a) {
        case Ability::Boost :
        {
            int currSpeed = this->link->getSpeed();
            this->link->setSpeed(1 + currSpeed);
            setStateAndNotify(*this, -1, '.', LinkType::NoType, false,
                              false, getPlayerNumFromLink(this->link));
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
                              false, getPlayerNumFromLink(this->link));
            break;
        }
    }
    notifyObservers();
}

void Cell::removeLink() {
    setStateAndNotify(*this, -1, '.', LinkType::NoType,
                      false, false, -1);
    notifyObservers();
    link = nullptr;
}

void Cell::removeAndDownload() {
    setStateAndNotify(*this, getPlayerNumFromLink(link),
                      link->getName(),
                      link->getType(),
                      false, false, -1);
    notifyObservers();
    removeLink();
}

void Cell::setLink(Link *newLink) {
    link = newLink;
}

InfoType Cell::getInfo() const{
    return {row, col, getName(),
            (link == nullptr ? LinkType::NoType : link->getType()),
            (link == nullptr ? -1 : link->getStrength())};
}