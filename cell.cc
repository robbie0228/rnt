#include "cell.h"
#include <cstdlib>

using namespace std;

int getPlayerNumFromLink(Link *link) {
    return link->getName() < 'a' ? 2 : 1;
}

map<string, string> initializeState(int player, char link) {
    map<string, string> state;
    state.insert(pair<string, string>("downloadingPlayer", to_string(player)));
    state.insert(pair<string, string>("downloadingLink", to_string(link)));
    return state;
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
            setState(initializeState(getPlayerNumFromLink(otherLink), link->getName()));
            link = otherLink;
            notifyObservers();
            return false;
        } else {
            setState(initializeState(getPlayerNumFromLink(otherLink), link->getName()));
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
    }
}

void Cell::removeLink() {
    notifyObservers();
    link = nullptr;
}

void Cell::removeAndDownload() {
    setState(initializeState(getPlayerNumFromLink(link), link->getName()));
    notifyObservers();
    removeLink();
}

void Cell::setLink(Link *newLink) {
    link = newLink;
}

map<string, string> Cell::getInfo() const{
    map<string, string> info;
    info.insert(pair<string, string>("row", to_string(row)));
    info.insert(pair<string, string>("col", to_string(col)));
    info.insert(pair<string, string>("name", string(1, getName())));
    return info;
}