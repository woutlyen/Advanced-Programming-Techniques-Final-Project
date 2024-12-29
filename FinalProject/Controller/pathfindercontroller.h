#ifndef PATHFINDERCONTROLLER_H
#define PATHFINDERCONTROLLER_H

#include <vector>
#include "pathfinder_class.h"
#include "world.h"
#include "Model/node.h"

class PathfinderController
{
public:
    PathfinderController();
    std::vector<int> findNearestEnemy();
    std::vector<int> findNearestHealthPack();
    helper_func<Tile> costFunction = [](const Tile& current, const Tile& next){return next.getValue();};
    helper_func<Tile> manhattanDistanceFunction = [](const Tile& next, const Tile& dest){
        return std::abs(next.getXPos() - dest.getXPos()) + std::abs(next.getYPos() - dest.getYPos());
    };
    float getHeuristicWeight() const;
    void setHeuristicWeight(float newHeuristicWeight);
    Comparator<Node> comparator = [](const Node& node, const Node& otherNode) {return node.f > otherNode.f;};


    std::vector<Node> initializeNodes();
    std::vector<int> calculatePath(const Tile& start, const Tile& end);

private:
    float heuristicWeight = 0.0f;


};

#endif // PATHFINDERCONTROLLER_H
