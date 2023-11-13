#ifndef BOXCOLIDER_H
#define BOXCOLIDER_H

#include <QPointF>

class BoxColider
{
public:
    BoxColider();
    bool isOverlap(const BoxColider& obj);
    void resize();
private:
    QPointF m_min;
    QPointF m_max;
};

#endif // BOXCOLIDER_H
