#pragma once

#include "Entity.h"
#include "Player.h"

class SuperPellet : public Entity
{
private:
    bool active;

public:
    SuperPellet(Vector2D p);
    int hit(Player &p);
};