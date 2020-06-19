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
class GhostState;
class GhostHuntingState;
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

class GhostState
{
public:
    virtual ~GhostState() {}
    virtual void enter(Ghost &g) {}
    virtual void update(Ghost &g, Player &p, Map &m) {}
};

class GhostHuntingState : public GhostState
{
public:
    void enter(Ghost &g);
    void update(Ghost &g, Player &p, Map &m);
};

class Ghost : public Entity
{
private:
    Direction dir;
    float speed;
    int animFrame;
    char sprite[1][2];
    GhostState *state;

public:
    Ghost(Vector2D p);
    void update(Player &p, Map *m);
    void setDir(Direction d);
    Direction getDir();
};

void GhostHuntingState::enter(Ghost &g)
{
    g.setDir(DIR_UP);
}
void GhostHuntingState::update(Ghost &g, Player &p, Map &m)
{
    static Direction gDir = g.getDir();
    static Direction gbackDir;
    // static Direction optimalDir;
    static Vector2D step;
    static Vector2D dest;

    // static int distFromPlayerX, distFromPlayerY;

    // distFromPlayerX = p.getPos().x - g.getPos().x;
    // distFromPlayerY = p.getPos().y - g.getPos().y;

    // if (abs(distFromPlayerX) > abs(distFromPlayerY))
    // {
    //     if (distFromPlayerX > 0)
    //         optimalDir = DIR_RIGHT;
    //     else
    //     {
    //         optimalDir = DIR_LEFT;
    //     }
    // }
    // else
    // {
    //     if (distFromPlayerY > 0)
    //         optimalDir = DIR_DOWN;
    //     else
    //     {
    //         optimalDir = DIR_UP;
    //     }
    // }

    if (gDir == DIR_RIGHT)
    {
        gbackDir = DIR_LEFT;
        step = Vector2D(1, 0);
    }
    if (gDir == DIR_LEFT)
    {
        gbackDir = DIR_RIGHT;
        step = Vector2D(-1, 0);
    }
    if (gDir == DIR_UP)
    {
        gbackDir = DIR_DOWN;
        step = Vector2D(0, -1);
    }
    if (gDir == DIR_DOWN)
    {
        gbackDir = DIR_UP;
        step = Vector2D(0, 1);
    }
    dest = g.getPos() + step;
    ObjectID destBlock = m.queryMap(dest);
    Direction toTry[4] = {DIR_UP, DIR_DOWN, DIR_RIGHT, DIR_LEFT};
    for (int i = 2; i >= 0; i--)
    {
        if (rand() / (RAND_MAX / 2))
        {
            auto temp = toTry[i];
            toTry[i] = toTry[3];
            toTry[3] = temp;
        }
    }
    // for (int i = 0; i < 3; i++)
    // {
    //     if (toTry[i] == optimalDir)
    //     {
    //         auto temp = toTry[0];
    //         toTry[0] = toTry[i];
    //         toTry[i] = temp;
    //     }
    // }
    for (int i = 0; i < 3; i++)
    {
        if (toTry[i] == gbackDir)
        {
            auto temp = toTry[3];
            toTry[3] = toTry[i];
            toTry[i] = temp;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        gDir = toTry[i];
        g.setDir(gDir);
        if (gDir == DIR_RIGHT)
        {
            step = Vector2D(1, 0);
        }
        if (gDir == DIR_LEFT)
        {
            step = Vector2D(-1, 0);
        }
        if (gDir == DIR_UP)
        {
            step = Vector2D(0, -1);
        }
        if (gDir == DIR_DOWN)
        {
            step = Vector2D(0, 1);
        }
        dest = g.getPos() + step;
        destBlock = m.queryMap(dest);
        if (destBlock != ID_WALL)
            break;
    }
    g.setPos(dest);
}

Ghost::Ghost(Vector2D p)
{
    pos = p;
    image = 'W';
    state = new GhostHuntingState();
    state->enter(*this);
}
void Ghost::update(Player &p, Map *m)
{
    state->update(*this, p, *m);
}
void Ghost::setDir(Direction d)
{
    dir = d;
}
Direction Ghost::getDir()
{
    return dir;
}

// Main Function

int main()
{
    srand(time(0));
    Map map;
    Player player(Vector2D(29, 10));
    Ghost ghost(Vector2D(29, 8));
    std::vector<std::vector<char>> board;

    map.fetchMap("default.map");
    board = map.getMap();

    std::thread inputThread(PollInput);

    while (true)
    {
        usleep(250000);
        player.update(&map);
        ghost.update(player, &map);
        board = map.getMap();
        board[player.getPos().y][player.getPos().x] = player.getImage();
        board[ghost.getPos().y][ghost.getPos().x] = ghost.getImage();

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