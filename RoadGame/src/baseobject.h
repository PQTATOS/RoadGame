#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QPointF>

class BaseObject
{
public:
    BaseObject();
private:
    QPointF m_leftTop;
    float m_height;
    float m_width;
};

#endif // BASEOBJECT_H
