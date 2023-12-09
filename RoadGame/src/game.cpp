#include "game.h"

Game::Game()
{
    _currentLevel = new Level();
    _pathChecker = new PathCollisionChecker(_tileRowCount, _tileColumCount, _tileSize, _currentLevel->getMap());
}

bool Game::loadLevel(int level)
{
    _currentLevel->LoadMap(level);
    return true;
}

std::vector<Tile*>* Game::getLevel()
{
    return _currentLevel->getMap();
}

void Game::addPath(int x, int y)
{
    Node* node = _pathChecker->addNode(x,y,0);
    if (node == nullptr)
    {
        _isPathContinues = false;
        return;
    }
    if (_isPathContinues)
    {
        tmp_path.moveTo(_prevX, _prevY);
        tmp_path.lineTo(x,y);
    }
    _prevX = x;
    _prevY = y;
    _isPathContinues = true;
}

void Game::endPath()
{
    _isPathContinues = false;
}

