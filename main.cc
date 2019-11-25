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
        if (cmd == "move")
        {
            char link;
            cin >> link;
            Direction dir;
            string dirtemp;
            cin >> dirtemp;
            if (dirtemp == "left") dir = Direction::Left;
            if (dirtemp == "right") dir = Direction::Right;
            if (dirtemp == "up") dir = Direction::Up;
            else dir = Direction::Down;   // note the absence of error checking
            game.move(link, dir);
        }
        else if (cmd == "abilities")
        {
            // ITERATION II
        }
        else if (cmd == "ability")
        {
            // ITERATION II
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
    }
}
