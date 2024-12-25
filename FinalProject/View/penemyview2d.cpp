#include "penemyview2d.h"

PEnemyView2D::PEnemyView2D(const std::unique_ptr<EnemyWrapper> &enemy, std::size_t gridSize) :EnemyView2D(enemy, gridSize, true) {

    initializeEnemy2DView();
    // Connect signals & slots
    connect(enemy.get(), &EnemyWrapper::dead, this, &PEnemyView2D::onDefeated);
}

void PEnemyView2D::onDefeated()
{
    if(currentState != Dying){
        setState(Dying);
    }
}
