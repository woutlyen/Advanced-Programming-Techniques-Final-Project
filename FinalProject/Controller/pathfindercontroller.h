#ifndef PATHFINDERCONTROLLER_H
#define PATHFINDERCONTROLLER_H

#include <vector>
#include "pathfinder_class.h"
#include "world.h"
#include "Model/node.h"
#include "Controller/levelcontroller.h"

class PathfinderController
{
public:
    PathfinderController();
    std::vector<int> findNearestEnemy();
    std::vector<int> findNearestHealthPack();

    // The cost function g is calculated by the tile value (the energy it will take from the player). Ranges from 0-1.
    helper_func<Tile> costFunction = [](const Tile& current, const Tile& next){return next.getValue();};

    /**
     *  The heuristic function is calculated using the Manhattan Distance function. As this value is significantly larger than the cost function,
     *  the calculated distance is scaled based on the maximum distance possible (between two opposite corners for 30x30 map)
    **/
    helper_func<Tile> manhattanDistanceFunction = [](const Tile& next, const Tile& dest){
        float scaled =  LevelController::getInstance().getCurrentLevel().height - 1 + LevelController::getInstance().getCurrentLevel().height - 1;
        return (std::abs(next.getXPos() - dest.getXPos()) + std::abs(next.getYPos() - dest.getYPos()))/scaled;
    };

    /**
     * Comparator for priority queue. Lowest total cost must be dequeued first, so the comparator
     * Priority queue compare parameter: "Note that the Compare parameter is defined such that it returns true if its
     * first argument comes before its second argument in a weak ordering. But because the priority queue outputs largest
     * elements first, the elements that "come before" are actually output last. That is, the front of the queue contains
     * the "last" element according to the weak ordering imposed by Compare."
     **/
    Comparator<Node> comparator = [](const Node& node, const Node& otherNode) {return node.f > otherNode.f;};

    float getHeuristicWeight() const;
    void setHeuristicWeight(float newHeuristicWeight);

    std::vector<Node> initializeNodes();
    std::vector<int> calculatePath(const Tile& start, const Tile& end);

private:
    //
    float heuristicWeight = 1.0f;


};

#endif // PATHFINDERCONTROLLER_H
