#include "player.h"
#include <iostream>
using namespace std;

Player::Player(): downloadedDataCount{0}, downloadedVirusCount{0} {
    ability = {make_pair(Ability::Firewall, 1),
               make_pair(Ability::Download, 1),
               make_pair(Ability::Boost, 1),
               make_pair(Ability::Scan, 1),
               make_pair(Ability::Polarize, 1)};
}

Status Player::checkStatus() {
    if (downloadedDataCount >= 4) return Status::Win;
    else if (downloadedVirusCount >= 4) return Status::Lose;
    else return Status::InPlay;
}

void Player::printAbilities(ostream& out) {
    out << "not implemented yet, print abilities with ID and used status" << endl;
}

Ability Player::useAbility(int abilityID) {
    bool isAvailable = ability[abilityID - 1].second;
    if (isAvailable) return ability[abilityID - 1].first;
    else throw "invalid ability";
}

