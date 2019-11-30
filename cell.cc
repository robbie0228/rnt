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
            setState(StateType{getPlayerNumFromLink(otherLink),
                               link->getName(),
                               link->getType(),
                               false, 0});
            link = otherLink;
            notifyObservers();
            return false;
        } else {
            setState(StateType{getPlayerNumFromLink(link),
                               otherLink->getName(),
                               otherLink->getType(),
                               false, 0});
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
    if (a == Ability::Boost) {
        int currSpeed = this->link->getSpeed();
        this->link->setSpeed(1 + currSpeed);
        setState(StateType{-1, '.', LinkType::NoType,
                           false, getPlayerNumFromLink(this->link)});
    }
    notifyObservers();
}

void Cell::removeLink() {
    setState(StateType{-1, '.', LinkType::NoType,
                       false, -1});
    notifyObservers();
    link = nullptr;
}

void Cell::removeAndDownload() {
    setState(StateType{getPlayerNumFromLink(link),
                       link->getName(),
                       link->getType(),
                       false, 0});
    notifyObservers();
    removeLink();
}

void Cell::setLink(Link *newLink) {
    link = newLink;
}

InfoType Cell::getInfo() const{
    return InfoType{row, col, getName(), 
                    link == nullptr ? LinkType::NoType : link->getType(),
                    link == nullptr ? -1 : link->getStrength()};
}