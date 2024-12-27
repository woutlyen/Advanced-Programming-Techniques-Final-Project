#include "pathfindercontroller.h"

PathfinderController::PathfinderController() {}

std::vector<int> PathfinderController::findNearestEnemy()
{

}

std::vector<int> PathfinderController::findNearestHealthPack()
{

}

float PathfinderController::getHeuristicWeight() const
{
    return heuristicWeight;
}

void PathfinderController::setHeuristicWeight(float newHeuristicWeight)
{
    heuristicWeight = newHeuristicWeight;
}

void PathfinderController::initializeNodes()
{

}
