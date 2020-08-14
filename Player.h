#pragma once

#include "Map.h"

class Player : public Entity
{
private:
    Direction dir;
    int lives;
    int score;
    float speed;
    int animFrame;
    char sprite[4][2];

public:
    int active;
    Player(Vector2D p);
    void update(Map &m);
    int getScore();
    int getLives();
    void setLives(int l);
    void kill();
};