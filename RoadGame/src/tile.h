#ifndef TILE_H
#define TILE_H

#include <QImage>

enum class TileType
{
    Empty,
    Obstacle,
    River
};

class Tile
{
public:
    Tile();
    bool isObstacle();
private:
    TileType m_type;
    QImage m_texture;
};

#endif // TILE_H
