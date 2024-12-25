#ifndef WORLDREVISED_H
#define WORLDREVISED_H

#include "Model/enemywrapper.h"
#include "Model/penemywrapper.h"
#include <world.h>


class WorldRevised: public World
{
public:
    WorldRevised();
    void createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio = 0.25f, float xRatio = 0.25f);
    [[nodiscard]] std::vector<std::unique_ptr<EnemyWrapper>> getEnemies();

private:
    QImage world;
    std::vector<std::unique_ptr<EnemyWrapper>> enemies;
    void convertToEnemyWrapper(std::vector<std::unique_ptr<Enemy>> enemies);
};

#endif // WORLDREVISED_H
