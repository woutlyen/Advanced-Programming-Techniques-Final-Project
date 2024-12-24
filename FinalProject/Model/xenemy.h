#ifndef XENEMY_H
#define XENEMY_H

#include "Model/enemyrevised.h"
#include <world.h>

class XEnemy: public EnemyRevised
{
public:
    XEnemy(int xPosition, int yPosition, float strength);

private:
    void attack() override;
};

#endif // XENEMY_H
