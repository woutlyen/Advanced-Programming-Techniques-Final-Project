#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include <world.h>
#include "qdebug.h"

class EnemyController
{
public:
    enum Position { Up, Down, Left, Right };

    bool checkForEnemy(const Position pos) const;

protected:
    virtual void attack(std::unique_ptr<Enemy> &enemy, std::unique_ptr<Player> &protagonist);
};

#endif // ENEMYCONTROLLER_H
