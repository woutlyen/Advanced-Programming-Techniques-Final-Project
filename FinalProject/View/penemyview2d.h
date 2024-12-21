#ifndef PENEMYVIEW2D_H
#define PENEMYVIEW2D_H

#include "enemyview2d.h"
#include <world.h>


class PEnemyView2D: public EnemyView2D
{
public:
    PEnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize);

private:
    QString getIdlePixmapsPath() const override{ return ":/images/penemy_sprites/penemy_idle"; }
    QString getFightingPixmapsPath() const override{ return ":/images/penemy_sprites/penemy_attack"; }
    QString getDyingPixmapsPath() const override{ return ":/images/penemy_sprites/penemy_die"; }

private slots:
    void onDefeated() override;
};

#endif // PENEMYVIEW2D_H
