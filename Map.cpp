#include <vector>
#include <fstream>
#include <iostream>
#include "Enums.h"
#include "Map.h"

bool Map::fetchMap(const char *fname)
{
    std::ifstream mapFile;
    std::string inStr;
    int i = 0;
    char c;
    mapFile.open(fname, std::ios_base::in);
    if (!mapFile.is_open())
        return 0;
    mapFile >> width;
    mapFile >> height;
    mapFile >> c;
    while (!mapFile.eof())
    {
        std::getline(mapFile, inStr);
        std::vector<char> inVecChar(inStr.begin(), inStr.end());
        map.push_back(inVecChar);
        i++;
    }

    mapFile.close();
    return 1;
}

ObjectID Map::queryMap(Vector2D queryPos)
{
    int qy = (int)queryPos.y;
    int qx = (int)queryPos.x;

    switch (map[qy][qx])
    {
    case '.':
        return ID_DOT;
        break;
    case '-':
        return ID_WALL;
        break;
    case '|':
        return ID_WALL;
        break;
    case '_':
        return ID_WALL;
        break;
    case '#':
        return ID_WALL;
        break;
    case '8':
        return ID_FRUIT;
        break;
    default:
        return ID_UNKNOWN;
        break;
    }
}

void Map::setBlock(Vector2D pos, char i)
{
    int px, py;
    px = (int)pos.x;
    py = (int)pos.y;
    map[py][px] = i;
}

Vector2D Map::getDimensions(void)
{
    return Vector2D(width, height);
}

std::vector<std::vector<char>> Map::getMap() { return map; }