#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <unordered_set>

#include "node.h"
#include "tile.h"
#include "car.h"

class Drawer
{
public:
    Drawer();
    static void drawPaths(QPainter *painter,  std::unordered_set<Node*>* nodes);
    static void drawMap(QPainter *painter, size_t tileSize, std::vector<Tile*>* map);
    static void drawCars(QPainter *painter, std::unordered_set<Car*>* carList);
};

#endif // DRAWER_H
