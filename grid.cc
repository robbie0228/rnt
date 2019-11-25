#include "grid.h"

using namespace std;

Grid::Grid(int size) {
    // Initialize links and locations
    for (int player = 0; player < size; ++player) {
        // Create a vector of links to contain the links in that row
        vector<Link> playerLinks;
        vector<pair<int, int>> linkLocations;
        for (int link = 0; link < 4; ++link) {
            // Initialize link
            playerLinks.emplace_back(Link(LinkType::Data, link, (char)('a' + link)));
            // Initialize location
            linkLocations.emplace_back(pair<int, int>(player, link));
        }
        for (int link = 0; link < 4; ++link) {
            playerLinks.emplace_back(Link(LinkType::Virus, link, (char)('e' + link)));
            linkLocations.emplace_back(pair<int, int>(player, link + 4));
        }
        links.emplace_back(playerLinks);
        locationOfLinks.emplace_back(linkLocations);
    }

    // Loop through each row
    for (int r = 0; r < size; ++r) {
        vector<Cell> row;
        // Loop through each column
        for (int c = 0; c < size; ++c) {
            if (r == 0) {
                if (c == 3 || c == 4) {
                    row.emplace_back(Cell(r, c, nullptr, 1));
                } else {
                    row.emplace_back(Cell(r, c, &(links[0][c])));
                }
            } else if (r == 7) {
                if (c == 3 || c == 4) {
                    row.emplace_back(Cell(r, c, nullptr, 2));
                } else {
                    row.emplace_back(Cell(r, c, &(links[1][c])));
                }
            } else if (r == 1) {
                if (c == 3 || c == 4) {
                    row.emplace_back(Cell(r, c, &(links[0][c])));
                } else {
                    row.emplace_back(Cell(r, c)); 
                }
            } else if (r == 6) {
                if (c == 3 || c == 4) {
                    row.emplace_back(Cell(r, c, &(links[1][c])));
                } else {
                    row.emplace_back(Cell(r, c)); 
                }
            } else {
                row.emplace_back(Cell(r, c)); 
            }
        }
        cells.emplace_back(row); // Add row of cells to grid
    }
}

void Grid::move(int player, int link, Direction dir) {
    pair<int, int> locationOfLink = locationOfLinks[player][link];
    int rowOfLink = locationOfLink.first;
    int colOfLink = locationOfLink.second;
    Cell &cellWithLink = cells[rowOfLink][colOfLink];
    if (dir == Direction::Down) {
        if (rowOfLink + 1 >= 8) {
            cellWithLink.removeAndDownload();
        } else {
            Cell &moveToCell = cells[rowOfLink + 1][colOfLink];
            moveToCell.moveCellHere(cellWithLink);
        }
    } else if (dir == Direction::Left) {
        if (colOfLink - 1 < 0) {
            cellWithLink.removeAndDownload();
        } else {
            Cell &moveToCell = cells[rowOfLink][colOfLink - 1];
            moveToCell.moveCellHere(cellWithLink);
        }
    } else if (dir == Direction::Right) {
        if (colOfLink + 1 >= 8) {
            cellWithLink.removeAndDownload();
        } else {
            Cell &moveToCell = cells[rowOfLink][colOfLink + 1];
            moveToCell.moveCellHere(cellWithLink);
        }
    } else {
        if (rowOfLink - 1 < 0) {
            cellWithLink.removeAndDownload();
        } else {
            Cell &moveToCell = cells[rowOfLink - 1][colOfLink];
            moveToCell.moveCellHere(cellWithLink);
        }
    }
}

ostream &operator<<(ostream &out, const Grid &grid) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            out << grid.cells[r][c].getLink()->getName();
        }
    }
    out << endl;
    return out; // Return out for chaining
}
