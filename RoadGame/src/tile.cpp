#include "tile.h"
#include <QDebug>

Tile::Tile(int x, int y, char type, std::string path)
{
    _x = x;
    _y = y;
    qDebug() << "Tile check";
    switch (type) {
    case 'R':
        _type = TileType::River;
        _pathToTexture = QColor("blue");
        break;
    case 'O':
        _type = TileType::Obstacle;
        _pathToTexture = QColor("yellow");
        break;
    case 'S':
        _type = TileType::Sign;
        _pathToTexture = QColor("pink");
        break;
    case 'T':
        _type = TileType::Empty;
        _pathToTexture = QColor("White");
        break;
    }
}

SignTile::SignTile(int id, int x, int y, char type, std::string path) : Tile(x, y, type, path)
{
    _roadId = id;
}
