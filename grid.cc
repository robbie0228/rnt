#include "grid.h"
#include "enums.h"

using namespace std;

Grid::Grid(int size) {
    // Initialize links and locations
    for (int player = 0; player < NUMPLAYERS; ++player) {
        // Create a vector of links to contain the links in that row
        vector<Link> playerLinks;
        vector<pair<int, int>> linkLocations;
        for (int link = 0; link < (size / 2); ++link) {
            // Initialize link
            playerLinks.emplace_back(Link(LinkType::Data, link, (char)((player == 0 ? 'a' : 'A') + link)));
            // Initialize location
            if (link == 3) {
                linkLocations.emplace_back(pair<int, int>(player == 0 ? 1 : 6, link));
            } else {
                linkLocations.emplace_back(pair<int, int>(player == 0 ? 0 : 7, link));
            }
        }
        for (int link = 0; link < (size / 2); ++link) {
            playerLinks.emplace_back(Link(LinkType::Virus, link, (char)((player == 0 ? 'e' : 'E') + link)));
            if (link == 0) {
                linkLocations.emplace_back(pair<int, int>(player == 0 ? 1 : 6, link + 4));
            } else {
                linkLocations.emplace_back(pair<int, int>(player == 0 ? 0 : 7, link + 4));
            }
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

    // construct the TextDisplay

    vector<vector<pair<char, string>>> displayLinks = 
        vector<vector<pair<char, string>>>(2, vector<pair<char, string>>(8, make_pair('%', "re")));
    vector<vector<char>> displayGrid =
        vector<vector<char>>(8, vector<char>(8, '&'));

    for (int playerAt = 0; playerAt < NUMPLAYERS; ++playerAt) {
        for (int linkAt = 0; linkAt < GRIDSIZE; ++linkAt) {
            Link currentLink = links[playerAt][linkAt];
            displayLinks[playerAt][linkAt].first = currentLink.getName();
            string linkTypeAndStrength = 
                    (currentLink.getType() == LinkType::Data ? "D" : "V") + 
                     to_string(currentLink.getStrength());
            displayLinks[playerAt][linkAt].second = linkTypeAndStrength;
        }
    }

    for (int row = 0; row < GRIDSIZE; ++row) {
        for (int col = 0; col < GRIDSIZE; ++col) {
            displayGrid[row][col] = cells[row][col].getName();
        }
    }
    
    textDisplay = make_unique<TextDisplay>(displayGrid, displayLinks);
    //new TextDisplay(displayGrid, displayLinks);
}

void Grid::move(int player, int link, Direction dir) {
    pair<int, int> locationOfLink = locationOfLinks[player][link];
    int rowOfLink = locationOfLink.first;
    int colOfLink = locationOfLink.second;
    Cell &cellWithLink = cells[rowOfLink][colOfLink];
    if (dir == Direction::Down) {
        if (rowOfLink + 1 >= 8) {
            if (player == 1) {
                throw "Invalid move";
            }
            locationOfLinks[player][link] = pair<int, int>(-1, -1);
            cellWithLink.removeAndDownload();
        } else {
            Cell &moveToCell = cells[rowOfLink + 1][colOfLink];
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                locationOfLinks[player][link] =
                    pair<int, int>(rowOfLink + 1, colOfLink);
            }
            cellWithLink.removeLink();
        }
    } else if (dir == Direction::Left) {
        if (colOfLink - 1 < 0) {
            throw "Invalid move";
        } else {
            Cell &moveToCell = cells[rowOfLink][colOfLink - 1];
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                locationOfLinks[player][link] =
                    pair<int, int>(rowOfLink, colOfLink - 1);
            }
            cellWithLink.removeLink();
        }
    } else if (dir == Direction::Right) {
        if (colOfLink + 1 >= 8) {
            throw "Invalid move";
        } else {
            Cell &moveToCell = cells[rowOfLink][colOfLink + 1];
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                locationOfLinks[player][link] =
                    pair<int, int>(rowOfLink, colOfLink + 1);
            }
            cellWithLink.removeLink();
        }
    } else {
        if (rowOfLink - 1 < 0) {
            if (player == 0) {
                throw "Invalid move";
            }
            locationOfLinks[player][link] = pair<int, int>(-1, -1);
            cellWithLink.removeAndDownload();
        } else {
            Cell &moveToCell = cells[rowOfLink - 1][colOfLink];
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                locationOfLinks[player][link] =
                    pair<int, int>(rowOfLink - 1, colOfLink);
            }
            cellWithLink.removeLink();
        }
    }
}

void Grid::useAbility(Ability a, vector<char> v) {
    if (a == Ability::Firewall) {
        int row = v[0] - '0';
        int col = v[1] - '0';
        cells[row][col].useAbility(Ability::Firewall);
    } else {
        char linkName = v[0];
        pair<int, int> locationOfLink;
        if ('a' <= linkName && linkName <= 'h') { 
            locationOfLink = locationOfLinks[0][linkName - 'a'];
        } else if ('A' <= linkName && linkName <= 'H') {
            locationOfLink = locationOfLinks[1][linkName - 'A'];    
        }
        int rowOfLink = locationOfLink.first;
        int colOfLink = locationOfLink.second;

        /*if (a == Ability::Download) {
            cells[rowOfLink][colOfLink].useAbility(Ability::Download);
        } else if (a == Ability::Boost) {
            cells[rowOfLink][colOfLink].useAbility(Ability::Boost);
        } else if (a == Ability::Polarize) {
            cells[rowOfLink][colOfLink].useAbility(Ability::Polarize);
        }*/
        cells[rowOfLink][colOfLink].useAbility(a);
    }
}

ostream &operator<<(ostream &out, const Grid &grid) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            out << grid.cells[r][c].getName();
        }
        out << endl;
    }
    return out; // Return out for chaining
}
