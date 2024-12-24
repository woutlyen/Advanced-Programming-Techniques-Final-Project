#ifndef PENEMYREVISED_H
#define PENEMYREVISED_H

#include "enemyrevised.h"
#include "world.h"

class PenemyRevised : public PEnemy, public EnemyRevised
{
public:
    PenemyRevised();

private:
    void attack() override;
};

#endif // PENEMYREVISED_H
