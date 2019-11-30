#include "cell.h"
#include <cstdlib>

using namespace std;

int getPlayerNumFromLink(Link *link) {
    return link->getName() < 'a' ? 2 : 1;
}

Cell::Cell(int row, int col, Link *link, int serverPort): 
    link{link}, row{row}, col{col}, firewall{0}, serverPort{serverPort} {}

bool Cell::moveCellHere(Cell &cell) {
    if (serverPort) {
        // TODO: Tell player to download link
        return true;
    } else if (link == nullptr) {
        link = cell.getLink();
        return false;
    } else {
        Link *otherLink = cell.getLink();
        if (otherLink == nullptr) {
            throw "Cannot move empty cell to cell with link";
        }
        if (abs(otherLink->getName() - link->getName()) < 8) {
            throw "Cannot move a link onto another of your links";
        }
        if (otherLink->getStrength() >= link->getStrength()) {
            setState(StateType{getPlayerNumFromLink(otherLink), link->getName(), link->getType(), false, false});
            link = otherLink;
            notifyObservers();
            return false;
        } else {
            setState(StateType{getPlayerNumFromLink(link), otherLink->getName(), otherLink->getType(), false, false});
            notifyObservers();
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

void Cell::useAbility(Ability a) {
    switch (a) {
        case Ability::Boost :
        {
            int currSpeed = this->link->getSpeed();
            this->link->setSpeed(1 + currSpeed);
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
            break;
        }
    }
}

void Cell::removeLink() {
    notifyObservers();
    link = nullptr;
}

void Cell::removeAndDownload() {
    setState(StateType{getPlayerNumFromLink(link), link->getName(), link->getType(), false, false});
    notifyObservers();
    removeLink();
}

void Cell::setLink(Link *newLink) {
    link = newLink;
}

InfoType Cell::getInfo() const{
    return InfoType{row, col, getName(), link->getType(), link->getStrength()};
}