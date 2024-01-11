#include "gamescene.h"
#include "drawer.h"

#include <QPainter>

GameScene::GameScene()
{
    qDebug() << "GameScene ready";
}

void GameScene::requestPaint()
{
    update();
}

void GameScene::paint(QPainter *painter)
{
    Drawer::drawMap(painter, _game->getTileSize(), _game->getLevel());

    Drawer::drawPaths(painter, _game->getPathBegins());
}

void GameScene::addPathPoint(int x, int y)
{
    if (x < 0 || x > _areaWidth || y < 0 || y > _areaHeight)
        return;
    _game->addPath(x , y);
}

void GameScene::startAddingPath()
{
    _game->startAddingPath();
}

void GameScene::stopAddingPath()
{
    _game->stopAddingPath();
}

void GameScene::loadGame()
{
    qDebug() << "start load game";
    _game = new Game();
}

void GameScene::loadLevel(int level)
{
    qDebug() << "start load level";
    _game->loadLevel(level);
}

void GameScene::restartLevel()
{
    _game->restartLevel();
}
