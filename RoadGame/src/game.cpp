#include "game.h"

#include <QDebug>
#include <QFile>
#include <queue>


Game::Game()
{
    _paths = new PathHandler(_tileRowCount, _tileColumCount, _tileSize, &_isPathContinues);
    Car::initStatic(_tileColumCount, _tileRowCount, _tileSize);
    _carContainer.resize(_tileColumCount*_tileRowCount);
    qDebug() << "game loaded";
}

void Game::loadLevel(int level)
{
    qDebug() << "loading map";
    std::string path = ":/src/levels/lv"+ std::to_string(level) +".txt";
    QFile map(path.c_str());
    if (!map.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "fail to open " <<  map.fileName() << ", is exsist " << map.exists();
        return;
    }
    while (!map.atEnd())
    {
        QString line = map.readLine();
        QStringList list = line.split(' ');

        char type = list.at(0).toStdString()[0];
        switch (type) {
        case 'E':
        {
            qDebug() << "Loading Enterence";

            QString idStr = map.readLine();
            int id = idStr.toInt();
            qDebug() << idStr;
            QString coords = map.readLine();
            QStringList listCoords = coords.split(' ');
            Node* n1 = new Node(list.at(1).toInt()*_tileSize+listCoords.at(0).toInt(),
                                list.at(2).toInt()*_tileSize+listCoords.at(1).toInt(),
                                0, NodeType::Entrance);
            coords = map.readLine();
            listCoords = coords.split(' ');
            n1->addNext(new Node(list.at(1).toInt()*_tileSize+listCoords.at(0).toInt(),
                                 list.at(2).toInt()*_tileSize+listCoords.at(1).toInt(),
                                 0));
            n1->getNexts()->at(0)->addPrev(n1);
            _paths->addLevelNode(n1);
            _roadBegins[id] = n1;
            qDebug() << "begins Size" << _roadBegins.size() << " id " << id;
            break;
        }
        case 'X':
        {
            qDebug() << "Loading Exit";

            QString idStr = map.readLine();
            int id = idStr.toInt();
            qDebug() << idStr;

            QString coords = map.readLine();
            QStringList listCoords = coords.split(' ');

            Node* n1 = new Node(list.at(1).toInt()*_tileSize+listCoords.at(0).toInt(),
                                list.at(2).toInt()*_tileSize+listCoords.at(1).toInt(),
                                0, NodeType::Exit);
            coords = map.readLine();
            listCoords = coords.split(' ');
            Node* n2 = new Node(list.at(1).toInt()*_tileSize+listCoords.at(0).toInt(),
                                list.at(2).toInt()*_tileSize+listCoords.at(1).toInt(),
                                0);
            n1->addPrev(n2);
            n2->addNext(n1);
            _paths->addLevelNode(n1);
            _roadEnds[id] = n1;
            qDebug() << "ends Size" << _roadEnds.size() << " id " << id;
            break;
        }
        case 'S':
        {
            qDebug() << "Loading Sign";
            QString idCount = map.readLine();
            QStringList listIdCount = idCount.split(' ');
            SignTile* sign = new SignTile(listIdCount.at(0).toInt(), list.at(1).toInt(), list.at(2).toInt(), type, "yellow");
            _levelMap.push_back((Tile*)sign);

            for (int i = 0; i < listIdCount.at(1).toInt(); ++i)
            {
                QString road = map.readLine();
                QStringList listRoad = road.split(' ');
                sign->addConnection(listRoad.at(0).toInt(), listRoad.at(1).toInt());
                _signs.push_back(sign);
            }
            break;
        }
        default:
            _levelMap.push_back(new Tile(list.at(1).toInt(), list.at(2).toInt(), type, "blue"));
            qDebug() << "Check 2";
            break;
        }
    }
    qDebug() << "map loded";

    _paths->loadNewTileMap(&_levelMap);
}

void Game::makeCarPaths()
{
    for (auto sign : _signs)
    {
        for (auto need: *(sign->getNeeds()))
        {
            std::queue<Node*> q;
            std::unordered_set<Node*> visited;
            std::unordered_map<Node*, Node*> prev;
            bool isFinded = false;

            q.push(_roadBegins[sign->getId()]);
            visited.insert(q.front());

            while (!q.empty())
            {
                Node* cur = q.front();
                q.pop();


                for (auto next : *cur->getNexts())
                {
                    if (!visited.count(next))
                    {
                        q.push(next);
                        visited.insert(next);
                        prev[next] = cur;
                    }
                    if (next == _roadEnds[need.first])
                    {
                        isFinded = true;
                        break;
                    }
                }
                if (isFinded)
                    break;
            }

            if (!prev.count(_roadEnds[need.first]))
                continue;

            Node* cur = _roadEnds[need.first];
            std::vector<Node*> p;
            while (cur != _roadBegins[sign->getId()])
            {
                p.push_back(cur);
                cur = prev[cur];
            }
            std::vector<Node*> newVec;
            for (auto end = p.rbegin(); end < p.rend(); ++end)
            {
                qDebug() << "       " << (*end)->getX() << ' ' << (*end)->getY();
                 newVec.push_back(*end);
            }
            _carPaths[sign->getId()][need.first] = newVec;
        }
    }
}

void Game::reqSimUpdate()
{
    if (_carCount < 2)
    {
        qDebug() << !(_carPaths)[1][2].empty();
        if (!(_carPaths)[1][2].empty()  && _car2Count < 1)
        {
            qDebug() << "adding  in car " << _roadBegins[1]->getX();
            ++_car2Count;
            ++_carCount;
            _carList.insert(new Car(_roadBegins[1]->getX(),_roadBegins[1]->getY(),1, 2, &_carPaths, &_carContainer));
            qDebug() << "added car 1";
        }
        if (!(_carPaths)[2][1].empty() && _car1Count < 1)
        {
            ++_carCount;
            ++_car1Count;
            _carList.insert(new Car(_roadBegins[2]->getX(),_roadBegins[2]->getY(),2, 1, &_carPaths, &_carContainer));
            qDebug() << "added car 2";
        }
        makeCarPaths();
    }
    if (_carCount == 0)
        return;
    qDebug() << "car counr " << _carList.size();
    std::vector<Car*> toDel;
    for(auto car : _carList)
    {
        car->updateCar();
        if (car->_isFinalDest)
            toDel.push_back(car);
    }

    for (auto car : toDel)
    {
        --_carCount;
        car->getId() == 1 ? --_car1Count : --_car2Count;
        _carList.erase(car);
    }
}

std::vector<Tile*>* Game::getLevel()
{
    return &_levelMap;
}

void Game::addPath(int x, int y)
{
    _paths->addNodeNew(x,y,0);
}

void Game::startAddingPath()
{
    _isPathContinues = true;
}

void Game::stopAddingPath()
{
    _paths->stopAdding();
}

void Game::restartLevel()
{
    _paths->restartLevel();
}

