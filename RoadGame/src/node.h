
#ifndef NODE_H
#define NODE_H

#include <QPointF>
#include "baseobject.h"
#include <vector>

class Node : BaseObject
{
public:
    Node();
private:
    int m_height;
    std::vector<Node*> m_adjNodes;
};

#endif // NODE_H
