#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
using namespace std;

int main()
{
    Game game;

    string cmd;

    istream *stream = &cin;
    ifstream file;

    while (true)
    {
        
        if (!((*stream) >> cmd)) {
            if (stream != &cin) {
                stream = &cin;
                if (!((*stream) >> cmd)) {
                    break;
                }
            } else {
                break;
            }
        }
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
                file = ifstream{fileName};
                stream = &file;
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
