#include "player.h"
#include <iostream>
using namespace std;

Player::Player(): downloadedDataCount{0}, downloadedVirusCount{0} {
    ability = {make_pair(1, 2)}
}

Status Player::checkStatus() {
    if (downloadedDataCount >= 4) return Status::Win;
    else if (downloadedVirusCount >= 4) return Status::Lose;
    else return Status::InPlay;
}

void Player::printAbilities(ostream& out) {
    out << "not implemented yet, print abilities with ID and used status" << std::endl;
}