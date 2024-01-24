#include "pathhandler.h"

#include <cmath>
#include <QDebug>

PathHandler::PathHandler(size_t rows, size_t columns, size_t tileSize, bool* ptr)
{
    _tileSize = tileSize;
    _columns = columns;
    _rows = rows;
    _isPathContinues = ptr;

    _prevNode = nullptr;

    _emptyTile = new Tile(0, 0 ,'T', "white");

    _nodeContainer.resize(_rows * _columns);
    _tileMap.resize(_rows * _columns, _emptyTile);

}

void PathHandler::loadNewTileMap(std::vector<Tile *> *map)
{
    for (auto t : *map)
        _tileMap[t->getY()*_columns + t->getX()] = t;
}

void PathHandler::addNodeNew(int x, int y, int h)
{
    qDebug() << "start adding node ";
    if (!*_isPathContinues)
        return;

    int nX = x/_tileSize, nY = y/_tileSize;

    if (checkCollision(nX,nY,h))
    {
        *_isPathContinues = false;
        _prevNode = nullptr;
        return;
    }

    qDebug() << "Get adj nodes";
    std::vector<Node*> nodes;
    getAdjsntNodes(x, y, nodes);

    qDebug() << "Get crating node";
    //если вокруг нет точек, то создаем новое начало пути
    if (nodes.size() == 0 && _prevNode == nullptr)
    {
        _nodeContainer[nY*_columns + nX].push_back(new Node(x, y, h));
        _pathBegins.insert(_nodeContainer[nY*_columns + nX].back());
        _prevNode = _nodeContainer[nY*_columns + nX].back();
        return;
    }

    qDebug() << "Connecting adj nodes";
    //проверяем соседнии точки
    bool isConnected = false;
    Node* nodeToConnect;
    for (auto node : nodes)
    {
        if (node == _prevNode)
            continue;
        int dist = getDist(x, y, node);
        if (dist < 45)
        {
            isConnected = true;
            nodeToConnect = node;
        }
    }

    qDebug() << "Connect prev node";
    //соединяем с предыдущей точкой, если она есть, на растоянии 45 пикселей
    if (_prevNode == nullptr)
    {
        _prevNode = nodeToConnect;
        *_isPathContinues=true;
        return;
    }
    if (_prevNode != nullptr)
    {
        if (isConnected)
        {
            _prevNode->addNext(nodeToConnect);
            nodeToConnect->addPrev(_prevNode);
            *_isPathContinues = false;
            _prevNode = nullptr;
            return;
        }
        else if (getDist(x, y, _prevNode) > 45)
        {
            Node* node = new Node(x,y, h);
            node->addPrev(_prevNode);
            _nodeContainer[nY*_columns + nX].push_back(node);
            ++nodeCount;
            _prevNode->addNext(node);
            _prevNode = node;
            return;
        }
    }
    qDebug() << "No node added";
}

void PathHandler::getAdjsntNodes(int x, int y, std::vector<Node*> &nodes)
{
    int nX = x/_tileSize, nY = y/_tileSize;

    for (auto cords : _adjsCoords)
    {
        if ( nX+cords.first < 0 || nX+cords.first >= (int)_columns ||
             nY+cords.second < 0 || nY+cords.second >= (int)_rows)
            continue;
        for (auto tile : _nodeContainer[(nY+cords.second)*_columns + (nX+cords.first)])
        {
            int dist = getDist(x, y, tile);
            if(tile->getType() == NodeType::Entrance || tile->getType() == NodeType::Exit)
                qDebug() << "EX node " << dist;
            if (dist <= 60)
            {
                nodes.push_back(tile);
            }
        }
    }
}

void PathHandler::stopAdding()
{
    _prevNode = nullptr;
    *_isPathContinues = false;
}

int PathHandler::getDist(int x, int y, Node *node)
{
    int a = std::abs(node->getX() - x),
        b = std::abs(node->getY() - y);
    return std::sqrt(a*a + b*b);
}

bool PathHandler::checkCollision(int x, int y, int h)
{
    Tile* tType = _tileMap[y*_columns + x];

    if (tType->getType() == TileType::Obstacle)
        return true;
    if (tType->getType() == TileType::Sign)
        return true;
    if (tType->getType() == TileType::River && h < 1)
        return true;

    return false;
}

void PathHandler::addLevelNode(Node * node)
{
    _nodeContainer[(node->getY()/_tileSize)*_columns +
            (node->getX()/_tileSize)].push_back(node);
    _levelNodes.insert(node);
    qDebug() << "node base " << node;

    if (node->getType() == NodeType::Entrance)
    {
        _nodeContainer[(node->getY()/_tileSize)*_columns +
                (node->getX()/_tileSize)].push_back(node->getNexts()->at(0));
        _levelNodes.insert(node->getNexts()->at(0));
        qDebug() << "node E " << node->getNexts()->at(0);
        _pathBegins.insert(node);
    }
    else
    {
        _nodeContainer[(node->getY()/_tileSize)*_columns +
                (node->getX()/_tileSize)].push_back(node->getPrevs()->at(0));
        qDebug() << "node X " << node->getPrevs()->at(0);
        _levelNodes.insert(node->getPrevs()->at(0));
        _pathBegins.insert(node->getPrevs()->at(0));
    }
}

void PathHandler::restartLevel()
{
    std::unordered_set<Node*> visited;
    for(auto node : _levelNodes)
        node->clearNodes(&_levelNodes, &visited);
    qDebug() << "Clearing";
    std::vector<Node*> toDel;
    for(auto begin : _pathBegins)
    {
        if (_levelNodes.count(begin))
            continue;
        toDel.push_back(begin);
    }

    for (auto node : toDel)
        _pathBegins.erase(node);

    for (size_t i = 0; i < _nodeContainer.size(); ++i)
    {
        std::vector<Node*> vec;
        for (auto node : _nodeContainer[i])
        {
            if(_levelNodes.count(node))
            {
                qDebug() << "node level";
                vec.push_back(node);
                continue;
            }
            delete node;
        }
        _nodeContainer[i] = vec;
    }
}
