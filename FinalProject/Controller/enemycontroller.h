#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include <world.h>
#include "Controller/gameobjectcontroller.h"
#include <QDebug>

class EnemyController: public GameObjectController
{
public:
    enum Position { Up, Down, Left, Right };

    bool checkForEnemy(const Position pos);

protected:
    virtual void attack(std::unique_ptr<Enemy> &enemy);
};

#endif // ENEMYCONTROLLER_H
