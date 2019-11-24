#include "link.h"

class Cell {
        Link *link; // If Cell contains a Link: link points to that Link;
                    //               otherwise: link is a nullptr
        int row;    // 1 <= row <= 8
        int col;    // 1 <= col <= 8
        int firewall;   // If Cell contains a firewall owned by Player n: 
                        //  firewall = n; 
                        //                                     otherwise:
                        //  firewall = 0;
        int serverPort; // If Cell contains a server port owned by Player n: 
                        //  serverPort = n;
                        //                                        otherwise:
                        //  serverPort = 0;

    public:
        // Constructor for Cell, default to an empty Cell
        Cell(Link *l = nullptr);

        // Moves a Link from the given cell to this Cell
        //   If this Cell has a Link, battle is taken care of
        //   If this Cell has a firewall, consequences are taken care of
        //   If this Cell has a server port, consequences are taken care of
        bool moveCellHere(Cell &cell); 

        // Returns this Cell's link (pointer)
        Link *getLink();

        // Sets this Cell's link (pointer) to nullptr
        void removeLink();

        // Sets this Cell's link (pointer) to nullptr
        // Takes care of recording the download by the owner of the now perished
        //  Link
        //   This is used in case of a Link crosses the opponent border
        void removeAndDownload();

        // TO BE DISCUSSED
        void setLink(Link *link); 

};
