#include "player.h"
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

pair<Ability, bool> Player::getAbility(int abilityID) {
    return abilities[abilityID - 1];
}

Ability Player::useAbility(int abilityID) {
    abilities[abilityID - 1].second = false;
    return abilities[abilityID - 1].first;
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


