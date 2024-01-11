#include "game.h"

#include <QDebug>
#include <QFile>


Game::Game()
{
    _paths = new PathHandler(_tileRowCount, _tileColumCount, _tileSize, &_isPathContinues);
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
            qDebug() << "x " <<list.at(1).toInt() << "y " << list.at(2).toInt();

            int id = map.readLine().toInt();
            QString coords = map.readLine();
            QStringList listCoords = coords.split(' ');
            qDebug() << "x " <<list.at(1).toInt()*_tileSize+listCoords.at(0).toInt() << "y " <<listCoords.at(1).toInt() ;
            Node* n1 = new Node(list.at(1).toInt()*_tileSize+listCoords.at(0).toInt(),
                                list.at(2).toInt()*_tileSize+listCoords.at(1).toInt(),
                                0, NodeType::Entrance);
            coords = map.readLine();
            listCoords = coords.split(' ');
            qDebug() << "x " <<list.at(1).toInt()*_tileSize+listCoords.at(0).toInt() << "y " <<listCoords.at(1).toInt() ;
            n1->addNext(new Node(list.at(1).toInt()*_tileSize+listCoords.at(0).toInt(),
                                 list.at(2).toInt()*_tileSize+listCoords.at(1).toInt(),
                                 0));
            n1->getNexts()->at(0)->addPrev(n1);
            _paths->addLevelNode(n1);
            _roadBegins[id] = n1;
            break;
        }
        case 'X':
        {
            qDebug() << "Loading Exit";

            int id = map.readLine().toInt();
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
                _signs[listIdCount.at(0).toInt()].push_back(
                            std::make_pair(
                                listRoad.at(0).toInt(),
                                listRoad.at(1).toInt())
                            );
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

