#include <stdlib.h>
#include "Enums.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Ghost.h"
#include "GhostState.h"

GhostStateID GhostHuntingState::stateID() { return HUNTING; }
void GhostHuntingState::enter(Ghost &g)
{
    g.setImage('W');
    // g.setDir(DIR_UP);
}
GhostState *GhostHuntingState::update(Ghost &g, Player &p, Map &m)
{
    gDir = g.getDir();

    distFromPlayerX = p.getPos().x - g.getPos().x;
    distFromPlayerY = p.getPos().y - g.getPos().y;

    if ((abs(distFromPlayerX) < 1) && (abs(distFromPlayerY) < 1))
    {
        return new GhostRetreatingState();
    }

    if (abs(distFromPlayerX) > abs(distFromPlayerY))
    {
        if (distFromPlayerX > 0)
            optimalDir = DIR_RIGHT;
        else
        {
            optimalDir = DIR_LEFT;
        }
    }
    else
    {
        if (distFromPlayerY > 0)
            optimalDir = DIR_DOWN;
        else
        {
            optimalDir = DIR_UP;
        }
    }

    if (gDir == DIR_RIGHT)
    {
        gbackDir = DIR_LEFT;
        step = Vector2D(1, 0);
        side = Vector2D(0, 1);
    }
    if (gDir == DIR_LEFT)
    {
        gbackDir = DIR_RIGHT;
        step = Vector2D(-1, 0);
        side = Vector2D(0, 1);
    }
    if (gDir == DIR_UP)
    {
        gbackDir = DIR_DOWN;
        step = Vector2D(0, -1);
        side = Vector2D(1, 0);
    }
    if (gDir == DIR_DOWN)
    {
        gbackDir = DIR_UP;
        step = Vector2D(0, 1);
        side = Vector2D(1, 0);
    }
    dest = g.getPos() + step;
    destBlock = m.queryMap(dest);
    side1Block = m.queryMap(g.getPos() + side);
    side2Block = m.queryMap(g.getPos() - side);

    if ((destBlock == ID_WALL) || (side1Block != ID_WALL) || (side2Block != ID_WALL))
    {
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
        for (int i = 0; i < 3; i++)
        {
            if (toTry[i] == optimalDir)
            {
                auto temp = toTry[0];
                toTry[0] = toTry[i];
                toTry[i] = temp;
            }
        }
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
    }
    g.setPos(dest);
    return NULL;
}

GhostStateID GhostRetreatingState::stateID() { return RETREATING; }
void GhostRetreatingState::enter(Ghost &g)
{
    g.setImage('v');
    spawner = Vector2D(15, 6);
}
GhostState *GhostRetreatingState::update(Ghost &g, Player &p, Map &m)
{
    gDir = g.getDir();

    distFromSpawnerX = spawner.x - g.getPos().x;
    distFromSpawnerY = spawner.y - g.getPos().y;

    if ((abs(distFromSpawnerX) < 1) && (abs(distFromSpawnerY) < 1))
    {
        return new GhostHuntingState();
    }

    if (abs(distFromSpawnerX) > abs(distFromSpawnerY))
    {
        if (distFromSpawnerX > 0)
            optimalDir = DIR_RIGHT;
        else
        {
            optimalDir = DIR_LEFT;
        }
    }
    else
    {
        if (distFromSpawnerY > 0)
            optimalDir = DIR_DOWN;
        else
        {
            optimalDir = DIR_UP;
        }
    }

    if (gDir == DIR_RIGHT)
    {
        gbackDir = DIR_LEFT;
        step = Vector2D(1, 0);
        side = Vector2D(0, 1);
    }
    if (gDir == DIR_LEFT)
    {
        gbackDir = DIR_RIGHT;
        step = Vector2D(-1, 0);
        side = Vector2D(0, 1);
    }
    if (gDir == DIR_UP)
    {
        gbackDir = DIR_DOWN;
        step = Vector2D(0, -1);
        side = Vector2D(1, 0);
    }
    if (gDir == DIR_DOWN)
    {
        gbackDir = DIR_UP;
        step = Vector2D(0, 1);
        side = Vector2D(1, 0);
    }
    dest = g.getPos() + step;
    destBlock = m.queryMap(dest);
    side1Block = m.queryMap(g.getPos() + side);
    side2Block = m.queryMap(g.getPos() - side);

    if ((destBlock == ID_WALL) || (side1Block != ID_WALL) || (side2Block != ID_WALL))
    {
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
        for (int i = 0; i < 4; i++)
        {
            if (toTry[i] == optimalDir)
            {
                auto temp = toTry[0];
                toTry[0] = toTry[i];
                toTry[i] = temp;
            }
        }
        // for (int i = 0; i < 3; i++)
        // {
        //     if (toTry[i] == gbackDir)
        //     {
        //         auto temp = toTry[3];
        //         toTry[3] = toTry[i];
        //         toTry[i] = temp;
        //     }
        // }
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
    }
    g.setPos(dest);
    return NULL;
}

GhostStateID GhostVulnerableState::stateID() { return VULNERABLE; }
void GhostVulnerableState::enter(Ghost &g)
{
    g.setImage('w');
    timer = 0;
}
GhostState *GhostVulnerableState::update(Ghost &g, Player &p, Map &m)
{
    timer++;
    gDir = g.getDir();

    if (timer > 20)
    {
        return new GhostHuntingState();
    }
    else
    {
        distFromPlayerX = p.getPos().x - g.getPos().x;
        distFromPlayerY = p.getPos().y - g.getPos().y;

        if ((abs(distFromPlayerX) < 1) && (abs(distFromPlayerY) < 1))
        {
            return new GhostRetreatingState();
        }
    }

    if (gDir == DIR_RIGHT)
    {
        gbackDir = DIR_LEFT;
        step = Vector2D(1, 0);
        side = Vector2D(0, 1);
    }
    if (gDir == DIR_LEFT)
    {
        gbackDir = DIR_RIGHT;
        step = Vector2D(-1, 0);
        side = Vector2D(0, 1);
    }
    if (gDir == DIR_UP)
    {
        gbackDir = DIR_DOWN;
        step = Vector2D(0, -1);
        side = Vector2D(1, 0);
    }
    if (gDir == DIR_DOWN)
    {
        gbackDir = DIR_UP;
        step = Vector2D(0, 1);
        side = Vector2D(1, 0);
    }
    dest = g.getPos() + step;
    destBlock = m.queryMap(dest);
    side1Block = m.queryMap(g.getPos() + side);
    side2Block = m.queryMap(g.getPos() - side);

    if ((destBlock == ID_WALL) || (side1Block != ID_WALL) || (side2Block != ID_WALL))
    {
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
    }
    g.setPos(dest);
    return NULL;
}