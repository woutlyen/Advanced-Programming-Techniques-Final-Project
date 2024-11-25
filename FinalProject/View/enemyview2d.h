#ifndef ENEMYVIEW2D_H
#define ENEMYVIEW2D_H

#include <QGraphicsPixmapItem>
#include <world.h>

class EnemyView2D : public QGraphicsPixmapItem
{
public:
    EnemyView2D(const std::unique_ptr<Enemy>& enemy, std::size_t gridSize, QGraphicsItem* parent = nullptr);
};

#endif // ENEMYVIEW2D_H
