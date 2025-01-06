#include "enemyview2d.h"

EnemyView2D::EnemyView2D(const std::unique_ptr<EnemyWrapper> &enemy, std::size_t gridSize)
    : GameObject2DView(gridSize){

    initializeEnemy2DView(enemy->getXPos(), enemy->getYPos());
    // Connect signals & slots
    connect(enemy.get(), &EnemyWrapper::dead, this, &EnemyView2D::onDefeated);
}

EnemyView2D::EnemyView2D(std::size_t gridSize)
    : GameObject2DView(gridSize) {
}

void EnemyView2D::setAnimation()
{
    switch (currentState) {
    case Idle:
        setPixmap(idlePixmaps[currentFrameIndex]);
        break;

    case Fighting:
        setPixmap(fightingPixmaps[currentFrameIndex]);
        break;

    case Dying:
        animationTimer->setInterval(120);
        setPixmap(dyingPixmaps[currentFrameIndex]);
        break;

    case Walking:
        break;
    }
}

void EnemyView2D::initializeEnemy2DView(int XPos, int YPos)
{
    // Initialize all Pixmaps
    idlePixmaps = extractFrames(getIdlePixmapsPath());
    fightingPixmaps = extractFrames(getFightingPixmapsPath()); //Unused for now
    dyingPixmaps = extractFrames(getDyingPixmapsPath());
    // Set the initial pixmap
    setPixmap(idlePixmaps[0]);
    setPos(gridSize*XPos, gridSize*YPos);

    // Configure the animation timer
    animationTimer->setInterval(240); // Frame switch interval (in milliseconds)
    animationTimer->start();
    connectAnimationTimer();

}

void EnemyView2D::onDefeated()
{
    if(currentState != Dying){
        setState(Dying);
    }
}
