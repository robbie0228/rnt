#include "game.h"
#include <iostream>
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
    for (int i = 0, j = 0; i < NUMLINKS * 2; i += 2, ++j) {
        LinkType linkTempType = (links[i] == 'D' ? LinkType::Data : 
                                                   LinkType::Virus);
        int linkTempStrength = links[i + 1];
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
    try {
        if (argc > MAXCMDLINEARGS + 1) {
            throw "Too many command line arguments given";
        }
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];
            if (arg == "-ability1") {
                string abilities = argv[i + 1];
                if (abilities.length() != NUMABILITIES) throw "Invalid abilities";
                ++i;
                allAbilities.emplace_back(make_pair(1, cmdInitAbilities(abilities)));
            }
            else if (arg == "-ability2") {
                string abilities = argv[i + 1];
                if (abilities.length() != NUMABILITIES) throw "Invalid abilities";
                ++i;
                allAbilities.emplace_back(make_pair(2, cmdInitAbilities(abilities)));
            }
            else if (arg == "-link1") {
                string links = argv [i + 1];
                if (links.length() != NUMLINKS * 2) throw "Invalid links";
                ++i;
                allLinks.emplace_back(make_pair(1, cmdInitLinks(1, links)));
            }
            else if (arg == "-link2") {
                string links = argv [i + 1];
                if (links.length() != NUMLINKS * 2) throw "Invalid links";
                ++i;
                allLinks.emplace_back(make_pair(2, cmdInitLinks(2, links)));
            }
            else if (arg == "-graphics") {
                //// Enable graphic display ////
            }
            else throw "Invalid command line argument given";
        }
    } catch (char const *e) {
        cout << e << endl;
        cout << endl;
        exit(1);
    }

    Game game(allAbilities, allLinks);

    string cmd;

    while (cin >> cmd)
    {
        try
        {
            if (cmd == "move")
            {
                char link;
                cin >> link;
                Direction dir;
                string dirtemp;
                cin >> dirtemp;
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
                cin >> abilityID;
                pair<int, bool> abilityInfo = game.verifyAbility(abilityID);
                char c;
                vector<char> useAbilityInfo;
                for (int i = 0; i < abilityInfo.first; i++) {
                    cin >> c;
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
                // TODO, can add a stream to the front of another?
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
    }
}
