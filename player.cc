#include "player.h"
#include "link.h"

using namespace std;

Player::Player(int playerNumber): 
    downloadedDataCount{0}, downloadedVirusCount{0}, 
    playerNumber{playerNumber} {
    ability = {make_pair(Ability::Firewall, 1),
               make_pair(Ability::Download, 1),
               make_pair(Ability::Boost, 1),
               make_pair(Ability::Scan, 1),
               make_pair(Ability::Polarize, 1)};
}

std::vector<Link *> Player::init() {
    vector<Link *> linkPointers;
    for (int link = 0; link < 8; ++link) {
        // Initialize link
        links.emplace_back(
            Link((link < 4 ? LinkType::Data : LinkType::Virus),
                 link,
                 (char)((playerNumber == 1 ? 'a' : 'A') + link)
            )
        );
    }
    for (int i = 0; i < links.size(); ++i) {
        linkPointers.emplace_back(&(links[i]));
    }
    return linkPointers;
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

void Player::printAbilities(ostream& out) {
    out << "not implemented yet, print abilities with ID and used status";
}

pair<Ability, bool> Player::getAbility(int abilityID) {
    return ability[abilityID - 1];
}

Ability Player::useAbility(int abilityID, vector<char> abilityInfo) {
    if (ability[abilityID - 1].first == Ability::Boost) {
        if (playerNumber == 1 && 'a' > abilityInfo[0] && abilityInfo[0] > 'h') {
            throw "Invalid ability";
        } else if (playerNumber == 2 && 'A' > abilityInfo[0] && abilityInfo[0] > 'H') {
            throw "Invalid ability";
        }
    } else if (ability[abilityID - 1].first == Ability::Polarize) {
        if (abilityInfo[0] < 'A' 
            || ('H' < abilityInfo[0] && abilityInfo[0] < 'a') 
            ||  abilityInfo[0] > 'h') 
        {
            throw "Invalid ability";
        }
    }
    ability[abilityID - 1].second = false;
    return ability[abilityID - 1].first;
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

