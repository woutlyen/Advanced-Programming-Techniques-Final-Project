#ifndef XENEMYVIEW2D_H
#define XENEMYVIEW2D_H

#include "View/enemyview2d.h"
#include "Model/xenemy.h"

class XEnemyView2D: public EnemyView2D
{
public:
    XEnemyView2D(const std::unique_ptr<EnemyWrapper>& enemy, std::size_t gridSize, QGraphicsItem* parent = nullptr);
private:
    QString getIdlePixmapsPath() const override{ return ":/images/xenemy_sprites/xenemy_idle"; }
    QString getFightingPixmapsPath() const override{ return ":/images/xenemy_sprites/xenemy_attack"; }
    QString getDyingPixmapsPath() const override{ return ":/images/xenemy_sprites/xenemy_die"; }
    void setAnimation() override;

    std::vector<QPixmap> initialDyingPixmaps;
    std::vector<QPixmap> initialIdlePixmaps;

    bool transformed{false};
    int getNrOfFramesDying() const override{ if(transformed){return dyingPixmaps.size();} else{return initialDyingPixmaps.size();}};
    int getNrOfFramesIdle() const override{ if(transformed){return idlePixmaps.size();} else{return initialIdlePixmaps.size();}};


private slots:
    void onDefeated() override;
    void onTransform();
    void startTransformationState();

};
#endif // XENEMYVIEW2D_H
