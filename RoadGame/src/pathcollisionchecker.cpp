#include "pathcollisionchecker.h"

PathCollisionChecker::PathCollisionChecker(size_t rows, size_t columns, size_t tileSize, std::vector<Tile*>* map)
{
    _tileSize = tileSize;
    _columns = columns;
    _rows = rows;
    _tileMap = map;
}

Node* PathCollisionChecker::addNode(int x, int y, int h)
{
    int nX = x/_tileSize, nY = y/_tileSize;

    if (checkCollision(nX,nY,h))
        return nullptr;

    _NodeTileContainer[nY*_columns + nX];
}

bool PathCollisionChecker::checkCollision(int x, int y, int h)
{
    int nX = x/_tileSize, nY = y/_tileSize;
    TileType tType = (*_tileMap)[nY*_columns + nX]->getType();

    if (tType == TileType::Obstacle)
        return true;
    if (tType == TileType::River && h < 1)
        return true;

    return false;
}
