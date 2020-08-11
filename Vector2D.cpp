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
Vector2D Vector2D::absolute(Vector2D a)
{
    return Vector2D(abs(a.x), abs(a.y));
}
Vector2D Vector2D::frac(Vector2D a)
{
    return Vector2D(a.x - std::floor(a.x), a.y - std::floor(a.y));
}
Vector2D Vector2D::ceil(Vector2D a)
{
    return Vector2D(std::ceil(a.x), std::ceil(a.y));
}
Vector2D Vector2D::floor(Vector2D a)
{
    return Vector2D(std::floor(a.x), std::floor(a.y));
}

Vector2D Vector2D::dirvec(Direction dir)
{
    if (dir == DIR_RIGHT)
    {
        return Vector2D(1, 0);
    }
    else if (dir == DIR_LEFT)
    {
        return Vector2D(-1, 0);
    }
    else if (dir == DIR_UP)
    {
        return Vector2D(0, -1);
    }
    else if (dir == DIR_DOWN)
    {
        return Vector2D(0, 1);
    }
    else
    {
        return Vector2D(0, 0);
    }
}

Vector2D Vector2D::product(Vector2D a, double c)
{
    return Vector2D(a.x * c, a.y * c);
}