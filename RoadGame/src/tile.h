#ifndef TILE_H
#define TILE_H

#include <string>
#include <QColor>

enum class TileType : int
{
    Empty,
    Obstacle,
    River,
    Entrance,
    Exit
};

class Tile
{
public:
    Tile(char type, std::string path);
    TileType getType() { return _type; }
    QColor getColor() { return _pathToTexture; }
private:
    TileType _type;
    QColor _pathToTexture;
};

#endif // TILE_H
