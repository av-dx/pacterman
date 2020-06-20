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
    std::vector<std::vector<char>> board;

    map.fetchMap("default.map");
    board = map.getMap();

    std::thread inputThread(PollInput);

    while (true)
    {
        usleep(250000);
        player.update(map);
        ghost.update(player, map);
        ghost1.update(player, map);
        ghost2.update(player, map);
        board = map.getMap();
        board[player.getPos().y][player.getPos().x] = player.getImage();
        board[ghost.getPos().y][ghost.getPos().x] = ghost.getImage();
        board[ghost1.getPos().y][ghost1.getPos().x] = ghost.getImage();
        board[ghost2.getPos().y][ghost2.getPos().x] = ghost.getImage();

        system("clear");
        std::cout << "  [" << map.getMap()[10][30] << "] ";
        std::cout << "SCORE : " << player.getScore() << std::endl;

        for (auto i : board)
        {
            for (auto j : i)
                std::cout << j;
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