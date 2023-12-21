#ifndef NODE_H
#define NODE_H

#include <vector>

enum class NodeType : int
{
    Exit,
    Entrance,
    Path
};

class Node
{
public:
    Node(int x, int y, int h, char colorTag, NodeType type = NodeType::Path);

    int getX() { return _x; }
    int getY() { return _y; }
    int getHeight() { return _h; }

    void addNext(Node* next);
    std::vector<Node*>* getNexts();

    void addPrev(Node* next);
    std::vector<Node*>* getPrevs();

private:
    std::vector<Node*> _nextNodes;
    std::vector<Node*> _prevNodes;

    NodeType _type;
    char _colorTag;

    int _x;
    int _y;
    int _h;
};

#endif // NODE_H
