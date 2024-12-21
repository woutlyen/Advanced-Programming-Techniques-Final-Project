#include "xenemyview2d.h"

XEnemyView2D::XEnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize, QGraphicsItem *parent)
    : EnemyView2D(enemy, gridSize,":/images/mario.png" , parent)
{}


void XEnemyView2D::updatePixMap()
{
    setPixmap(QPixmap(":/images/dead.png").scaled(gridSize,gridSize));
    update();
}
