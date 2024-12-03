#include "penemyview2d.h"

PEnemyView2D::PEnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize, QGraphicsItem *parent)
    : EnemyView2D(enemy, gridSize, ":/images/dead.png", parent)
{}

void PEnemyView2D::updatePixMap()
{
    setPixmap(QPixmap(":/images/mario.png").scaled(gridSize,gridSize));
    update();
}
