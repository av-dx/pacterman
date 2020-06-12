#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include "Globals.h"
#include "Enums.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Map.h"
#include "Player.h"

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

class Ghost;
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

class Ghost : public Entity
{
    private:
    Direction dir;
    float speed;
    int animFrame;
    char sprite[1][2];

    public:
    Ghost (Vector2D p);
    void update(Map *m);
    
};

// Main Function

int main()
{
    Map map;
    Player player(Vector2D(30, 10));
    std::vector<std::vector<char>> board;

    map.fetchMap("default.map");
    board = map.getMap();

    std::thread inputThread(PollInput);

    while (true)
    {
        usleep(250000);
        player.update(&map);
        board = map.getMap();
        board[player.getPos().y][player.getPos().x] = player.getImage();

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