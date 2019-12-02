#include "grid.h"
#include "player.h"
#include "enums.h"

using namespace std;

Grid::Grid(vector<Player *> players, 
           vector<vector<Link *>> linkPointers, 
           bool useGraphics): useGraphics{useGraphics} {
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

    // construct the displays

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
    graphicsDisplay = make_unique<GraphicsDisplay>(displayGrid, displayLinks);

    for (int row = 0; row < GRIDSIZE; ++row) {
        for (int col = 0; col < GRIDSIZE; ++col) {
            for (int player = 0; player < NUMPLAYERS; ++player) {
                cells[row][col].attach(players[player]);
            }
            cells[row][col].attach(textDisplay.get());
            cells[row][col].attach(graphicsDisplay.get());
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
            cellWithLink.removeAndDownload(player + 1, -1);
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
            cellWithLink.removeAndDownload(player + 1, -1);
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

void Grid::useAbility(Ability a, vector<char> abilityInfo, int user) {
    if (a == Ability::Firewall) {
        int row = abilityInfo[0] - '0';
        int col = abilityInfo[1] - '0';
        if (row < 0 || row >= GRIDSIZE || col < 0 || col >= GRIDSIZE) {
            throw "Invalid use of ability";
        }
        cells[row][col].useAbility(Ability::Firewall, user);
    } else if (a == Ability::Ambush) {
        int myLinkIndex;
        int myIndex;
        int enemyLinkIndex;
        int enemyIndex;

        char myLink = abilityInfo[0];
        char enemyLink = abilityInfo[1];

        getIndicesFromName(myLink, myLinkIndex, myIndex);
        getIndicesFromName(enemyLink, enemyLinkIndex, enemyIndex);

        int enemyRow = locationOfLinks[enemyIndex][enemyLinkIndex].first;
        int enemyCol = locationOfLinks[enemyIndex][enemyLinkIndex].second;
        int myRow = locationOfLinks[myIndex][myLinkIndex].first;
        int myCol = locationOfLinks[myIndex][myLinkIndex].second;

        bool enemyWon = cells[enemyRow][enemyCol].
                            moveCellHere(cells[myRow][myCol]);
        cells[myRow][myCol].removeLink();
        if (!enemyWon) {
            cells[myRow][myCol].
                moveCellHere(cells[enemyRow][enemyCol]);
            cells[enemyRow][enemyCol].removeLink();
        }

    } else {
        char linkName = abilityInfo[0];
        int linkIndex;
        int playerIndex;
        getIndicesFromName(linkName, linkIndex, playerIndex);

        int rowOfLink = locationOfLinks[playerIndex][linkIndex].first;
        int colOfLink = locationOfLinks[playerIndex][linkIndex].second;

        cells[rowOfLink][colOfLink].useAbility(a, user);

        if (a == Ability::Download) {
            locationOfLinks[playerIndex][linkIndex] = make_pair(-1, -1);
        }
    }
}

void Grid::printBoard(int currentPlayer) {
    textDisplay->draw(currentPlayer);
    if (useGraphics) graphicsDisplay->draw(currentPlayer);
}
