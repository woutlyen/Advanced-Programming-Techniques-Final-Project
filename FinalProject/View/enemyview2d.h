#ifndef ENEMYVIEW2D_H
#define ENEMYVIEW2D_H

#include "View/gameobject2dview.h"
#include <world.h>

class EnemyView2D : public GameObject2DView
{
public:
    EnemyView2D(const std::unique_ptr<Enemy>& enemy, std::size_t gridSize);

protected:
    const std::unique_ptr<Enemy> &enemy;
    std::vector<QPixmap> idlePixmaps;
    std::vector<QPixmap> fightingPixmaps;
    std::vector<QPixmap> dyingPixmaps;
    virtual QString getIdlePixmapsPath() const { return ":/images/enemy_sprites/enemy_idle"; }
    virtual QString getFightingPixmapsPath() const { return ":/images/enemy_sprites/enemy_attack"; }
    virtual QString getDyingPixmapsPath() const { return ":/images/enemy_sprites/enemy_die"; }
    int animationTimerInterval = 500;
    void setAnimation();
    void initializeEnemy2DView();
private slots:
    virtual void onDefeated();
};

#endif // ENEMYVIEW2D_H
