#ifndef ENEMYVIEW2D_H
#define ENEMYVIEW2D_H

#include "View/gameobject2dview.h"
#include <QGraphicsPixmapItem>
#include <world.h>

class EnemyView2D : public GameObject2DView
{
public:
    EnemyView2D(const std::unique_ptr<Enemy>& enemy, std::size_t gridSize);

private:
    std::vector<QPixmap> idlePixmaps;
    std::vector<QPixmap> fightingPixmaps;
    std::vector<QPixmap> dyingPixmaps;
    void setAnimation();
private slots:
    void onDefeated();
};

#endif // ENEMYVIEW2D_H
