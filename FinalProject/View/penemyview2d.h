#ifndef PENEMYVIEW2D_H
#define PENEMYVIEW2D_H

#include "View/enemyview2d.h"

class PEnemyView2D: public EnemyView2D
{
public:
    PEnemyView2D(const std::unique_ptr<Enemy>& enemy, std::size_t gridSize, QGraphicsItem* parent = nullptr);

protected:
    void updatePixMap() override;
};

#endif // PENEMYVIEW2D_H
