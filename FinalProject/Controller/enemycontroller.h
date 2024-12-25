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
};

#endif // ENEMYCONTROLLER_H
