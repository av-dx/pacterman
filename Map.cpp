#include <vector>
#include <fstream>
#include "Enums.h"
#include "Map.h"

bool Map::fetchMap(const char *fname)
{
    std::ifstream mapFile;
    std::string inStr;
    int i = 0;

    mapFile.open(fname, std::ios_base::in);
    if (!mapFile.is_open())
        return 0;
    mapFile >> width;
    mapFile >> height;
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

    if (map[qy][qx] == '.')
    {
        // std::cout << qx << " , " << qy << "  [" << map[qy][qx] << "] "
        //           << "ONDOT";
        return ID_DOT;
    }
    if (map[qy][qx] == '|')
        return ID_WALL;
    if (map[qy][qx] == '-')
        return ID_WALL;
    if (map[qy][qx] == '8')
        return ID_FRUIT;
    if (map[qy][qx] == ' ')
        return ID_BLANK;
    return ID_UNKNOWN;
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