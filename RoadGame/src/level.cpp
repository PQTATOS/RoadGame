#include "level.h"

#include <QFile>

#include <QDebug>

Level::Level()
{

}

bool Level::LoadMap(int num)
{
    std::string deb_file = "###EX######"
                           "###########"
                           "###########"
                           "###########"
                           "###########"
                           "###########"
                           "###########"
                           "RRRRRRRRRRR"
                           "RRRR#######"
                           "###########"
                           "###########"
                           "##OO#######"
                           "##OO#######"
                           "###########"
                           "##########E"
                           "##########X"
                           "###########";
    for (int i = 0; i < deb_file.size(); ++i)
        _currentMap.push_back(new Tile(deb_file[i], ""));

    qDebug() << "Map loaded";

    return true;
}
