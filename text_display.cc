#include "text_display.h"
using namespace std;

TextDisplay::TextDisplay(vector<vector<char>> grid,
                         vector<vector<pair<char, string>>> links)
{
    this->grid = grid;
    this->links = links;

    knownLinks = vector<vector<bool>>(NUMPLAYERS,
                                      vector<bool>(NUMLINKS, false));

    downloadedCounts = vector<pair<int, int>>(NUMPLAYERS,
                                              pair<int, int>(0, 0));

    abilityRemainingCounts = vector<int>(NUMPLAYERS, NUMABILITIES);
}

void TextDisplay::doNotify(Subject &whoFrom)
{
    StateType state = whoFrom.getState();
    InfoType info = whoFrom.getInfo();

    int linkDownloader = state.downloadingPlayer - 1;
    // When a player is downloading a link
    if (linkDownloader >= 0)
    {
        if (state.downloadingLinkType == LinkType::Data)
        {
            downloadedCounts[linkDownloader].first += 1;
        }
        else
        {
            downloadedCounts[linkDownloader].second += 1;
        }

        // When two links battle and the downloading link is revealed
        if (state.downloadingLinkName - 'a' >= 0)
        {
            knownLinks[1][state.downloadingLinkName - 'a'] = true;
        }
        else
        {
            knownLinks[0][state.downloadingLinkName - 'A'] = true;
        }
    }

    int abilityUser = state.playerUsingAbility - 1;
    // When a player is using an ability
    if (abilityUser >= 0)
    {
        abilityRemainingCounts[abilityUser] -= 1;
    }

    grid[info.row][info.col] = info.name;

    // When the cell contains a link
    if ((0 <= info.name - 'a' && info.name - 'a' < NUMLINKS) ||
        (0 <= info.name - 'A' && info.name - 'A' < NUMLINKS))
    {
        // When a link is revealed using reveal
        if (state.linkIsRevealed)
        {
            if (info.name - 'a' >= 0)
            {
                knownLinks[1][info.name - 'a'] = true;
            }
            else
            {
                knownLinks[0][info.name - 'A'] = true;
            }
        }

        string linkTypeAndStrength =
            (info.type == LinkType::Data ? "D" : "V") +
            to_string(info.strength);
        if (info.name - 'a' >= 0)
        {
            links[0][info.name - 'a'] =
                make_pair(info.name, linkTypeAndStrength);
        }
        else
        {
            links[1][info.name - 'A'] =
                make_pair(info.name, linkTypeAndStrength);
        }
    }
}

void TextDisplay::draw(ostream &out, int currentPlayer)
{
    out << "Player 1:" << endl
        << "Downloaded: " << downloadedCounts[0].first << "D, "
        << downloadedCounts[0].second << "V" << endl
        << "Abilities: " << abilityRemainingCounts[0] << endl;

    if (currentPlayer == 0)
    {
        for (int i = 0; i < 8; ++i)
        {
            out << links[0][i].first << ": "
                << links[0][i].second;
            if (i == 3 || i == 7)
                out << endl;
            else
                out << "   ";
        }
    }
    else if (currentPlayer == 1)
    {
        for (int i = 0; i < 8; ++i)
        {
            out << links[0][i].first << ": ";
            if (knownLinks[1][i])
            {
                out << links[0][i].second;
                if (i == 3 || i == 7)
                    out << endl;
                else
                    out << "   ";
            }
            else
            {
                out << "?";
                if (i == 3 || i == 7)
                    out << endl;
                else
                    out << "    ";
            }
        }
    }
    else
    {
        throw "!This player does not exist!";
    }

    out << string(8, '=') << endl;

    for (int row = 0; row < GRIDSIZE; ++row)
    {
        for (int col = 0; col < GRIDSIZE; ++col)
        {
            out << grid[row][col];
        }
        out << endl;
    }

    out << string(8, '=') << endl;

    out << "Player 2:" << endl
        << "Downloaded: " << downloadedCounts[1].first << "D, "
        << downloadedCounts[1].second << "V" << endl
        << "Abilities: " << abilityRemainingCounts[1] << endl;

    if (currentPlayer == 0)
    {
        for (int i = 0; i < 8; ++i)
        {
            out << links[1][i].first << ": ";
            if (knownLinks[0][i])
            {
                out << links[1][i].second;
                if (i == 3 || i == 7)
                    out << endl;
                else
                    out << "   ";
            }
            else
            {
                out << "?";
                if (i == 3 || i == 7)
                    out << endl;
                else
                    out << "    ";
            }
        }
    }
    else if (currentPlayer == 1)
    {
        for (int i = 0; i < 8; ++i)
        {
            out << links[1][i].first << ": "
                << links[1][i].second;
            if (i == 3 || i == 7)
                out << endl;
            else
                out << "   ";
        }
    }
    else
    {
        throw "!This player does not exist!";
    }
}
