#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include "Globals.h"
#include "Enums.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Ghost.h"
#include "SuperPellet.h"

// Globals

bool oldKeyDown[256];
bool keyDown[256];

// Functions

void Loop(void);
void Init(void);
void Display(void);
void Clear(void);
void Update(void);
void PollInput(void);

// Classes

class Item;
class Dot;
class Fruit;

// Enumerables

// Game Functions

void Init()
{
}

void Loop()
{
}

// Main Function

int main()
{
    srand(time(0));
    Map map;

    Player player(Vector2D(29, 10));

    Ghost ghost(Vector2D(29, 8));
    Ghost ghost1(Vector2D(29, 7));
    Ghost ghost2(Vector2D(29, 6));

    SuperPellet pellet(Vector2D(32, 10));

    std::vector<std::vector<char>> board;

    map.fetchMap("default.map");
    board = map.getMap();

    std::thread inputThread(PollInput);

    while (true)
    {
        usleep(250000);

        if (pellet.hit(player))
        {
            ghost.setState(VULNERABLE);
            ghost1.setState(VULNERABLE);
            ghost2.setState(VULNERABLE);
        }

        player.update(map);

        ghost.update(player, map);
        ghost1.update(player, map);
        ghost2.update(player, map);

        board = map.getMap();

        board[pellet.getPos().y][pellet.getPos().x] = pellet.getImage();

        board[ghost.getPos().y][ghost.getPos().x] = ghost.getImage();
        board[ghost1.getPos().y][ghost1.getPos().x] = ghost1.getImage();
        board[ghost2.getPos().y][ghost2.getPos().x] = ghost2.getImage();

        board[player.getPos().y][player.getPos().x] = player.getImage();

        system("clear");
        // std::cout << "  [" << map.getMap()[10][30] << "] ";
        std::cout << "SCORE : " << player.getScore() << "<" << board[1][28] << ">" << std::endl;
        // std::cout << "G1:<" << ghost.getState() << ghost.getPos().x <<
        //           << "> -- G2:<" << ghost1.getState()
        //           << "> -- G3:<" << ghost2.getState() << ">" << std::endl;
        std::printf("G1:<%d,%.1f,%.1f,%d> -- G2:<%d,%.1f,%.1f,%d> -- G3:<%d,%.1f,%.1f,%d>\n",
                    ghost.getState(), ghost.getPos().x, ghost.getPos().y, ghost.getDir(),
                    ghost1.getState(), ghost1.getPos().x, ghost1.getPos().y, ghost1.getDir(),
                    ghost2.getState(), ghost2.getPos().x, ghost2.getPos().y, ghost2.getDir());
        for (auto i : board)
        {
            for (auto j : i)
                switch (j)
                {
                case '.':
                    std::cout << "\033[1;33m" << j << "\033[0m";
                    break;
                case ' ':
                    std::cout << j;
                    break;
                case '_':
                case '|':
                case '#':
                    std::cout << "\033[37;47m" << j << "\033[0m";
                    break;
                case 'w':
                    std::cout << "\033[1;34m" << j << "\033[0m";
                    break;
                case 'W':
                    std::cout << "\033[1;31m" << j << "\033[0m";
                    break;
                case 'v':
                    std::cout << "\033[1;32m" << j << "\033[0m";
                    break;
                case '0':
                case '(':
                case ')':
                case 'u':
                case 'n':
                case 'o':
                    std::cout << "\033[1;33m" << j << "\033[0m";
                    break;
                case '8':
                    std::cout << "\033[1;36;43m" << j << "\033[0m";
                    break;
                default:
                    std::cout << j;
                    break;
                }
            std::cout << "\n";
        }
        std::cout << std::endl;
        // if (player.getPos().y == 8)
        // {
        //     // stop;
        // }
    }

    return 0;
}

void PollInput()
{
    termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~ICANON;
    new_tio.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    char newchar, oldchar;
    while (true)
    {

        std::cin.get(newchar);
        if (oldchar != newchar)
        {
            keyDown[newchar] = true;
            keyDown[oldchar] = false;
            oldchar = newchar;
        }
    }
}