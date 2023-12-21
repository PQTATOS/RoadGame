#include <unordered_set>
#include <queue>

#include "drawer.h"

Drawer::Drawer()
{

}

void Drawer::drawPathDebug(QPainter *painter, Node *node)
{
    QBrush _brushPoint = QBrush(QColor("pink"), Qt::SolidPattern);
    QPen _penPoint = QPen(_brushPoint, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush _brush = QBrush(QColor("red"), Qt::SolidPattern);
    QPen _penPath = QPen(_brush, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    std::queue<Node*> q;
    std::unordered_set<Node*> visited;

    q.push(node);

    while (!q.empty())
    {
        Node* cur = q.back();
        q.pop();
        visited.insert(cur);

        painter->setPen(_penPoint);
        painter->drawPoint(cur->getX(), cur->getY());
        for (auto next : *cur->getNexts())
        {
            painter->setPen(_penPath);
            painter->drawLine(cur->getX(), cur->getY(), next->getX(), next->getY());
            if (!visited.count(next))
                q.push(next);
        }
    }
}
