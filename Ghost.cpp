#include "Enums.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Ghost.h"
#include "GhostState.h"

Ghost::Ghost(Vector2D p)
{
    pos = p;
    state = new GhostHuntingState();
    state->enter(*this);
}
void Ghost::setState(GhostStateID g)
{
    switch (g)
    {
    case HUNTING:
        state = new GhostHuntingState();
        break;
    case RETREATING:
        state = new GhostRetreatingState();
        break;
    case VULNERABLE:
        state = new GhostVulnerableState();
        break;
    default:
        state = new GhostHuntingState();
        break;
    }
    state->enter(*this);
}
GhostStateID Ghost::getState() { return state->stateID(); }
void Ghost::update(Player &p, Map &m)
{
    GhostState *next_state = state->update(*this, p, m);
    if (next_state != NULL)
    {
        delete state;
        state = next_state;
        next_state->enter(*this);
    }
}
void Ghost::setDir(Direction d)
{
    dir = d;
}
Direction Ghost::getDir()
{
    return dir;
}
int Ghost::move(Map &m, Direction d)
{
    Vector2D dest, step;
    ObjectID destBlock;

    step = Vector2D::dirvec(d);
    if ((d == DIR_UP) || (d == DIR_LEFT))
    {
        step = Vector2D::product(step, speed);
    }
    dest = pos + step;
    destBlock = m.queryMap(dest);

    if (destBlock == ID_WALL)
    {
        return 0;
    }
    else
    {
        step = Vector2D::product(Vector2D::dirvec(d), speed);
        dest = pos + step;
        setPos(dest);
    }
    return 1;
}