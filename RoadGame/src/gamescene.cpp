#include "gamescene.h"

#include <QPainter>

GameScene::GameScene()
{
    _color = QColor("dimgray");
    _brush = QBrush(_color, Qt::SolidPattern);
    _pen = QPen(_brush, 45, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

void GameScene::requestPaint()
{
    qDebug() << "reqPaint";
    update();

}

void GameScene::paint(QPainter *painter)
{
    qDebug() << "drawing";
    std::vector<Tile*>* tiles = _game->getLevel();

    for (size_t x = 0; x < _game->getColumCount(); ++x)
        for (size_t y = 0; y < _game->getRowCount(); ++y) {
            _brush.setColor((*tiles)[y*_game->getColumCount() +x]->getColor());
            painter->fillRect(x*_game->getTileSize(), y*_game->getTileSize(),
                             _game->getTileSize(), _game->getTileSize(), _brush);
        }
    painter->setPen(_pen);
    painter->drawPath(*_game->getPath());
}

void GameScene::addPathPoint(int x, int y)
{
    _game->addPath(x , y);
}

void GameScene::endPathPoint()
{
    _game->endPath();
}

void GameScene::loadGame()
{
    _game = new Game();
}

void GameScene::loadLevel(int level)
{
    _game->loadLevel(level);
}
