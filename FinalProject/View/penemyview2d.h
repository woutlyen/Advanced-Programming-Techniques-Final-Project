#ifndef PENEMYVIEW2D_H
#define PENEMYVIEW2D_H

#include "enemyview2d.h"
#include <world.h>
#include "Model/penemywrapper.h"
#include "Controller/levelcontroller.h"



class PEnemyView2D: public EnemyView2D
{
public:
    PEnemyView2D(const std::unique_ptr<EnemyWrapper> &enemy, std::size_t gridSize);
    void setPoisonCircle(int value);

private:
    int getNrOfFramesIdle() const override{ return idlePixmaps.size();}
    int getNrOfFramesWalking() const override{ return 0;}
    int getNrOfFramesFighting() const override{ return fightingPixmaps.size();}
    int getNrOfFramesDying() const override{ return dyingPixmaps.size();}
    QString getIdlePixmapsPath() const override{ return ":/images/penemy_sprites/penemy_idle"; }
    QString getFightingPixmapsPath() const override{ return ":/images/penemy_sprites/penemy_attack"; }
    QString getDyingPixmapsPath() const override{ return ":/images/penemy_sprites/penemy_die"; }
    QGraphicsEllipseItem* poisonCircle;
    void expandPoisonCircle();

private slots:
    void onDefeated() override;
    void onPoisonLevelValueUpdated(int value);
};

#endif // PENEMYVIEW2D_H
