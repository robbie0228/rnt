#include "cell.h"
#include <cstdlib>
Cell::Cell(int row, int col, Link *link, int serverPort): 
    link{link}, row{row}, col{col}, firewall{0}, serverPort{serverPort} {}

bool Cell::moveCellHere(Cell &cell) {
    if (serverPort) {
        // TODO: Tell player to download link
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
            // TODO: Tell player that owns link to download link
            link = otherLink;
            return false;
        } else {
            // TODO: Tell player that owns otherLink to download otherLink
            return true;
        }
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
