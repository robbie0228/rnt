#include "graphics_display.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(
    vector<vector<char>> grid, 
    vector<vector<pair<char, string>>> links) {
        
    this->grid = grid;
    this->links = links;

    knownLinks = vector<vector<bool>>(NUMPLAYERS,
                                      vector<bool>(NUMLINKS, false));

    downloadedCounts = vector<pair<int, int>>(NUMPLAYERS,
                                              pair<int, int>(0, 0));

    abilityRemainingCounts = vector<int>(NUMPLAYERS, NUMABILITIES);
}

void GraphicsDisplay::doNotify(Subject &whoFrom) {
    StateType state = whoFrom.getState();
    InfoType info = whoFrom.getInfo();

    int linkDownloader = state.downloadingPlayer - 1;
    // When a player is downloading a link
    if (linkDownloader >= 0) {
        if (state.downloadingLinkType == LinkType::Data) {
            downloadedCounts[linkDownloader].first += 1;
        } else {
            downloadedCounts[linkDownloader].second += 1;
        }

        // When two links battle and the downloading link is revealed
        if (state.downloadingLinkIsRevealed) {
            if (state.downloadingLinkName - 'a' >= 0) {
                knownLinks[1][state.downloadingLinkName - 'a'] = true;
            } else {
                knownLinks[0][state.downloadingLinkName - 'A'] = true;
            }
        }
    }

    int abilityUser = state.playerUsingAbility - 1;
    // When a player is using an ability
    if (abilityUser >= 0) {
        abilityRemainingCounts[abilityUser] -= 1;
    }

    grid[info.row][info.col] = info.name;

    // When the cell contains a link
    if ((0 <= info.name - 'a' && info.name - 'a' < NUMLINKS)
        || (0 <= info.name - 'A' && info.name - 'A' < NUMLINKS)) {
        // When a link is revealed using reveal
        if (state.linkIsRevealed) {
            if (info.name - 'a' >= 0) {
                knownLinks[1][info.name - 'a'] = true;
            } else {
                knownLinks[0][info.name - 'A'] = true;
            }
        }
        
        string linkTypeAndStrength = 
                    (info.type == LinkType::Data ? "D" : "V") + 
                    to_string(info.strength);
        if (info.name - 'a' >= 0) {
            links[0][info.name - 'a'] = 
                make_pair(info.name, linkTypeAndStrength);
        } else {
            links[1][info.name - 'A'] = 
                make_pair(info.name, linkTypeAndStrength);
        }
    }
}

pair<size_t, size_t> getOffsetToCenterString(string s, size_t width, size_t height) {
    size_t widthOfString = s.length() * 6;
    size_t paddingWidth = (width - widthOfString) / 2;
    size_t heightOfString = 8;
    size_t paddingHeight = (width - heightOfString) / 2;
    return make_pair(paddingWidth, paddingHeight);
}

void GraphicsDisplay::draw(int currentPlayer) {
    if (!win) {
        // Create window
        win = make_unique<Xwindow>(500, 700);

        draw(0);
    }

    // Create background
    win->fillRectangle(0, 0, 500, 7000, 0);

    // Create grid dividing lines
    size_t pieceSize = 500 / GRIDSIZE;
    size_t lineWidth = 2;
    for (size_t i = 0; i < GRIDSIZE + 1; ++i)
    {
        win->fillRectangle((i * pieceSize) - (lineWidth / 2), 100, lineWidth, 500, 3);
    }
    for (size_t i = 0; i < GRIDSIZE + 1; ++i)
    {
        win->fillRectangle(0, 100 + (i * pieceSize) - (lineWidth / 2), 500, lineWidth, 3);
    }

    int playerInfoPadding = 10;
    win->drawString(playerInfoPadding,
                    playerInfoPadding + 10,
                    "Player 1:");
    string s = string("Downloaded: ") + 
               to_string(downloadedCounts[0].first) + "D, " +
               to_string(downloadedCounts[0].second) + "V";
    win->drawString(playerInfoPadding,
                    playerInfoPadding + 30,
                    s);
    s = "Abilities: " + to_string(abilityRemainingCounts[0]);
    win->drawString(playerInfoPadding,
                    playerInfoPadding + 50,
                    s);

    size_t paddingWidth = 10; // Size of padding around pieces
    for (int row = 0; row < GRIDSIZE; ++row) {
        for (int col = 0; col < GRIDSIZE; ++col) {
            string name;
            int colour;
            if (grid[row][col] == '.') {
                colour = 0;
                name = "";
            } else if ('a' <= grid[row][col] && grid[row][col] <= 'h') {
                int linkIndex = grid[row][col] - 'a';
                if (currentPlayer == 0) {
                    if (links[0][linkIndex].second < "E") {
                        colour = 3;
                    } else {
                        colour = 2;
                    }
                    name = string(1, grid[row][col]) + ":" +
                           links[0][linkIndex].second;
                } else {
                    if (knownLinks[1][linkIndex]) {
                        if (links[0][linkIndex].second < "E") {
                            colour = 3;
                        } else {
                            colour = 2;
                        }
                        name = string(1, grid[row][col]) + ":" +
                               links[0][linkIndex].second;
                    } else {
                        colour = 1;
                        name = string(1, grid[row][col]);
                    }
                }
            } else if ('A' <= grid[row][col] && grid[row][col] <= 'H') {
                int linkIndex = grid[row][col] - 'A';
                if (currentPlayer == 1) {
                    if (links[1][linkIndex].second < "E") {
                        colour = 3;
                    } else {
                        colour = 2;
                    }
                    name = string(1, grid[row][col]) + ":" +
                           links[1][linkIndex].second;
                } else {
                    if (knownLinks[0][linkIndex]) {
                        if (links[1][linkIndex].second < "E") {
                            colour = 3;
                        } else {
                            colour = 2;
                        }
                        name = string(1, grid[row][col]) + ":" +
                               links[1][linkIndex].second;
                    } else {
                        colour = 1;
                        name = string(1, grid[row][col]);
                    }
                }
            } else if (grid[row][col] == 'S') {
                colour = 5;
                name = string(1, grid[row][col]);
            } else {
                colour = 4;
                name = string(1, grid[row][col]);
            }

            // Add rectangle with the notifying piece's colour
            win->fillArc(pieceSize * col + paddingWidth, 
                               100 + pieceSize * row + paddingWidth, 
                               pieceSize - (2 * paddingWidth), 
                               pieceSize - (2 * paddingWidth), 
                               0, 23040,
                               colour);
            pair<size_t, size_t> offset = 
                getOffsetToCenterString(name, 
                                        pieceSize - (2 * paddingWidth),
                                        pieceSize - (2 * paddingWidth));
            win->drawString(pieceSize * col + paddingWidth + offset.first, 
                            110 + pieceSize * row + paddingWidth + offset.second, 
                            name);
        }
    }

    win->drawString(playerInfoPadding,
                    playerInfoPadding + 610,
                    "Player 2:");
    s = string("Downloaded: ") + 
               to_string(downloadedCounts[1].first) + "D, " +
               to_string(downloadedCounts[1].second) + "V";
    win->drawString(playerInfoPadding,
                    playerInfoPadding + 630,
                    s);
    s = "Abilities: " + to_string(abilityRemainingCounts[1]);
    win->drawString(playerInfoPadding,
                    playerInfoPadding + 650,
                    s);
}
