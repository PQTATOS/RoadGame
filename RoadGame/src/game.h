#ifndef GAME_H
#define GAME_H

#include <QPainterPath>
#include <unordered_map>

#include "pathhandler.h"
#include "car.h"

class Game
{
public:
    Game();

    void loadLevel(int level);
    void restartLevel();
    std::vector<Tile*>* getLevel();

    size_t getColumCount() { return _tileColumCount;}
    size_t getRowCount() { return _tileRowCount; }
    size_t getTileSize() { return _tileSize; }

    std::unordered_set<Node*>* getPathBegins() { return _paths->getPathBegins(); }
    std::unordered_set<Car*>* getCarList() { return &_carList; };

    void addPath(int x, int y);
    void startAddingPath();
    void stopAddingPath();

    void reqSimUpdate();
private:    
    PathHandler* _paths;
    std::unordered_map<int,Node*> _roadBegins;
    std::unordered_map<int,Node*> _roadEnds;
    std::vector<SignTile*> _signs;

    std::unordered_set<Car*> _carList;
    std::unordered_map<int, std::unordered_map<int, std::vector<Node*>>> _carPaths;
    std::vector<std::unordered_set<Car*>> _carContainer;

    size_t _tileColumCount = 11;
    size_t _tileRowCount = 17;
    size_t _tileSize = 60;

    bool _isPathContinues = false;
    int _prevX;
    int _prevY;

    std::vector<Tile*> _levelMap;

    int _carCount = 0;
    int _car1Count = 0;
    int _car2Count = 0;
    void makeCarPaths();
};

#endif // GAME_H
