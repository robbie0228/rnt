#include "game.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc > MAXCMDLINEARGS + 1) {
        throw "Too many command line arguments given";
    }

    // argc = #cmd + 1
    // agrv[i] points to the ith cmd

    Game game;

    try {
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];

            if (arg == "-ability1") {
                string abilities = argv[i + 1];
                if (abilities.length() != NUMABILITIES) throw "Invalid abilities";
                ++i;
                game.cmdInitAbilities(1, abilities);
            }
            else if (arg == "-ability2") {
                string abilities = argv[i + 1];
                if (abilities.length() != NUMABILITIES) throw "Invalid abilities";
                ++i;
                game.cmdInitAbilities(2, abilities);
            }
            else if (arg == "-link1") {
                string links = argv [i + 1];
                if (links.length() != NUMLINKS * 2) throw "Invalid links";
                ++i;
                game.cmdInitLinks(1, links);
            }
            else if (arg == "-link2") {
                string links = argv [i + 1];
                if (links.length() != NUMLINKS * 2) throw "Invalid links";
                ++i;
                game.cmdInitLinks(2, links);
            }
            else if (arg == "-graphics") {
                // Enable graphic display
            }
            else throw "Invalid command line argument given";
        }
    } catch (char const *e) {
        cout << e << endl;
        cout << endl;
        EXIT_FAILURE;
    }

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
