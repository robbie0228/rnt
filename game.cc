#include <vector>
#include "game.h"
#include "grid.h"
#include "player.h"
#include "enums.h"
using namespace std;

// helper functions

int charLinkToInt(char c) {
    if (c == 'a' || c == 'A') {
        return 0;
    } if (c == 'b' || c == 'B') {
        return 1;
    } if (c == 'c' || c == 'C') {
        return 2;
    } if (c == 'd' || c == 'D') {
        return 3;
    } if (c == 'e' || c == 'E') {
        return 4;
    } if (c == 'f' || c == 'F') {
        return 5;
    } if (c == 'g' || c == 'G') {
        return 6;
    } if (c == 'h' || c == 'H') {
        return 7;
    }
}


//implementations

Game::Game() : grid { Grid() }, currentPlayer{ 1 } {
    Player p1 = Player();
    Player p2 = Player();

    this->players.push_back(p1);
    this->players.push_back(p2);
}

void Game::init() {
    return;
}

void Game::move(char link, Direction dir) {
    this->grid.move(currentPlayer, charLinkToInt(link), dir);
    if (currentPlayer == 1) {
        currentPlayer = 2;
    } else if (currentPlayer == 2) {
        currentPlayer = 1;
    }
}

ostream &operator<<(ostream &out, const Game &g) {
    out << this->grid << endl;
    return out;
}


