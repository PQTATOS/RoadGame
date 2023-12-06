#include "tile.h"

Tile::Tile(char type, std::string path)
{
    switch (type) {
    case '#':
        _type = TileType::Empty;
        _pathToTexture = QColor("black");
        break;
    case 'R':
        _type = TileType::River;
        _pathToTexture = QColor("blue");
        break;
    case 'O':
        _type = TileType::Obstacle;
        _pathToTexture = QColor("yellow");
        break;
    case 'E':
        _type = TileType::Entrance;
        _pathToTexture = QColor("green");
        break;
    case 'X':
        _type = TileType::Exit;
        _pathToTexture = QColor("red");
        break;
    }
}
