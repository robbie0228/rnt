#include "graphicsDisplay.h"

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

	// Create window
    win = make_unique<Xwindow>(500, 1000);

	// Create blue background
	win->fillRectangle(0, 0, 500, 1000, 4);

	// Create dividing lines
	size_t pieceSize = 500 / GRIDSIZE;
	size_t lineWidth = 2;
	for (size_t i = 1; i < GRIDSIZE; ++i)
	{
		win->fillRectangle((i * pieceSize) - (lineWidth / 2), 250, lineWidth, 500, 3);
	}
	for (size_t i = 1; i < GRIDSIZE; ++i)
	{
		win->fillRectangle(0, 250 + (i * pieceSize) - (lineWidth / 2), 500, lineWidth, 3);
	}
}

void GraphicsDisplay::notify(Subject &whoFrom) {
    StateType state = whoFrom.getState();
    InfoType info = whoFrom.getInfo();

    int linkDownloader = state.downloadingPlayer - 1;
    // When a player is downloading a link
    if (linkDownloader != -2) {
        if (state.downloadingLinkType == LinkType::Data) {
            downloadedCounts[linkDownloader].first += 1;
        } else {
            downloadedCounts[linkDownloader].second += 1;
        }

        // When two links battle and the downloading link is revealed
        if (state.downloadingLinkIsRevealed) {
            if (state.downloadingLinkName - 'a' >= 0) {
                knownLinks[linkDownloader][state.downloadingLinkName - 'a'] = true;
            } else {
                knownLinks[linkDownloader][state.downloadingLinkName - 'A'] = true;
            }
        }
    }

    int abilityUser = state.playerUsingAbility - 1;
    // When a player is using an ability
    if (state.playerUsingAbility != -2) {
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

void GraphicsDisplay::draw(int currentPlayer) {
    string s = string("Player 1:") + "\n"
        + "Downloaded: " + to_string(downloadedCounts[0].first) + "D, " 
                          + to_string(downloadedCounts[0].second) + "V" + "\n"
        + "Abilities: " + to_string(abilityRemainingCounts[0]) + "\n";

    if (currentPlayer == 0) {
        for (int i = 0; i < 8; ++i) {
            s += links[0][i].first + ": " 
                + links[0][i].second;
            if (i == 3 || i == 7) s += "\n";
            else s += "   ";
        }
    }
    else if (currentPlayer == 1) {
        for (int i = 0; i < 8; ++i) {
            s += links[0][i].first + ": ";
            if (knownLinks[1][i]) {
                s += links[0][i].second;
                if (i == 3 || i == 7) s += "\n";
                else s += "   ";
            } else {
                s += "?";
                if (i == 3 || i == 7) s += "\n";
                else s += "    ";
            }
        }
    }
    else {
        throw "this player does not exist";
    }

    s += string(8, '=') + "\n";
	win->drawString(0,0,s);

    for (int row = 0; row < GRIDSIZE; ++row) {
        for (int col = 0; col < GRIDSIZE; ++col) {
            s = grid[row][col];
        }
        s = "\n";
    }

    s = string(8, '=') + "\n";

    s = string("Player 2:") + "\n"
        + "Downloaded: " + to_string(downloadedCounts[1].first) + "D, " 
                          + to_string(downloadedCounts[1].second) + "V" + "\n"
        + "Abilities: " + to_string(abilityRemainingCounts[1]) + "\n";

    if (currentPlayer == 0) {
        for (int i = 0; i < 8; ++i) {
            s += links[1][i].first + ": ";
            if (knownLinks[0][i]) {
                s += links[1][i].second;
                if (i == 3 || i == 7) s += "\n";
                else s += "   ";
            } else {
                s += "?";
                if (i == 3 || i == 7) s += "\n";
                else s += "    ";
            }
        }
    }
    else if (currentPlayer == 1) {
        for (int i = 0; i < 8; ++i) {
            s += links[1][i].first + ": " 
                + links[1][i].second;
            if (i == 3 || i == 7) s += "\n";
            else s += "   ";
        }
    }
    else {
        throw "this player does not exist";
    }
	win->drawString(0,750,s);
}
