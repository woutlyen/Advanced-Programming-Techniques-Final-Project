#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include <world.h>


class EnemyController
{
public:
    enum Position { Up, Down, Left, Right };

    bool checkForEnemy(const Position pos) const;

};

#endif // ENEMYCONTROLLER_H
