#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
using namespace std;

vector<pair<Ability, bool>> cmdInitAbilities(string s){
    vector<pair<Ability, bool>> abilitiesInit;
    for (int i = 0; i < NUMABILITIES; ++i) {
        char ability = s[i];
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
    return abilitiesInit;
}

vector<Link> cmdInitLinks(int playerNumber, string links) {
    vector<Link> linksInit;
    for (int i = 0, j = 0; j < NUMLINKS; i += 2, ++j) {
        LinkType linkTempType = (links[i] == 'D' ? LinkType::Data : 
                                                   LinkType::Virus);
        int linkTempStrength = links[i + 1] - '0';
        char linkTempName = (playerNumber == 1 ? 'a' : 'A') + j;
        linksInit.emplace_back(Link
                                (linkTempType, linkTempStrength, linkTempName));
    }
    return linksInit;
}

int main(int argc, char* argv[])
{
    // empty, 1 or 2 pairs of <playerNumber, 5 pairs of <Ability, notUsed?>>
    vector<pair<int, vector<pair<Ability, bool>>>> allAbilities;
    // empty, 1 or 2 pairs of <playerNumber, 8 Links>
    vector<pair<int, vector<Link>>> allLinks;
    // Whether or not to use graphics
    bool useGraphics;
    
    try {
        if (argc > MAXCMDLINEARGS + 1) {
            throw "Too many command line arguments given";
        }
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];
            if (arg == "-ability1") {
                string abilities = argv[i + 1];
                if (abilities.length() != NUMABILITIES) throw "Invalid abilities";
                string sorted = abilities;
                sort(sorted.begin(), sorted.end());
                for (int j = 1; j < NUMABILITIES - 1; ++j) {
                    if (sorted[j] == sorted[j - 1] && sorted[j] == sorted[j + 1]) 
                        throw "Invalid abilities";
                }
                ++i;
                allAbilities.emplace_back(make_pair(1, cmdInitAbilities(abilities)));
            }
            else if (arg == "-ability2") {
                string abilities = argv[i + 1];
                if (abilities.length() != NUMABILITIES) throw "Invalid abilities";
                string sorted = abilities;
                sort(sorted.begin(), sorted.end());
                for (int j = 1; j < NUMABILITIES - 1; ++j) {
                    if (sorted[j] == sorted[j - 1] && sorted[j] == sorted[j + 1])
                        throw "Invalid abilities";
                }
                ++i;
                allAbilities.emplace_back(make_pair(2, cmdInitAbilities(abilities)));
            }
            else if (arg == "-link1") {
                string links = argv [i + 1];
                if (links.length() != NUMLINKS * 2) throw "Invalid links";
                vector<bool> verification = vector<bool>(NUMLINKS, false);
                for (int j = 1; j < NUMLINKS * 2 ; j += 2) {
                    if (links[j - 1] == 'D') verification[links[j] - '0' - 1] = true;
                    else if (links[j - 1] == 'V') verification[links[j] - '0' + 3] = true;
                }
                for (int j = 0; j < NUMLINKS; ++j) {
                    if (!verification[j]) throw "Invalid links";
                }
                ++i;
                allLinks.emplace_back(make_pair(1, cmdInitLinks(1, links)));
            }
            else if (arg == "-link2") {
                string links = argv [i + 1];
                if (links.length() != NUMLINKS * 2) throw "Invalid links";
                vector<bool> verification = vector<bool>(NUMLINKS, false);
                for (int j = 1; j < NUMLINKS * 2 ; j += 2) {
                    if (links[j - 1] == 'D') verification[links[j] - '0' - 1] = true;
                    else if (links[j - 1] == 'V') verification[links[j] - '0' + 3] = true;
                }
                for (int j = 0; j < NUMLINKS; ++j) {
                    if (!verification[j]) throw "Invalid links";
                }
                ++i;
                allLinks.emplace_back(make_pair(2, cmdInitLinks(2, links)));
            }
            else if (arg == "-graphics") {
                useGraphics = true;
            }
            else throw "Invalid command line argument given";
        }
    } catch (char const *e) {
        cout << e << endl;
        cout << endl;
        exit(1);
    }

    Game game(allAbilities, allLinks, useGraphics);

    string cmd;

    vector<ifstream> fstreams;
    istream *stream = &cin;

    bool moreToRead = true;
    if (!(cin >> cmd)) {
        exit(0);
    }
    while (moreToRead)
    {
        try
        {
            if (cmd == "move")
            {
                char link;
                (*stream) >> link;
                Direction dir;
                string dirtemp;
                (*stream) >> dirtemp;
                if (dirtemp == "left") dir = Direction::Left;
                else if (dirtemp == "right") dir = Direction::Right;
                else if (dirtemp == "up") dir = Direction::Up;
                else if (dirtemp == "down") dir = Direction::Down;
                else throw "invalid direction";
                game.move(link, dir);
            }
            else if (cmd == "abilities")
            {
                game.printAbilities(cout);
                cout << endl;
            }
            else if (cmd == "ability")
            {
                int abilityID;
                (*stream) >> abilityID;
                pair<int, bool> abilityInfo = game.verifyAbility(abilityID);
                char c;
                vector<char> useAbilityInfo;
                for (int i = 0; i < abilityInfo.first; i++) {
                    (*stream) >> c;
                    useAbilityInfo.emplace_back(c);
                }
                if (abilityInfo.second) {
                    game.useAbility(abilityID, useAbilityInfo);
                }
                else {
                    cout << "Invalid ability" << endl;
                    cout << endl;
                }
            }
            else if (cmd == "board")
            {
                game.printBoard();
                cout << endl;
            }
            else if (cmd == "sequence")
            {
                string fileName;
                (*stream) >> fileName;
                fstreams.emplace_back(ifstream{fileName});
                stream = &(fstreams.back());
            }
            else if (cmd == "quit")
            {
                break;
            }
            else
            {
                throw "invalid command";
            }
        } catch (char const *e) {
            cout << e << endl;
            cout << endl;
        }
        if (game.checkStatus() != -1) {
            if (game.checkStatus() == 1) {
                cout << "Player 1 won!" << endl;
                exit(0);
            } else {
                cout << "Player 2 won!" << endl;
                exit(0);
            }
        }
        while (!((*stream) >> cmd)) {
            if (fstreams.size() > 1) {
                fstreams.pop_back();
                stream = &(fstreams.back());
            } else if (fstreams.size() == 1) {
                fstreams.pop_back();
                stream = &cin;
            } else {
                moreToRead = false;
                break;
            }
        }
    }
}
