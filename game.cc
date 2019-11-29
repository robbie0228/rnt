#include "game.h"
using namespace std;

// helper functions

int charLinkToInt(char c) {
    if ('a' <= c && c <= 'h') {
        return c - 'a';
    } else if ('A' <= c && c <= 'H') {
        return c - 'A';
    }
    throw "Invalid Link";
}


//implementations

Game::Game(): 
    grid{Grid()}, currentPlayer{0} {

    Player p1 = Player(1);
    Player p2 = Player(2);

    this->players.push_back(p1);
    this->players.push_back(p2);
}

void Game::init() {
    return;
}

void Game::move(char link, Direction dir) {
    this->grid.move(currentPlayer, charLinkToInt(link), dir);
    if (currentPlayer == 0) {
        currentPlayer = 1;
    } else if (currentPlayer == 1) {
        currentPlayer = 0;
    }
}

ostream &operator<<(ostream &out, const Game &g) {
    out << g.grid;
    return out;
}

void Game::printAbilities(ostream& out){
    players[currentPlayer].printAbilities(out);
}

pair<int, bool> Game::verifyAbility(int abilityID) {
    pair<Ability, bool> abilityPair = players[currentPlayer].getAbility(abilityID);
    if (abilityPair.first == Ability::Firewall) {
        return make_pair(2, abilityPair.second);
    } else if (abilityPair.first == Ability::Download || abilityPair.first == Ability::Boost || 
        abilityPair.first == Ability::Scan || abilityPair.first == Ability::Polarize) {
        return make_pair(1, abilityPair.second);
    }
    return make_pair(0, false);
}

void Game::useAbility(int abilityID, vector<char> useAbilityInfo) {
    Ability abilityName = players[currentPlayer].useAbility(abilityID, useAbilityInfo);
    grid.useAbility(abilityName, useAbilityInfo);
}
