#ifndef LEVEL_H
#define LEVEL_H

#include <cstddef>
#include <vector>

#include "tile.h"

class Level
{
public:
    Level();
    bool LoadMap(int num);
    std::vector<Tile*>* getMap()  { return &_currentMap; }
private:
    std::vector<Tile*> _currentMap;
};

#endif // LEVEL_H
