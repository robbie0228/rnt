#include "game.h"
using namespace std;

// This helper function converts bewteen a Link's name and corresponding index
int charLinkToInt(char c)
{
    if ('a' <= c && c <= 'h')
        return c - 'a';
    else if ('A' <= c && c <= 'H')
        return c - 'A';
    else
        throw "!Invalid Link!";
}

Game::Game(vector<pair<int, vector<pair<Ability, bool>>>> cmdAllAbilities,
           vector<pair<int, vector<Link>>> cmdAllLinks, bool useGraphics)
    : currentPlayer{0}, abilityUsedCount{0}
{

    Player p1 = Player(1);
    Player p2 = Player(2);

    if (cmdAllAbilities.size())
    {
        for (unsigned int i = 0; i < cmdAllAbilities.size(); ++i)
        {
            if (cmdAllAbilities[i].first == 1)
                p1.overrideAbilities(cmdAllAbilities[i].second);
            else if (cmdAllAbilities[i].first == 2)
                p2.overrideAbilities(cmdAllAbilities[i].second);
        }
    }

    this->players.push_back(p1);
    this->players.push_back(p2);

    vector<Player *> playerPointers;
    for (int i = 0; i < NUMPLAYERS; ++i)
    {
        playerPointers.emplace_back(&(players[i]));
    }

    vector<vector<Link *>> allLinks;
    for (int i = 0; i < NUMPLAYERS; ++i)
    {
        int playerNumber = i + 1;
        int cmdSchemeFoundAt = -1;
        if (cmdAllLinks.size())
        {
            for (unsigned int j = 0; j < cmdAllLinks.size(); ++j)
            {
                if (cmdAllLinks[j].first == playerNumber)
                {
                    cmdSchemeFoundAt = j;
                    break;
                }
            }
        }
        if (cmdSchemeFoundAt == -1)
            allLinks.emplace_back(players[i].init());
        else
            allLinks.emplace_back(players[i]
                                      .cmdInit(
                                          cmdAllLinks[cmdSchemeFoundAt]
                                              .second));
    }

    grid = make_unique<Grid>(playerPointers, allLinks, useGraphics);
}

void Game::move(char link, Direction dir)
{
    if ((link < 'a' && currentPlayer == 0) ||
        (link >= 'a' && currentPlayer == 1))
    {
        throw "Cannot move opponent's piece!";
    }

    this->grid->move(currentPlayer, charLinkToInt(link), dir);

    if (currentPlayer == 0)
    {
        currentPlayer = 1;
    }
    else if (currentPlayer == 1)
    {
        currentPlayer = 0;
    }

    abilityUsedCount = 0;
}

pair<int, bool> Game::verifyAbility(int abilityID) const {
    pair<Ability, bool> abilityPair = players[currentPlayer].getAbility(abilityID);
    if (abilityPair.first == Ability::Firewall || abilityPair.first == Ability::Ambush) {
        return make_pair(2, abilityPair.second);
    }
    else if (abilityPair.first == Ability::Download ||
             abilityPair.first == Ability::Boost ||
             abilityPair.first == Ability::Scan ||
             abilityPair.first == Ability::Polarize ||
             abilityPair.first == Ability::Uber ||
             abilityPair.first == Ability::Whey)
    {
        return make_pair(1, abilityPair.second);
    }
    return make_pair(0, false);
}

void Game::useAbility(int abilityID, vector<char> useAbilityInfo)
{
    if (abilityUsedCount >= MAXABILITYUSE)
    {
        throw "Only use one ability per turn!";
    }
    else
    {
        Ability abilityName =
            players[currentPlayer].useAbility(abilityID, useAbilityInfo);

        grid->useAbility(abilityName, useAbilityInfo, currentPlayer + 1);
        abilityUsedCount += 1;
    }
}

void Game::printBoard() const {
    grid->printBoard(currentPlayer);
}

void Game::printAbilities(ostream& out) const {
    players[currentPlayer].printAbilities(out);
}

int Game::checkStatus() const {
    int curStatus = -1;
    for (int i = 0; i < NUMPLAYERS; i++)
    {
        if (players[i].checkStatus() == PlayStatus::Win)
        {
            curStatus = i + 1;
        }
        else if (players[i].checkStatus() == PlayStatus::Lose)
        {
            curStatus = (i + 1) % NUMPLAYERS + 1;
        }
    }
    
    return curStatus;
}
