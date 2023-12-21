#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>

#include "node.h"

class Drawer
{
public:
    Drawer();
    static void drawPathDebug(QPainter *painter, Node *node);
};

#endif // DRAWER_H
