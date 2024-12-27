#include "xenemyview2d.h"

XEnemyView2D::XEnemyView2D(const std::unique_ptr<EnemyWrapper> &enemy, std::size_t gridSize, QGraphicsItem *parent):EnemyView2D(enemy, gridSize, true)
{
    initializeEnemy2DView();

    initialDyingPixmaps = extractFrames(":/images/xenemy_sprites/xenemy_transform");
    initialIdlePixmaps = extractFrames(":/images/enemy_sprites/enemy_idle");

    connect(enemy.get(), &EnemyWrapper::dead, this, &XEnemyView2D::onDefeated);
    connect(static_cast<XEnemy*>(enemy.get()), &XEnemy::transform, this, &XEnemyView2D::onTransform);

}

void XEnemyView2D::setAnimation()
{
    switch (currentState) {
    case Idle:
        if(!transformed){
            setPixmap(initialIdlePixmaps[currentFrameIndex]);
        }
        else{
            setPixmap(idlePixmaps[currentFrameIndex]);
        }
        break;

    case Fighting:
        setPixmap(fightingPixmaps[currentFrameIndex]);
        break;

    case Dying:
        animationTimer->setInterval(120);

        if(!transformed){
            setPixmap(initialDyingPixmaps[currentFrameIndex]);
            if (currentFrameIndex >= getNrOfFramesDying() - 1) {
                startTransformationState();
            }
        }
        else{
           setPixmap(dyingPixmaps[currentFrameIndex]);
        }
        break;

    case Walking:
        break;
    }
}

void XEnemyView2D::onDefeated()
{
    if(currentState != Dying){
        setState(Dying);
    }
}

void XEnemyView2D::onTransform()
{
    setState(Dying);
}

void XEnemyView2D::startTransformationState()
{
    currentState = Fighting;
    currentFrameIndex = 0;
    transformed = true;
}

