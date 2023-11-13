#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QQuickPaintedItem>
#include "game.h"

class GameScene : public QQuickPaintedItem
{
    Q_OBJECT
public:
    GameScene();
    Q_INVOKABLE void requestPaint();
    void paint(QPainter *painter);
private:
    Game m_game;
};

#endif // GAMESCENE_H
