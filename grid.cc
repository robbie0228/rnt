#include "grid.h"
#include "enums.h"

using namespace std;

Grid::Grid(vector<Player *> players, vector<vector<Link *>> linkPointers, int size) {
    locationOfLinks = vector<vector<pair<int, int>>>(2, 
                      vector<pair<int, int>>(8, 
                      make_pair(-1, -1)));

    // Loop through each row
    for (int r = 0; r < size; ++r) {
        vector<Cell> row;
        // Loop through each column
        for (int c = 0; c < size; ++c) {
            if (r == 0 || r == 7) {
                int player = (r == 0 ? 0 : 1);
                if (c == 3 || c == 4) {
                    row.emplace_back(Cell(r, c, nullptr, player + 1));
                } else {
                    row.emplace_back(Cell(r, c, linkPointers[player][c]));
                    locationOfLinks[player][c] = make_pair(r, c);
                }
            } else if (r == 1 || r == 6) {
                int player = (r == 1 ? 0 : 1);
                if (c == 3 || c == 4) {
                    row.emplace_back(Cell(r, c, linkPointers[player][c]));
                    locationOfLinks[player][c] = make_pair(r, c);
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
        vector<vector<pair<char, string>>>(2,
        vector<pair<char, string>>(8,
        make_pair('%', "re")));
    vector<vector<char>> displayGrid =
        vector<vector<char>>(8,
        vector<char>(8, '&'));

    for (int playerAt = 0; playerAt < NUMPLAYERS; ++playerAt) {
        for (int linkAt = 0; linkAt < GRIDSIZE; ++linkAt) {
            Link * currentLink = linkPointers[playerAt][linkAt];
            displayLinks[playerAt][linkAt].first = currentLink->getName();
            string linkTypeAndStrength = 
                    (currentLink->getType() == LinkType::Data ? "D" : "V") + 
                     to_string(currentLink->getStrength());
            displayLinks[playerAt][linkAt].second = linkTypeAndStrength;
        }
    }

    for (int row = 0; row < GRIDSIZE; ++row) {
        for (int col = 0; col < GRIDSIZE; ++col) {
            displayGrid[row][col] = cells[row][col].getName();
        }
    }

    textDisplay = make_unique<TextDisplay>(displayGrid, displayLinks);

    for (int row = 0; row < GRIDSIZE; ++row) {
        for (int col = 0; col < GRIDSIZE; ++col) {
            for (int player = 0; player < 2; ++player) {
                cells[row][col].attach(players[player]);
            }
            cells[row][col].attach(textDisplay.get());
        }
    }
}

void Grid::move(int player, int link, Direction dir) {
    pair<int, int> locationOfLink = locationOfLinks[player][link];
    int rowOfLink = locationOfLink.first;
    int colOfLink = locationOfLink.second;
    Cell &cellWithLink = cells[rowOfLink][colOfLink];
    int linkSpeed = cellWithLink.getLink()->getSpeed();
    if (dir == Direction::Down) {
        if (rowOfLink + linkSpeed >= 8) {
            if (player == 1) {
                throw "Invalid move";
            }
            locationOfLinks[player][link] = make_pair(-1, -1);
            cellWithLink.removeAndDownload();
        } else {
            Cell &moveToCell = cells[rowOfLink + linkSpeed][colOfLink];
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                locationOfLinks[player][link] =
                    make_pair(rowOfLink + linkSpeed, colOfLink);
            }
            cellWithLink.removeLink();
        }
    } else if (dir == Direction::Left) {
        if (colOfLink - linkSpeed < 0) {
            throw "Invalid move";
        } else {
            Cell &moveToCell = cells[rowOfLink][colOfLink - linkSpeed];
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                locationOfLinks[player][link] =
                    make_pair(rowOfLink, colOfLink - linkSpeed);
            }
            cellWithLink.removeLink();
        }
    } else if (dir == Direction::Right) {
        if (colOfLink + linkSpeed >= 8) {
            throw "Invalid move";
        } else {
            Cell &moveToCell = cells[rowOfLink][colOfLink + linkSpeed];
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                locationOfLinks[player][link] =
                    make_pair(rowOfLink, colOfLink + linkSpeed);
            }
            cellWithLink.removeLink();
        }
    } else {
        if (rowOfLink - linkSpeed < 0) {
            if (player == 0) {
                throw "Invalid move";
            }
            locationOfLinks[player][link] = make_pair(-1, -1);
            cellWithLink.removeAndDownload();
        } else {
            Cell &moveToCell = cells[rowOfLink - linkSpeed][colOfLink];
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                locationOfLinks[player][link] =
                    make_pair(rowOfLink - linkSpeed, colOfLink);
            }
            cellWithLink.removeLink();
        }
    }
}

void Grid::useAbility(Ability a, vector<char> v, int user) {
    if (a == Ability::Firewall) {
        int row = v[0] - '0';
        int col = v[1] - '0';
        cells[row][col].useAbility(Ability::Firewall, user);
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
        cells[rowOfLink][colOfLink].useAbility(a, user);
    }
}

void Grid::printBoard(int currentPlayer) {
    textDisplay->draw(currentPlayer);
}
