#ifndef ENEMYVIEW2D_H
#define ENEMYVIEW2D_H

#include "Model/enemywrapper.h"
#include "View/gameobject2dview.h"
#include <world.h>

class EnemyView2D : public GameObject2DView
{
    Q_OBJECT
public:
    EnemyView2D(const std::unique_ptr<EnemyWrapper>& enemy, std::size_t gridSize);
    EnemyView2D(const std::unique_ptr<EnemyWrapper>& enemy, std::size_t gridSize, bool isDerivedClass);
    virtual ~EnemyView2D() = default;

protected:
    const std::unique_ptr<EnemyWrapper> &enemy;
    std::vector<QPixmap> idlePixmaps;
    std::vector<QPixmap> fightingPixmaps;
    std::vector<QPixmap> dyingPixmaps;
    int getNrOfFramesIdle() const override{ return idlePixmaps.size();}
    int getNrOfFramesWalking() const override{ return 0;}
    int getNrOfFramesFighting() const override{ return fightingPixmaps.size();}
    int getNrOfFramesDying() const override{ return dyingPixmaps.size();}
    virtual QString getIdlePixmapsPath() const { return ":/images/enemy_sprites/enemy_idle"; }
    virtual QString getFightingPixmapsPath() const { return ":/images/enemy_sprites/enemy_attack"; }
    virtual QString getDyingPixmapsPath() const { return ":/images/enemy_sprites/enemy_die"; }
    void setAnimation() override;
    void initializeEnemy2DView();

private slots:
    virtual void onDefeated();
};

#endif // ENEMYVIEW2D_H
