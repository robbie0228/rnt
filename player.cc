#include "player.h"
#include "link.h"

using namespace std;

// implementations

Player::Player(int playerNumber): 
                    downloadedDataCount{0}, 
                    downloadedVirusCount{0}, 
                    playerNumber{playerNumber} {
    abilities = {make_pair(Ability::Boost, 1),
               make_pair(Ability::Firewall, 1),
               make_pair(Ability::Download, 1),
               make_pair(Ability::Scan, 1),
               make_pair(Ability::Polarize, 1)
               };
}

void Player::overrideAbilities(vector<pair<Ability, bool>> cmdAbilities) {
    abilities = cmdAbilities;
}

vector<Link *> Player::init() {
    vector<Link *> linkPointers;
    for (int link = 0; link < NUMLINKS; ++link) {
        // Initialize link
        links.emplace_back(
            Link((link < 4 ? LinkType::Virus : LinkType::Data),
                 (link % 4) + 1,
                 (char)((playerNumber == 1 ? 'a' : 'A') + link)
            )
        );
    }
    for (int i = 0; i < NUMLINKS; ++i) {
        linkPointers.emplace_back(&(links[i]));
    }
    return linkPointers;
}

vector<Link *> Player::cmdInit(vector<Link> cmdLinks) {
    vector<Link *> linkPointers;
    links = cmdLinks;
    for (int i = 0; i < NUMLINKS; ++i) {
        linkPointers.emplace_back(&(links[i]));
    }
    return linkPointers;
}

bool Player::isMyLink(char linkName) {
    if (playerNumber == 1) {
        return ('a' <= linkName && linkName <= 'h') && 
                links[linkName - 'a'].getType() != LinkType::NoType;
    } else {
        return ('A' <= linkName && linkName <= 'H') && 
                links[linkName - 'A'].getType() != LinkType::NoType;
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

PlayStatus Player::checkStatus() {
    if (downloadedDataCount >= 4) {
        return PlayStatus::Win;
    }
    else if (downloadedVirusCount >= 4) {
        return PlayStatus::Lose;
    }
    else {
        return PlayStatus::InPlay;
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
            case Ability::Ambush   : abilityName = "Ambush"     ; break;
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
        case Ability::Scan :
            if (!isMyLink(abilityInfo[0]) && !isEnemyLink(abilityInfo[0])) {
                throw "Invalid use of ability";
            }
            break;
        case Ability::Firewall :
            if ((abilityInfo[0] - '0' < 0) || 
                (abilityInfo[0] - '0' >= GRIDSIZE) || 
                (abilityInfo[1] - '0' < 0) || 
                (abilityInfo[1] - '0' >= GRIDSIZE)) {

                throw "Invalid use of ability";
            }
            break;
        case Ability::Ambush :
            if (!isMyLink(abilityInfo[0]) || !isEnemyLink(abilityInfo[1])) {
                throw "Invalid use of ability";
            }
            break;
        case Ability::Uber :
            if (!isMyLink(abilityInfo[0])) {
                throw "Invalid use of ability";
            }
            break;
        default :
            break;
    }
    
    abilities[abilityID - 1].second = false;
    return abilities[abilityID - 1].first;
}

int getPlayerNumFromLink(char name) {
    return name < 'a' ? 2 : 1;
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
    if (('a' <= state.downloadingLinkName && 
         state.downloadingLinkName <= 'h') || 
        ('A' <= state.downloadingLinkName && 
         state.downloadingLinkName <= 'H')) {
        if (getPlayerNumFromLink(state.downloadingLinkName) == 
            playerNumber) {
            if (playerNumber == 1) {
                links[state.downloadingLinkName - 'a'].setType(
                    LinkType::NoType);
            } else {
                links[state.downloadingLinkName - 'A'].setType(
                    LinkType::NoType);
            }
        }
    }
}
