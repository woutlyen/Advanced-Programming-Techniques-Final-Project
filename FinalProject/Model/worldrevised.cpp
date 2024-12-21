#include "worldrevised.h"

#include "xenemy.h"

#include <bits/random.h>
#include <iostream>

WorldRevised::WorldRevised() {}

void WorldRevised::createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio, float xRatio)
{
    //use World to generate HP & E & PE
    World::createWorld(filename,nrOfEnemies, nrOfHealthpacks, pRatio);
    enemies = World::getEnemies();
    world.load(filename);

    //generate XEnemies
    std::random_device r;

    // Choose a random distribution for x, y and strength
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_x(0, getRows() - 1);
    std::uniform_int_distribution<int> uniform_y(0, getCols() - 1);
    std::uniform_int_distribution<int> uniform_perc(0, 100);

    xRatio = std::min(xRatio, 1-pRatio);
    int XEnemyCounter = (int)(xRatio*(float)nrOfEnemies);

    for (size_t i = 0; i < enemies.size(); i++){
        if(typeid(enemies.at(i).get()) == typeid(Enemy*)){
            int xPos = enemies.at(i)->getXPos();
            int yPos = enemies.at(i)->getYPos();
            float val = enemies.at(i)->getValue();
            enemies.erase(enemies.begin() + i);

            std::cout << "Voor: " << enemies.size() << std::endl;

            auto eptr = std::make_unique<XEnemy>(xPos, yPos, val);
            enemies.emplace(enemies.begin()+i, std::move(eptr));

            std::cout << "Achter: " << enemies.size() << std::endl;

            if(XEnemyCounter > 1)
                XEnemyCounter--;
            else
                break;
        }
    }

    //be sure at least 1 XEnemy in the collection
    if (XEnemyCounter == (int)(xRatio/(float)nrOfEnemies) && enemies.size() >= 2) {
        int xPos = enemies.at(0)->getXPos();
        int yPos = enemies.at(0)->getYPos();
        float val = enemies.at(0)->getValue();
        enemies.erase(enemies.begin());

        auto eptr = std::make_unique<XEnemy>(xPos, yPos, val);
        enemies.push_back(std::move(eptr));
    }

}

std::vector<std::unique_ptr<Enemy>> WorldRevised::getEnemies()
{
    if (world.isNull())
        throw "No enemies created yet";
    return std::move(enemies);
}
