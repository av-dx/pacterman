#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}
Vector2D::Vector2D(float a, float b)
{
    x = a;
    y = b;
}
Vector2D Vector2D::operator+(Vector2D &a)
{
    return Vector2D(x + a.x, y + a.y);
}
Vector2D Vector2D::operator-(Vector2D &a)
{
    return Vector2D(x - a.x, y - a.y);
}
Vector2D Vector2D::absolute(Vector2D &a)
{
    return Vector2D(abs(a.x), abs(a.y));
}
Vector2D Vector2D::frac()
{
    return Vector2D(x - floor(x), y - floor(y));
}