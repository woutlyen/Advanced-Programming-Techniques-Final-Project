#include "worldrevised.h"

#include "xenemy.h"

WorldRevised::WorldRevised() {}

void WorldRevised::createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio, float xRatio)
{
    //use World to generate HP & E & PE
    World::createWorld(filename,nrOfEnemies, nrOfHealthpacks, pRatio);

    convertToEnemyWrapper(World::getEnemies());
    convertToPlayerWrapper(World::getProtagonist());

    world.load(filename);

    xRatio = std::min(xRatio, 1-pRatio);
    int XEnemyCounter = (int)(xRatio*(float)nrOfEnemies);

    for (size_t i = 0; i < enemies.size(); i++){
        if(typeid(enemies.at(i).get()) == typeid(EnemyWrapper*)){
            int xPos = enemies.at(i)->getXPos();
            int yPos = enemies.at(i)->getYPos();
            float val = enemies.at(i)->getValue();
            enemies.erase(enemies.begin() + i);

            //std::cout << "Voor: " << enemies.size() << std::endl;

            auto eptr = std::make_unique<XEnemy>(xPos, yPos, val);
            enemies.emplace(enemies.begin()+i, std::move(eptr));

            //std::cout << "Achter: " << enemies.size() << std::endl;

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

std::vector<std::unique_ptr<EnemyWrapper>> WorldRevised::getEnemies()
{
    if (world.isNull())
        throw "No enemies created yet";
    return std::move(enemies);
}

std::unique_ptr<Player> WorldRevised::getPlayer()
{
    if (world.isNull())
        throw "No player created yet";
    return std::move(player);
}

void WorldRevised::convertToEnemyWrapper(std::vector<std::unique_ptr<Enemy>> oldEnemies)
{
    for (auto& enemy : oldEnemies) {
        if(dynamic_cast<PEnemy *>(enemy.get())){
            enemies.push_back(std::make_unique<PEnemyWrapper>(std::move(enemy)));
        }
        else{
            enemies.push_back(std::make_unique<EnemyWrapper>(std::move(enemy)));
        }
    }
}

void WorldRevised::convertToPlayerWrapper(std::unique_ptr<Protagonist> oldPlayer)
{
    player = std::make_unique<Player>(std::move(oldPlayer));
}
