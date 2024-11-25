#include "enemyview2d.h"

EnemyView2D::EnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent) {

    setPixmap(QPixmap(":/images/enemy.png").scaled(gridSize,gridSize));
    setPos(gridSize*enemy->getXPos(), gridSize*enemy->getYPos());

}
