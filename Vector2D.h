#pragma once
#include "Enums.h"

struct Vector2D
{
    float x, y;
    Vector2D();
    Vector2D(float a, float b);
    Vector2D operator+(Vector2D &a);
    Vector2D operator-(Vector2D &a);
    static Vector2D absolute(Vector2D a);
    static Vector2D frac(Vector2D a);
    static Vector2D floor(Vector2D a);
    static Vector2D ceil(Vector2D a);
    static Vector2D dirvec(Direction dir);
    // static Vector2D dot(Vector2D &a, Vector2D &b);
    static Vector2D product(Vector2D a, double c);
};
