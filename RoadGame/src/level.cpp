#include "level.h"

#include <QFile>

#include <QDebug>

Level::Level()
{

}

bool Level::LoadMap(int num)
{
    QFile file ("maps/map_1.txt");
    QString errMsg;
    QFileDevice::FileError err = QFileDevice::NoError;
    if (!file.open(QIODevice::ReadOnly)) {
        errMsg = file.errorString();
        err = file.error();
    }

    qDebug() << errMsg;

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

    return true;
}
