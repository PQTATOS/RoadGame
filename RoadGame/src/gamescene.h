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

    Q_INVOKABLE void requestPaint();
    Q_INVOKABLE void loadGame();
    Q_INVOKABLE void loadLevel(int level);

    Q_INVOKABLE void addPathPoint(int x, int y);
    Q_INVOKABLE void endPathPoint();

    void paint(QPainter *painter);
private:
    Game* _game;

    QBrush _brush;
    QPen _pen;
    QColor _color;
};

#endif // GAMESCENE_H
