#include "xenemyview2d.h"

XEnemyView2D::XEnemyView2D(const std::unique_ptr<EnemyWrapper> &enemy, std::size_t gridSize, QGraphicsItem *parent):EnemyView2D(enemy, gridSize, true)
{
    initializeEnemy2DView();
    connect(enemy.get(), &EnemyWrapper::dead, this, &XEnemyView2D::onDefeated);
}

void XEnemyView2D::onDefeated()
{
    if(currentState != Dying){
        setState(Dying);
    }
}

