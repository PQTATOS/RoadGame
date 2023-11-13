#ifndef GAME_H
#define GAME_H

#include <vector>
#include <QImage>
#include "tile.h"

class Game
{
public:
    Game();
    bool loadMap();
private:
    std::vector<std::vector<Tile*>> m_currentMap;
    // colider cheacker
    // cars
    // roads
};

#endif // GAME_H
