#include "player.h"
#include "link.h"

using namespace std;

// implementations

Player::Player(int playerNumber): 
    downloadedDataCount{0}, downloadedVirusCount{0}, 
    playerNumber{playerNumber} {
    abilities = {make_pair(Ability::Firewall, 1),
               make_pair(Ability::Download, 1),
               make_pair(Ability::Boost, 1),
               make_pair(Ability::Scan, 1),
               make_pair(Ability::Polarize, 1)};
}

void Player::cmdInitAbilities(string abilities){
    vector<pair<Ability, bool>> abilitiesInit;
    for (int i = 0; i < NUMABILITIES; ++i) {
        char ability = abilities[i];
        switch(ability) {
            case 'F' : 
                abilitiesInit.emplace_back(make_pair(Ability::Firewall, true));
                break;
            case 'D' :
                abilitiesInit.emplace_back(make_pair(Ability::Download, true));
                break;
            case 'L' : 
                abilitiesInit.emplace_back(make_pair(Ability::Boost, true));
                break;
            case 'S' : 
                abilitiesInit.emplace_back(make_pair(Ability::Scan, true));
                break;
            case 'P' : 
                abilitiesInit.emplace_back(make_pair(Ability::Polarize, true));
                break;
            case 'U' : 
                abilitiesInit.emplace_back(make_pair(Ability::Uber, true));
                break;
            case 'W' : 
                abilitiesInit.emplace_back(make_pair(Ability::Whey, true));
                break;
            case 'C' : 
                abilitiesInit.emplace_back(make_pair(Ability::Cop, true));
                break;
            default  :
                throw "Invalid ability";
        }
    }
    this->abilities = abilitiesInit;
}


vector<Link *> Player::init() {
    vector<Link *> linkPointers;
    for (int link = 0; link < NUMLINKS; ++link) {
        // Initialize link
        links.emplace_back(
            Link((link < 4 ? LinkType::Data : LinkType::Virus),
                 (link % 4) + 1,
                 (char)((playerNumber == 1 ? 'a' : 'A') + link)
            )
        );
    }
    for (unsigned int i = 0; i < links.size(); ++i) {
        linkPointers.emplace_back(&(links[i]));
    }
    return linkPointers;
}

void Player::cmdInitLinks(string links) {
    vector<Link> linksInit;
    for (int i = 0, j = 0; i < NUMLINKS * 2; i += 2, ++j) {
        LinkType linkTempType = (links[i] == 'D' ? LinkType::Data : 
                                                   LinkType::Virus);
        int linkTempStrength = links[i + 1];
        char linkTempName = (playerNumber == 1 ? 'a' : 'A') + j;
        linksInit.emplace_back(Link
                                (linkTempType, linkTempStrength, linkTempName));
    }
    this->links = linksInit;
}

bool Player::isMyLink(char linkName) {
    if (playerNumber == 1) {
        return ('a' <= linkName && linkName <= 'h');
    } else {
        return ('A' <= linkName && linkName <= 'H');
    }
    return false;
}

bool Player::isEnemyLink(char linkName) {
    if (playerNumber == 1) {
        return ('A' <= linkName && linkName <= 'H');
    } else {
        return ('a' <= linkName && linkName <= 'h');
    }
    return false;
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
    out << "Player " << playerNumber << "'s Abilities:" << endl;
    for (int i = 0; i < 5; ++i) {
        string abilityName;

        switch (abilities[i].first) {
            case Ability::Boost    : abilityName = "Link Boost" ; break;
            case Ability::Download : abilityName = "Download"   ; break;
            case Ability::Firewall : abilityName = "Firewall"   ; break;
            case Ability::Polarize : abilityName = "Polarize"   ; break;
            case Ability::Scan     : abilityName = "Scan"       ; break;
            case Ability::Cop      : abilityName = "Cop"        ; break;
            case Ability::Uber     : abilityName = "Uber"       ; break;
            case Ability::Whey     : abilityName = "Whey"       ; break;
            default                : throw "ability unavailable";
        }

        out << i + 1 << ": " << abilityName << ", ";

        if (abilities[i].second) out << "Unused" << endl;
        else out << "Used" << endl;
    }
}

pair<Ability, bool> Player::getAbility(int abilityID) {
    return abilities[abilityID - 1];
}

Ability Player::useAbility(int abilityID, vector<char> abilityInfo) {
    switch(abilities[abilityID - 1].first) {
        case Ability::Boost :
            if (!isMyLink(abilityInfo[0])) {
                throw "Invalid use of ability";
            }
            break;
        case Ability::Polarize :
            if (!isMyLink(abilityInfo[0]) && !isEnemyLink(abilityInfo[0])) {
                throw "Invalid use of ability";
            }
            break;
        case Ability::Download :
            if (!isEnemyLink(abilityInfo[0])) {
                throw "Invalid use of ability";
            }
            break;
        default :
            break;
    }
    
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
