#include "node.h"

#include <QDebug>

Node::Node(int x, int y, int h, NodeType type)
{
    _x = x;
    _y = y;
    _h = h;
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

void Node::clearNodes(std::unordered_set<Node*>* levelsN, std::unordered_set<Node*>* visited)
{
    std::vector<Node*> newNext;
    std::vector<Node*> newPrev;
    visited->insert(this);

    qDebug() << "New next " << _nextNodes.size();
    for(auto node : _nextNodes)
        if (levelsN->count(node))
        {
            newNext.push_back(node);
            if (!visited->count(node))
                node->clearNodes(levelsN, visited);
        }
    _nextNodes = newNext;
    for(auto node : _prevNodes)
        if (levelsN->count(node))
        {
            newPrev.push_back(node);
            if (!visited->count(node))
                node->clearNodes(levelsN, visited);
        }
    _prevNodes = newPrev;
    qDebug() << "New prev " << _prevNodes.size();
}
