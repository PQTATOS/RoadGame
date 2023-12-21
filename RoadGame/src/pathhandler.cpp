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

    _nodeContainer.resize(_rows * _columns);
}

void PathHandler::loadNewTileMap(std::vector<Tile *> *map)
{
    _tileMap = map;

    for (size_t x = 0; x < _columns; ++x)
    {
        for (size_t y = 0; y < _rows; ++y)
        {
            if ((*_tileMap)[y*_columns + x]->getType() == TileType::Entrance)
            {
                _nodeContainer[y*_columns + x].push_back(new Node(x*_tileSize+30, y*_tileSize+30, 0, 'r', NodeType::Entrance));
                _pathBegins.insert(_nodeContainer[y*_columns + x].back());
            }
            else if ((*_tileMap)[y*_columns + x]->getType() == TileType::Exit)
            {
                _nodeContainer[y*_columns + x].push_back(new Node(x*_tileSize+_tileSize/2, y*_tileSize+_tileSize/2, 0, 'r', NodeType::Exit));
                _pathBegins.insert(_nodeContainer[y*_columns + x].back());
            }
        }
    }
}

void PathHandler::addNode(int x, int y, int h)
{
    if (!*_isPathContinues)
        return;

    int nX = x/_tileSize, nY = y/_tileSize;

    if (checkCollision(nX,nY,h))
    {
        *_isPathContinues = false;
        _prevNode = nullptr;
        return;
    }

    std::vector<Node*> nodes;
    getAdjsntNodes(x, y, nodes);

    qDebug() << nodes.size();
    if (_prevNode != nullptr)
    {
        int dist = getDist(x, y, _prevNode);
        qDebug() << "dist " <<  dist;
        if (dist > 45)
        {
            qDebug() << "adde";

            Node* node = new Node(x,y, h, 'r');
            node->addPrev(_prevNode);
            _nodeContainer[nY*_columns + nX].push_back(node);
            _prevNode->addNext(node);
            _prevNode = node;
        }
    }

    if (nodes.size() == 0)
    {
        _nodeContainer[nY*_columns + nX].push_back(new Node(x, y, h, 'r'));
        _pathBegins.insert(_nodeContainer[nY*_columns + nX].back());
        qDebug() << "new path begin added";
        _prevNode = _nodeContainer[nY*_columns + nX].back();
        return;
    }

    for (auto node : nodes)
    {
        if (node == _prevNode)
            continue;
        int dist = getDist(x, y, node);
        if (dist < 60)
        {
            if (_prevNode == nullptr)
            {
                Node* next = new Node(x,y,h,'r');
                node->addNext(next);
                _prevNode = next;
                break;
            }

            node->addPrev(_prevNode);
            _prevNode->addNext(node);
            break;
        }
    }
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
            qDebug() << "near dist " << dist;
            if (dist <= 90)
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
    TileType tType = (*_tileMap)[y*_columns + x]->getType();

    if (tType == TileType::Obstacle)
        return true;
    if (tType == TileType::River && h < 1)
        return true;

    return false;
}
