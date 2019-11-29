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

int Game::verifyAbility(int abilityID) {
    Ability a = players[currentPlayer].getAbility(abilityID);
    if (a == Ability::Firewall) {
        return 2;
    } else if (a == Ability::Download || a == Ability::Boost || 
        a == Ability::Scan || a == Ability::Polarize) {
        return 1;
    }
    return 0;
}

void Game::useAbility(int abilityID, vector<char> useAbilityInfo) {
    grid.useAbility(abilityName, useAbilityInfo);
}
