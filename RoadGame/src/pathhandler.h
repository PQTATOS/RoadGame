#ifndef PATHHANDLER_H
#define PATHHANDLER_H

#include <unordered_set>

#include "node.h"
#include "tile.h"

class PathHandler
{
public:
    PathHandler(size_t rows, size_t columns, size_t tileSize, bool* ptr);

    void loadNewTileMap(std::vector<Tile*>* map);

    std::unordered_set<Node*>* getPathBegins() { return &_pathBegins; }

    void addNode(int x, int y, int h);
    void addNodeNew(int x, int y, int h);
    void stopAdding();
    void addLevelNode(Node*);

    void restartLevel();
private:
    std::unordered_set<Node*> _pathBegins;
    std::unordered_set<Node*> _levelNodes;
    std::vector<std::vector<Node*>> _nodeContainer;
    std::vector<Tile*> _tileMap;

    std::vector<std::pair<int,int>> _adjsCoords ={ {-1,-1}, {0,-1}, {1,-1},
                                                   {-1,0}, {0,0}, {1,0},
                                                   {-1,1}, {0,1}, {1,1}
                                                 };

    bool* _isPathContinues;
    Node* _prevNode;
    int nodeCount;

    size_t _tileSize;
    size_t _columns;
    size_t _rows;

    Tile* _emptyTile;

    void getAdjsntNodes(int x, int y, std::vector<Node*>& nodes);
    bool checkCollision(int x, int y, int h);

    int getDist(int x, int y, Node* node);
};

#endif // PATHHANDLER_H
