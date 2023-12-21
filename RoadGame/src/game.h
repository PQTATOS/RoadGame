#ifndef GAME_H
#define GAME_H

#include <QPainterPath>

#include "level.h"
#include "pathhandler.h"

class Game
{
public:
    Game();

    bool loadLevel(int level);
    std::vector<Tile*>* getLevel();

    size_t getColumCount() { return _tileColumCount;}
    size_t getRowCount() { return _tileRowCount; }
    size_t getTileSize() { return _tileSize; }

    std::unordered_set<Node*>* getPathBegins() { return _paths->getPathBegins(); }

    void addPath(int x, int y);
    void startAddingPath();
    void stopAddingPath();
private:
    PathHandler* _paths;

    size_t _tileColumCount = 11;
    size_t _tileRowCount = 17;
    size_t _tileSize = 60;

    bool _isPathContinues = false;
    int _prevX;
    int _prevY;

    Level* _currentLevel;
};

#endif // GAME_H
