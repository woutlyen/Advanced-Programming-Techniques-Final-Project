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
    [[nodiscard]] std::unique_ptr<Player> getPlayer();

private:
    QImage world;
    std::vector<std::unique_ptr<EnemyWrapper>> enemies;
    std::unique_ptr<Player> player;
    void convertToEnemyWrapper(std::vector<std::unique_ptr<Enemy>> oldEnemies);
    void convertToPlayerWrapper(std::unique_ptr<Protagonist> oldPlayer);
};

#endif // WORLDREVISED_H
