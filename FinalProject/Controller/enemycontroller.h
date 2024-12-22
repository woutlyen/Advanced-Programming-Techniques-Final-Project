#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "Model/player.h"
#include <world.h>
#include "qdebug.h"

class EnemyController
{
public:
    enum Position { Up, Down, Left, Right };

    EnemyController();
    bool checkForEnemy(std::vector<std::unique_ptr<Enemy>>& enemies, std::unique_ptr<Player>& protagonist, int width, int height, Position pos);

protected:
    virtual void attack(std::unique_ptr<Enemy> &enemy, std::unique_ptr<Player> &protagonist);
};

#endif // ENEMYCONTROLLER_H
