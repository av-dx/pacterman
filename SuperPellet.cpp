#include <math.h>
#include "Entity.h"
#include "Player.h"
#include "SuperPellet.h"

SuperPellet::SuperPellet(Vector2D p)
{
    pos = p;
    active = true;
    image = 'P';
}

int SuperPellet::hit(Player &p)
{
    if (active)
    {
        if ((abs(p.getPos().x - pos.x) < 1) && (abs(p.getPos().y - pos.y) < 1))
        {
            image = ' ';
            active = false;
            return 1;
        }
    }
    return 0;
}
