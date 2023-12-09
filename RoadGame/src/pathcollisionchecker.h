#ifndef PATHCOLLISIONCHECKER_H
#define PATHCOLLISIONCHECKER_H

#include <vector>

#include "node.h"
#include "tile.h"

class PathCollisionChecker
{
public:
    PathCollisionChecker(size_t, size_t, size_t ,std::vector<Tile*>*);
    Node* addNode(int x, int y, int h);
    bool checkCollision(int x, int y, int h);
private:
    std::vector<std::vector<Node*>> _NodeTileContainer;
    std::vector<Tile*>* _tileMap;

    std::vector<std::pair<int,int>> _adjsCoords ={ {-1,-1}, {0,-1}, {1,-1},
                                                   {-1,0}, {0,0}, {1,0},
                                                   {-1,1}, {0,1}, {1,1}
                                                 };

    //bool checkCollision(int x, int y, int h);

    size_t _tileSize;
    size_t _columns;
    size_t _rows;
};

#endif // PATHCOLLISIONCHECKER_H
