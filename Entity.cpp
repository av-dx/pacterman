#include <bitset>
#include "Vector2D.h"
#include "Entity.h"

Vector2D Entity::getPos(void) { return pos; }
void Entity::setPos(Vector2D v) { pos = v; }
char Entity::getImage(void) { return image; }
void Entity::setImage(char i) { image = i; }
Entity::Entity()
{
    pos = Vector2D(0, 0);
    image = ' ';
}
Entity::Entity(Vector2D v, char i)
{
    pos = v;
    image = i;
}