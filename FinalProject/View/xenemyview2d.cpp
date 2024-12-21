#include "xenemyview2d.h"

XEnemyView2D::XEnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize, QGraphicsItem *parent):EnemyView2D(enemy, gridSize)
{
    initializeEnemy2DView();
    connect(enemy.get(), &Enemy::dead, this, &XEnemyView2D::onDefeated);
}

void XEnemyView2D::onDefeated()
{
    if(currentState != Dying){
        setState(Dying);
    }
}

