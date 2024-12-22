#ifndef PENEMYCONTROLLER_H
#define PENEMYCONTROLLER_H

#include "enemycontroller.h"

class PEnemyController : public EnemyController
{
public:
    PEnemyController();
    void attack(std::unique_ptr<Enemy> &enemy, std::unique_ptr<Player> &protagonist) override;
};

#endif // PENEMYCONTROLLER_H
