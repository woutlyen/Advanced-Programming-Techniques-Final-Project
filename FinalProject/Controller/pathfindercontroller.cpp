#include "pathfindercontroller.h"
#include "Controller/levelcontroller.h"

PathfinderController::PathfinderController() {}

std::vector<int> PathfinderController::findNearestEnemy()
{
    float shortestDistance = std::numeric_limits<float>::infinity();

    const auto & player = LevelController::getInstance().getCurrentLevel().protagonist;
    const auto & enemies = LevelController::getInstance().getCurrentLevel().enemies;
    bool enemyFound = false;

    Tile playerPosition(player->getXPos(), player->getYPos(), 0.0f);
    Tile nearestEnemyPosition{0,0,0};

    for(const auto& enemy: enemies){
        if(enemy->getDefeated()){
            continue;
        }

        if(PEnemyWrapper* penemy = dynamic_cast<PEnemyWrapper *>(enemy.get())){
            if(penemy->getPoisonStarted()){
                continue;
            }
        }

        Tile enemyPosition(enemy->getXPos(), enemy->getYPos(), enemy->getValue());
        float distance = manhattanDistanceFunction(playerPosition, enemyPosition);

        if(distance <= shortestDistance){
            shortestDistance = distance;
            nearestEnemyPosition.setXPos(enemy->getXPos());
            nearestEnemyPosition.setYPos(enemy->getYPos());
            enemyFound = true;
        }
    }

    if(!enemyFound){
        return {};
    }

    qDebug() << "Player is at x: " << playerPosition.getXPos() << " And y: " << playerPosition.getYPos();
    qDebug() << "Going to enemy at x: " << nearestEnemyPosition.getXPos() << " And y: " << nearestEnemyPosition.getYPos();
    return calculatePath(playerPosition, nearestEnemyPosition);
}

std::vector<int> PathfinderController::findNearestHealthPack()
{
    float shortestDistance = std::numeric_limits<float>::infinity();

    const auto & player = LevelController::getInstance().getCurrentLevel().protagonist;
    const auto & healthpacks = LevelController::getInstance().getCurrentLevel().healthPacks;
    bool healthpackFound = false;

    Tile playerPosition(player->getXPos(), player->getYPos(), 0.0f);
    Tile nearestHealthpackPosition{0,0,0.0f};

    for(const auto& healthpack: healthpacks){
        if(healthpack->getValue() == 0){
            continue;
        }
        Tile healthpackPosition(healthpack->getXPos(), healthpack->getYPos(), healthpack->getValue());
        float distance = manhattanDistanceFunction(playerPosition, healthpackPosition);

        if(distance < shortestDistance){
            shortestDistance = distance;
            nearestHealthpackPosition.setXPos(healthpack->getXPos());
            nearestHealthpackPosition.setYPos(healthpack->getYPos());
            healthpackFound = true;
        }
    }

    if(!healthpackFound){
        return {};
    }

    qDebug() << "Player is at x: " << playerPosition.getXPos() << " And y: " << playerPosition.getYPos();
    qDebug() << "Going to hp at x: " << nearestHealthpackPosition.getXPos() << " And y: " << nearestHealthpackPosition.getYPos();
    return calculatePath(playerPosition, nearestHealthpackPosition);
}

float PathfinderController::getHeuristicWeight() const
{
    return heuristicWeight;
}

void PathfinderController::setHeuristicWeight(float newHeuristicWeight)
{
    heuristicWeight = newHeuristicWeight;
}

std::vector<Node> PathfinderController::initializeNodes()
{
    std::vector<Node> nodes;
    std::vector<std::unique_ptr<Tile>> &tiles = LevelController::getInstance().getCurrentLevel().tiles;

    for (const auto& tile : tiles)
    {

        float val = (tile->getValue());
        if (val == std::numeric_limits<float>::infinity()){
            nodes.emplace_back(tile->getXPos(), tile->getYPos(), val);;
        }
        else{
            nodes.emplace_back(tile->getXPos(), tile->getYPos(), 1.0-val);;
        }
    }
    return nodes;
}

std::vector<int> PathfinderController::calculatePath(const Tile &start, const Tile &end)
{
    std::vector<Node> nodes = initializeNodes();
    PathFinder<Node, Tile> pathfinder(nodes, &start, &end, comparator, LevelController::getInstance().getCurrentLevel().width, costFunction, manhattanDistanceFunction, heuristicWeight);
    return pathfinder.A_star();
}

