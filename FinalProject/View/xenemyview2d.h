#ifndef XENEMYVIEW2D_H
#define XENEMYVIEW2D_H

#include "View/enemyview2d.h"

class XEnemyView2D: public EnemyView2D
{
public:
    XEnemyView2D(const std::unique_ptr<Enemy>& enemy, std::size_t gridSize, QGraphicsItem* parent = nullptr);

private:
    QString getIdlePixmapsPath() const override{ return ":/images/xenemy_sprites/xenemy_attack"; }
    QString getFightingPixmapsPath() const override{ return ":/images/xenemy_sprites/xenemy_attack"; }
    QString getDyingPixmapsPath() const override{ return ":/images/xenemy_sprites/xenemy_die"; }
    QString getTransformPixmapsPath() const {return ":/images/xenemy_sprites/xenemy_transform"; }

private slots:
    void onDefeated() override;
};
#endif // XENEMYVIEW2D_H
