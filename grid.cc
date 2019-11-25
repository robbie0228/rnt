#include "grid.h"

Grid::Grid(int size) {
    // Initialize links
    for (size_t player = 0; player < size; ++player) {
        // Create a vector of links to contain the links in that row
        std::vector<Link> playerLinks;
        for (size_t link = 0; link < 4; ++link) {
            playerLinks.emplace_back(Link(LinkType::Data, link, 'a' + link));
        }
        for (size_t link = 0; link < 4; ++link) {
            playerLinks.emplace_back(Link(LinkType::Data, link, 'e' + link));
        }
        links.emplace_back(playerLinks);
    }

    // Loop through each row
    for (size_t r = 0; r < size; ++r) {
        std::vector<Cell> row;
        // Loop through each column
        for (size_t c = 0; c < size; ++c) {
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

void Grid::init() {

}

void Grid::move(int player, int link, Direction dir) {

}

std::ostream &operator<<(std::ostream &out, const Grid &grid) {
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            out << grid.cells[r][c].getName();
        }
    }
    out << std::endl;
    return out; // Return out for chaining
}
