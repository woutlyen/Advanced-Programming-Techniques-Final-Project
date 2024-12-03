#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Model/player.h"
#include <world.h>


class EnemyController
{
public:
    enum Position { Up, Down, Left, Right };

    EnemyController();
    bool checkForEnemy(std::vector<std::unique_ptr<Enemy>>& enemies, std::unique_ptr<Player>& protagonist, int width, int height, Position pos);

};

#endif // ENEMYCONTROLLER_H
