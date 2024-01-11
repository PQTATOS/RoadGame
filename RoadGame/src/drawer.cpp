#include <queue>
#include <QDebug>

#include "drawer.h"

Drawer::Drawer()
{
}

void Drawer::drawPaths(QPainter *painter, std::unordered_set<Node*>* nodes)
{
    qDebug() << "painting paths " << nodes->size();
    QBrush _brushPoint = QBrush(QColor("pink"), Qt::SolidPattern);
    QPen _penPoint = QPen(_brushPoint, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush _brush = QBrush(QColor("red"), Qt::SolidPattern);
    QPen _penPath = QPen(_brush, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    for (auto node : *nodes)
    {
        std::queue<Node*> q;
        std::unordered_set<Node*> visited;

        q.push(node);

        while (!q.empty())
        {
            Node* cur = q.front();
            q.pop();
            visited.insert(cur);

            painter->setPen(_penPoint);
            painter->drawPoint(cur->getX(), cur->getY());
            qDebug() << "painting nexts " << cur->getNexts()->size();
            for (auto next : *cur->getNexts())
            {
                painter->setPen(_penPath);
                painter->drawLine(cur->getX(), cur->getY(), next->getX(), next->getY());
                if (!visited.count(next))
                    q.push(next);
            }
        }
    }
}

void Drawer::drawMap(QPainter *painter, size_t tileSize, std::vector<Tile*>* map)
{
    QBrush _brush = QBrush("cyan", Qt::SolidPattern);
    //QPen _pen = QPen(_brush, 45, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    for (auto t : *map)
    {
        _brush.setColor(t->getColor());

        painter->fillRect(t->getX()*tileSize, t->getY()*tileSize, tileSize, tileSize, _brush);
    }
}
