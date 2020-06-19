#pragma once

#include "Vector2D.h"

class Entity
{
protected:
    Vector2D pos;
    char image;

public:
    Vector2D getPos(void);
    void setPos(Vector2D v);
    char getImage(void);
    void setImage(char i);
    Entity();
    Entity(Vector2D v, char i);
};