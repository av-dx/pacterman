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
bool gameRunning;

// Functions

void Loop(Player &, Ghost &, Ghost &, Ghost &, Map &, std::vector<std::vector<char>>, SuperPellet &);
void Init(void);
void Intro(void);
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

void Intro()
{
}

void Init()
{
    while (!keyDown[' '])
    {
        usleep(1000000);
        system("clear");
        std::cout << "\033[1;37m"
                  << "____________________________________________________________\n"
                  << "|                             ^                            |\n"
                  << "|                                                          |\n"
                  << "|< The terminal window should be big enough for this box. >|\n"
                  << "|                                                          |\n"
                  << "|    \aYou should be hearing your terminal bell right now.   |\n"
                  << "|                                                          |\n"
                  << "|   Your terminal theme might be different. This is how    |\n"
                  << "|  colours will look on your terminal. Turn on 'Show bold  |\n"
                  << "|  text in bright colors' check under Preferences->Colors. |\n"
                  << "|      \033[1;31mRED              \033[1;32mGREEN              \033[1;33mYELLOW\033[1;37m          |\n"
                  << "|      \033[1;34mBLUE             \033[1;35mMAGENTA            \033[1;36mCYAN\033[1;37m            |\n"
                  << "|                                                          |\n"
                  << "|               \033[4;37mPress [SPACE] to continue\033[24;37m                  |\n"
                  << "|__________________________________________________________|\n"
                  << "\033[0m" << std::endl;
    }
}

// Main Function

int main()
{
    gameRunning = true;
    std::thread inputThread(PollInput);
    Init();
    Intro();
    srand(time(0));
    Map map;
    Player player(Vector2D(29, 10));
    std::vector<std::vector<char>> board;
    board = map.getMap();
    map.fetchMap("default.map");
    Ghost ghost(Vector2D(29, 8));
    Ghost ghost1(Vector2D(29, 7));
    Ghost ghost2(Vector2D(29, 6));
    SuperPellet pellet(Vector2D(50, 10));

    while (player.getLives() > 0)
    {
        Loop(player, ghost, ghost1, ghost2, map, board, pellet);
    }
    gameRunning = false;
    std::cout << "u lost now get lost, press any key to exit" << std::endl;
    inputThread.join();
    return 0;
}

void Loop(Player &player, Ghost &ghost, Ghost &ghost1, Ghost &ghost2,
          Map &map, std::vector<std::vector<char>> board, SuperPellet &pellet)
{
    int TIMER = 0;

    while (true)
    {
        usleep(250000);

        if (pellet.hit(player))
        {
            ghost.setState(VULNERABLE);
            ghost1.setState(VULNERABLE);
            ghost2.setState(VULNERABLE);
        }
        if (!player.active)
        {
            if (TIMER < 20)
                TIMER++;
            else
            {
                TIMER = 0;
                player.active = 1;
                player.setPos(Vector2D(29, 10));
                return;
            }
        }
        else
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
        std::cout << "\033[1;37m\tSCORE : " << player.getScore() << "\t\t\t LIVES : " << player.getLives() << "\033[0m" << std::endl;
        // std::cout << "G1:<" << ghost.getState() << ghost.getPos().x <<
        //           << "> -- G2:<" << ghost1.getState()
        //           << "> -- G3:<" << ghost2.getState() << ">" << std::endl;
        // std::printf("G1:<%d,%.1f,%.1f,%d> -- G2:<%d,%.1f,%.1f,%d> -- G3:<%d,%.1f,%.1f,%d>\n",
        //             ghost.getState(), ghost.getPos().x, ghost.getPos().y, ghost.getDir(),
        //             ghost1.getState(), ghost1.getPos().x, ghost1.getPos().y, ghost1.getDir(),
        //             ghost2.getState(), ghost2.getPos().x, ghost2.getPos().y, ghost2.getDir());
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
    while (gameRunning)
    {
        std::cin.get(newchar);
        if (oldchar != newchar)
        {
            keyDown[newchar] = true;
            keyDown[oldchar] = false;
            oldchar = newchar;
        }
    }
    return;
}