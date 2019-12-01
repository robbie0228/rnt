#include "grid.h"
#include "enums.h"

using namespace std;

Grid::Grid(vector<Player *> players, vector<vector<Link *>> linkPointers) {
    locationOfLinks = vector<vector<pair<int, int>>>(NUMPLAYERS,
                      vector<pair<int, int>>(NUMLINKS,
                      make_pair(-1, -1)));

    // Loop through each row
    for (int r = 0; r < GRIDSIZE; ++r) {
        vector<Cell> row;
        // Loop through each column
        for (int c = 0; c < GRIDSIZE; ++c) {
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
        vector<vector<pair<char, string>>>(NUMPLAYERS,
        vector<pair<char, string>>(NUMLINKS,
        make_pair('%', "N0")));
    vector<vector<char>> displayGrid =
        vector<vector<char>>(GRIDSIZE,
        vector<char>(GRIDSIZE, '&'));

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
            for (int player = 0; player < NUMPLAYERS; ++player) {
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

    if (rowOfLink == -1 && colOfLink == -1) {
        throw "Invalid move";
    }

    Cell &cellWithLink = cells[rowOfLink][colOfLink];
    int linkSpeed = cellWithLink.getLink()->getSpeed();
    if (dir == Direction::Down) {
        if (rowOfLink + linkSpeed >= GRIDSIZE) {
            if (player == 1) {
                throw "Invalid move";
            }
            locationOfLinks[player][link] = make_pair(-1, -1);
            cellWithLink.removeAndDownload(player, -1);
        } else {
            Cell &moveToCell = cells[rowOfLink + linkSpeed][colOfLink];
            char otherCellName = moveToCell.getName();
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                if (('A' <= otherCellName && otherCellName <= 'H')
                    || ('a' <= otherCellName && otherCellName <= 'h')) 
                {
                    locationOfLinks[(player + 1) % NUMPLAYERS][link] = make_pair(-1, -1);
                }
                locationOfLinks[player][link] =
                    make_pair(rowOfLink + linkSpeed, colOfLink);
            } else {
                locationOfLinks[player][link] = make_pair(-1, -1);
            }
            cellWithLink.removeLink();
        }
    } else if (dir == Direction::Left) {
        if (colOfLink - linkSpeed < 0) {
            throw "Invalid move";
        } else {
            Cell &moveToCell = cells[rowOfLink][colOfLink - linkSpeed];
            char otherCellName = moveToCell.getName();
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                if (('A' <= otherCellName && otherCellName <= 'H')
                    || ('a' <= otherCellName && otherCellName <= 'h')) 
                {
                    locationOfLinks[(player + 1) % NUMPLAYERS][link] = make_pair(-1, -1);
                }
                locationOfLinks[player][link] =
                    make_pair(rowOfLink, colOfLink - linkSpeed);
            } else {
                locationOfLinks[player][link] = make_pair(-1, -1);
            }
            cellWithLink.removeLink();
        }
    } else if (dir == Direction::Right) {
        if (colOfLink + linkSpeed >= GRIDSIZE) {
            throw "Invalid move";
        } else {
            Cell &moveToCell = cells[rowOfLink][colOfLink + linkSpeed];
            char otherCellName = moveToCell.getName();
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                if (('A' <= otherCellName && otherCellName <= 'H')
                    || ('a' <= otherCellName && otherCellName <= 'h')) 
                {
                    locationOfLinks[(player + 1) % NUMPLAYERS][link] = make_pair(-1, -1);
                }
                locationOfLinks[player][link] =
                    make_pair(rowOfLink, colOfLink + linkSpeed);
            } else {
                locationOfLinks[player][link] = make_pair(-1, -1);
            }
            cellWithLink.removeLink();
        }
    } else {
        if (rowOfLink - linkSpeed < 0) {
            if (player == 0) {
                throw "Invalid move";
            }
            locationOfLinks[player][link] = make_pair(-1, -1);
            cellWithLink.removeAndDownload(player, -1);
        } else {
            Cell &moveToCell = cells[rowOfLink - linkSpeed][colOfLink];
            char otherCellName = moveToCell.getName();
            bool linkStayedTheSame = moveToCell.moveCellHere(cellWithLink);
            if (!linkStayedTheSame) {
                if (('A' <= otherCellName && otherCellName <= 'H')
                    || ('a' <= otherCellName && otherCellName <= 'h')) 
                {
                    locationOfLinks[(player + 1) % NUMPLAYERS][link] = make_pair(-1, -1);
                }
                locationOfLinks[player][link] =
                    make_pair(rowOfLink - linkSpeed, colOfLink);
            } else {
                locationOfLinks[player][link] = make_pair(-1, -1);
            }
            cellWithLink.removeLink();
        }
    }
}

void Grid::useAbility(Ability a, vector<char> v, int user) {
    if (a == Ability::Firewall) {
        int row = v[0] - '0';
        int col = v[1] - '0';
        if (row < 0 || row >= GRIDSIZE || col < 0 || col >= GRIDSIZE) {
            throw "Invalid use of ability";
        }
        cells[row][col].useAbility(Ability::Firewall, user);
    } else {
        char linkName = v[0];
        int linkIndex;
        int playerIndex;
        if ('a' <= linkName && linkName <= 'h') { 
            linkIndex = linkName - 'a';
            playerIndex = 0;   
        } else if ('A' <= linkName && linkName <= 'H') {
            linkIndex = linkName - 'A';
            playerIndex = 1;   
        } else {
            throw "Invalid link";
        }

        pair<int, int> locationOfLink = locationOfLinks[playerIndex][linkIndex];

        if (a == Ability::Download) {
            locationOfLinks[playerIndex][linkIndex] = make_pair(-1, -1);
        }

        int rowOfLink = locationOfLink.first;
        int colOfLink = locationOfLink.second;

        cells[rowOfLink][colOfLink].useAbility(a, user);
    }
}

void Grid::printBoard(int currentPlayer) {
    textDisplay->draw(currentPlayer);
}
