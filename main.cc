#include "game.h"
#include <iostream>
#include <string>
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
                else dir = Direction::Down;   // note the absence of error checking
                game.move(link, dir);
            }
            else if (cmd == "abilities")
            {
                game.printAbilities(cout);
            }
            else if (cmd == "ability")
            {
                int abilityID;
                cin >> abilityID;
                char info1, info2, info3;
                cin >> info1 >> info2 >> info3;
                vector<char> useAbilityInfo = {info1, info2, info3};
                game.useAbility(abilityID, useAbilityInfo);
            }
            else if (cmd == "board")
            {
                cout << game;
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
            { // invalid command, take input again
                cout << "invalid command, try again" << endl;
            }
        } catch (char const *e) {
            cout << e << endl;
        }
    }
}
