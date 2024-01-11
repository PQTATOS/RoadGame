#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QQuickPaintedItem>
#include <QPainterPath>
#include <QBrush>
#include <QPen>

#include "game.h"

class GameScene : public QQuickPaintedItem
{
    Q_OBJECT
public:
    GameScene();

    Q_PROPERTY(int width MEMBER _areaWidth);
    Q_PROPERTY(int height MEMBER _areaHeight)

    Q_INVOKABLE void requestPaint();
    Q_INVOKABLE void loadGame();
    Q_INVOKABLE void loadLevel(int level);

    Q_INVOKABLE void addPathPoint(int x, int y);
    Q_INVOKABLE void startAddingPath();
    Q_INVOKABLE void stopAddingPath();

    Q_INVOKABLE void restartLevel();

    void paint(QPainter *painter);
private:
    Game* _game;
    int _areaWidth;
    int _areaHeight;
};

#endif // GAMESCENE_H
