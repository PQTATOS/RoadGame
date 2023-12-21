#include "gamescene.h"
#include "drawer.h"

#include <QPainter>

GameScene::GameScene()
{
    _color = QColor("pink");
    _brush = QBrush(_color, Qt::SolidPattern);
    _pen = QPen(_brush, 45, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    qDebug() << "GameScene ready";
}

void GameScene::requestPaint()
{
    update();

}

void GameScene::paint(QPainter *painter)
{
    std::vector<Tile*>* tiles = _game->getLevel();

    for (size_t x = 0; x < _game->getColumCount(); ++x)
        for (size_t y = 0; y < _game->getRowCount(); ++y)
        {
            _brush.setColor((*tiles)[y*_game->getColumCount() +x]->getColor());
            painter->fillRect(x*_game->getTileSize(), y*_game->getTileSize(),
                             _game->getTileSize(), _game->getTileSize(), _brush);
        }
    painter->setPen(_pen);
    for (auto node : *(_game->getPathBegins()))
    {
        Drawer::drawPathDebug(painter, node);
    }

    painter->setPen(_pen);
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
    _game = new Game();
}

void GameScene::loadLevel(int level)
{
    _game->loadLevel(level);
}
