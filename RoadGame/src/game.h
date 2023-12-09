#ifndef GAME_H
#define GAME_H

#include <QPainterPath>

#include "level.h"
#include "pathcollisionchecker.h"

class Game
{
public:
    Game();

    bool loadLevel(int level);
    std::vector<Tile*>* getLevel();

    size_t getColumCount() { return _tileColumCount;}
    size_t getRowCount() { return _tileRowCount; }
    size_t getTileSize() { return _tileSize; }

    //delete
    QPainterPath* getPath() { return &tmp_path; }
    //delete
    void addPath(int x, int y);
    void endPath();
private:
    PathCollisionChecker* _pathChecker;

    size_t _tileColumCount = 11;
    size_t _tileRowCount = 17;
    size_t _tileSize = 60;

    //delete
    QPainterPath tmp_path;
    //delete
    bool _isPathContinues = false;
    int _prevX;
    int _prevY;

    Level* _currentLevel;
};

#endif // GAME_H
