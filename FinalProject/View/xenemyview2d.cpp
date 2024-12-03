#include "xenemyview2d.h"

XEnemyView2D::XEnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize, QGraphicsItem *parent)
    : EnemyView2D(enemy, gridSize,":/images/dead.png" , parent)
{}


void XEnemyView2D::updatePixMap()
{
    setPixmap(QPixmap(":/images/enemy.png").scaled(gridSize,gridSize));
    update();
}
