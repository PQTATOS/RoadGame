#ifndef TILE_H
#define TILE_H

#include <string>
#include <QColor>
#include <vector>
#include <utility>

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
    void addConnection(int to, int demand);
    size_t getId() { return _roadId; };
    std::vector<std::pair<int, int>>* getNeeds() { return &_needsConnection; };
private:
    size_t _roadId;
    std::vector<std::pair<int, int>> _needsConnection;

};

#endif // TILE_H
