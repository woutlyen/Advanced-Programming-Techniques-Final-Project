#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include <world.h>
#include "Model/player.h"
#include "qdebug.h"

class EnemyController
{
public:
    enum Position { Up, Down, Left, Right };

    bool checkForEnemy(const Position pos);

protected:
    virtual void attack(std::unique_ptr<Enemy> &enemy);
};

#endif // ENEMYCONTROLLER_H
