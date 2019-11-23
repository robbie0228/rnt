#include "link.h"

class Cell {
    Link *link; // If this cell contains a link, this is a pointer to that link, otherwise nullptr
    
    public:
        Cell(Link *l = nullptr); // Constructs the cell
        bool moveCellHere(Cell &c); // Moves the link from the given cell to here, 
                                    // battling with this cell's link if required
        void removeLink(); // sets this cell's link pointer to nullptr
        Link *getLink(); // Returns this cell's link pointer
        void setLink(Link *link); // Sets the cell's link
};
