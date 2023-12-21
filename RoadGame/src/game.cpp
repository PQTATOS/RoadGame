#include "game.h"

#include <QDebug>

Game::Game()
{
    _currentLevel = new Level();
    _paths = new PathHandler(_tileRowCount, _tileColumCount, _tileSize, &_isPathContinues);
}

bool Game::loadLevel(int level)
{
    _currentLevel->LoadMap(level);
    _paths->loadNewTileMap(_currentLevel->getMap());
    return true;
}

std::vector<Tile*>* Game::getLevel()
{
    return _currentLevel->getMap();
}

void Game::addPath(int x, int y)
{
    _paths->addNode(x,y,0);
}

void Game::startAddingPath()
{
    _isPathContinues = true;
}

void Game::stopAddingPath()
{
    _paths->stopAdding();
}

