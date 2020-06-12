#pragma once
#include <vector>
#include "Enums.h"
#include "Vector2D.h"

class Map
{
private:
    std::vector<std::vector<char>> map;
    int height, width;

public:
    bool fetchMap(const char *fname);
    ObjectID queryMap(Vector2D queryPos);
    void setBlock(Vector2D pos, char i);
    Vector2D getDimensions(void);
    std::vector<std::vector<char>> getMap();
};