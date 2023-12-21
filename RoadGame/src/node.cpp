#include "node.h"

#include <QDebug>

Node::Node(int x, int y, int h, char colorTag, NodeType type)
{
    _x = x;
    _y = y;
    _h = h;
    _colorTag = colorTag;
    _type = type;
}

void Node::addNext(Node *next)
{
    _nextNodes.push_back(next);
}

std::vector<Node*>* Node::getNexts()
{
    return &_nextNodes;
}

void Node::addPrev(Node *next)
{
    _prevNodes.push_back(next);
}

std::vector<Node*>* Node::getPrevs()
{
    return &_prevNodes;
}
