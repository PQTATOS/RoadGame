#ifndef CAR_H
#define CAR_H

#include <utility>
#include <unordered_map>
#include <vector>

#include "node.h"
class Car
{
public:
    Car(int x, int y, int id, int toid,
        std::unordered_map<int, std::unordered_map<int, std::vector<Node*>>>* paths,
        std::vector<std::unordered_set<Car*>>* container
        );

    void updateCar();
    std::pair<float, float>* getPositin() { return &_position; };
    int getId()  { return _id; };

    static void initStatic(size_t clm, size_t row, size_t tSize);
    bool _isFinalDest = false;
private:
    int _id;
    int _toId;
    int _speed;
    std::pair<float, float> _position;
    std::pair<float, float> _velocity;

    size_t _curNode;
    Node* _destination;
    bool _isReachDest;
    std::unordered_map<int, std::unordered_map<int, std::vector<Node*>>>* _paths;
    std::vector<std::unordered_set<Car*>>* _carContainer;

    static inline size_t _tileSize = 1;
    static inline size_t _columns = 1;
    static inline size_t _rows = 1;

};
#endif // CAR_H
