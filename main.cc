#include "game.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main()
{
    Game game;

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
                    cout << "invalid ability" << endl;
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
