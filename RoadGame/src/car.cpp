#include "car.h"
#include <QDebug>
#include <cmath>

Car::Car(int x, int y, int id, int toid,
         std::unordered_map<int, std::unordered_map<int, std::vector<Node*>>>* paths,
         std::vector<std::unordered_set<Car*>>* container
         )
{
    _id = id;
    _toId = toid;
    _position = std::make_pair(x,y);
    _paths = paths;
    _curNode = 0;
    _speed = 2;
    _destination = nullptr;
    _isReachDest = true;
    _carContainer = container;
    (*_carContainer)[(y/_tileSize)/_columns + (x/_tileSize)].insert(this);
}

void Car::initStatic(size_t clm, size_t row, size_t tSize)
{
    _columns = clm;
    _rows = row;
    _tileSize = tSize;
}

void Car::updateCar()
{
    qDebug() << "cur " << _curNode << " " << (*_paths)[_id][_toId].size()
             << (_isFinalDest || (_isReachDest && _curNode >= (*_paths)[_id][_toId].size()));
    if (_isFinalDest || (_isReachDest && _curNode >= (*_paths)[_id][_toId].size()))
    {
        qDebug() << "       final";
        _isFinalDest = true;
        return;
    }
    if (_isReachDest && !(*_paths)[_id][_toId].empty())
    {
        _destination = (*_paths)[_id][_toId][_curNode];
        float dirX = _destination->getX()-_position.first,
            dirY = _destination->getY()-_position.second;
        float len = std::sqrt(dirX*dirX + dirY*dirY);

        _velocity = std::make_pair((dirX / len) * _speed, (dirY/len) * _speed);
        ++_curNode;
        _isReachDest = false;
    }
    if (_destination != nullptr)
    {
        _position.first += _velocity.first;
        _position.second += _velocity.second;
        float dirX = _destination->getX()-_position.first,
            dirY = _destination->getY()-_position.second;
        float len = std::sqrt(dirX*dirX + dirY*dirY);
        if(len < 45)
            _isReachDest = true;
    }
}
