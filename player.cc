#include "player.h"
#include <iostream>
using namespace std;

Player::Player(int playerNumber): downloadedDataCount{0}, downloadedVirusCount{0}, playerNumber{playerNumber} {
    abilities = {make_pair(Ability::Firewall, 1),
                 make_pair(Ability::Download, 1),
                 make_pair(Ability::Boost, 1),
                 make_pair(Ability::Scan, 1),
                 make_pair(Ability::Polarize, 1)};
}

Status Player::checkStatus() {
    if (downloadedDataCount >= 4) {
        return Status::Win;
    }
    else if (downloadedVirusCount >= 4) {
        return Status::Lose;
    }
    else {
        return Status::InPlay;
    }
}

void Player::printAbilities(ostream& out) const{
    out << "not implemented yet, print abilities with ID and used status";
}

void Player::print(ostream& out) const{
    out << "Player " << playerNumber << ":" << endl;
    out << "Downloaded: " << downloadedDataCount << "D, "
        << downloadedVirusCount << "V" << endl;
    out << "Abilities: " << abilities.size() << endl;
}

Ability Player::getAbility(int abilityID) {
    bool isAvailable = abilities[abilityID - 1].second;
    if (isAvailable) {
        return abilities[abilityID - 1].first;
    }
    else {
        throw "invalid ability";
    }
}

void Player::notify(Subject &whoFrom) {
    StateType state = whoFrom.getState();
    if (state.downloadingPlayer == playerNumber) {
        if (state.downloadingLinkType == LinkType::Data) {
            downloadedDataCount += 1;
        } else {
            downloadedVirusCount += 1;
        }
    }
}


