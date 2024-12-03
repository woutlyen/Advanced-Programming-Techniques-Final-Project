#ifndef XENEMYVIEW2D_H
#define XENEMYVIEW2D_H

#include "View/enemyview2d.h"

class XEnemyView2D: public EnemyView2D
{
public:
    XEnemyView2D(const std::unique_ptr<Enemy>& enemy, std::size_t gridSize, QGraphicsItem* parent = nullptr);
    void initPixMap();

protected:
    void updatePixMap() override;
};

#endif // XENEMYVIEW2D_H
