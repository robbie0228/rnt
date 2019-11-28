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
            map<string, string> state;
            state.insert(pair<string, string>("downloadingPlayer", to_string(getPlayerNumFromLink(otherLink))));
            state.insert(pair<string, string>("downloadingLink", to_string(link->getName())));
            setState(state);
            link = otherLink;
            return false;
        } else {
            map<string, string> state;
            state.insert(pair<string, string>("downloadingPlayer", to_string(getPlayerNumFromLink(link))));
            state.insert(pair<string, string>("downloadingLink", to_string(otherLink->getName())));
            setState(state);
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
        return getPlayerNumFromLink(link) == 1 ? 'm' : 'w';
    } else {
        return '.';
    }
}

Link *Cell::getLink() const{
    return link;
}

void Cell::removeLink() {
    link = nullptr;
}

void Cell::removeAndDownload() {
    // TODO: Tell player to download link
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