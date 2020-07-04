#pragma once

struct Vector2D
{
    float x, y;
    Vector2D();
    Vector2D(float a, float b);
    Vector2D operator+(Vector2D &a);
    Vector2D operator-(Vector2D &a);
    Vector2D absolute(Vector2D &a);
    Vector2D frac();
};
