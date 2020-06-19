#include "Enums.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Ghost.h"

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
