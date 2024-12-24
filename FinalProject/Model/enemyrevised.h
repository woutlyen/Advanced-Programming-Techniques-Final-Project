#ifndef ENEMYREVISED_H
#define ENEMYREVISED_H
#include "world.h"

class EnemyRevised : public Enemy
{
public:
    EnemyRevised();

private:
    virtual void attack();
};

#endif // ENEMYREVISED_H
