#ifndef WORLDREVISED_H
#define WORLDREVISED_H

#include <world.h>


class WorldRevised: public World
{
public:
    WorldRevised();
    void createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio = 0.25f, float xRatio = 0.25f);
    [[nodiscard]] std::vector<std::unique_ptr<Enemy>> getEnemies();

private:
    QImage world;
    std::vector<std::unique_ptr<Enemy>> enemies;
};

#endif // WORLDREVISED_H
