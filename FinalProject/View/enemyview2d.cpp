#include "enemyview2d.h"

EnemyView2D::EnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize)
    : GameObject2DView(gridSize), enemy(enemy) {

    initializeEnemy2DView();
    // Connect signals & slots
    connect(enemy.get(), &Enemy::dead, this, &EnemyView2D::onDefeated);
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
        setPixmap(dyingPixmaps[currentFrameIndex]);
        break;

    case Walking:
        break;
    }
}

void EnemyView2D::initializeEnemy2DView()
{
    // Initialize all Pixmaps
    idlePixmaps = extractFrames(getIdlePixmapsPath());
    fightingPixmaps = extractFrames(getFightingPixmapsPath()); //Unused for now
    dyingPixmaps = extractFrames(getDyingPixmapsPath());

    // Initialize Pixmap Animation Sizes
    nrOfFramesIdle = idlePixmaps.size();
    nrOfFramesWalking = 0;
    nrOfFramesFighting = fightingPixmaps.size();
    nrOfFramesDying = dyingPixmaps.size();

    // Set the initial pixmap
    setPixmap(idlePixmaps[0]);
    setPos(gridSize*enemy->getXPos(), gridSize*enemy->getYPos());

    // Configure the animation timer
    animationTimer->setInterval(animationTimerInterval); // Frame switch interval (in milliseconds)
    animationTimer->start();
    GameObject2DView::connectAnimationTimer();
}

void EnemyView2D::onDefeated()
{
    if(currentState != Dying){
        setState(Dying);
    }
}
