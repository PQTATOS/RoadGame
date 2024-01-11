#ifndef TILE_H
#define TILE_H

#include <string>
#include <QColor>

enum class TileType : int
{
    Obstacle,
    River,
    Sign,
    Empty
};

class Tile
{
public:
    Tile(int x, int y, char type, std::string path);
    TileType getType() { return _type; }
    QColor getColor() { return _pathToTexture; }
    int getX() { return _x; };
    int getY() { return _y; };

private:
    TileType _type;
    QColor _pathToTexture;
    int _x;
    int _y;
};


class SignTile: public Tile
{
public:
    SignTile(int id, int x, int y, char type, std::string path);
private:
    size_t _roadId;

};

#endif // TILE_H
