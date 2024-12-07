#include "enemyview2d.h"


EnemyView2D::EnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize, QGraphicsItem *parent)
    : QObject(),
    QGraphicsPixmapItem(parent),
    gridSize{gridSize}{

    setPixmap(QPixmap(":/images/enemy.png").scaled(gridSize,gridSize));
    setPos(gridSize*enemy->getXPos(), gridSize*enemy->getYPos());

    connect(enemy.get(), &Enemy::dead, this, &EnemyView2D::onDeadUpdated);
}

EnemyView2D::EnemyView2D(const std::unique_ptr<Enemy> &enemy, std::size_t gridSize, QString filename, QGraphicsItem *parent)
    : QObject(),
    QGraphicsPixmapItem(parent),
    gridSize{gridSize}{

    setPixmap(QPixmap(filename).scaled(gridSize,gridSize));
    setPos(gridSize*enemy->getXPos(), gridSize*enemy->getYPos());

    connect(enemy.get(), &Enemy::dead, this, &EnemyView2D::onDeadUpdated);
}

void EnemyView2D::updatePixMap()
{
    setPixmap(QPixmap(":/images/dead.png").scaled(gridSize,gridSize));
    update();
}

void EnemyView2D::onDeadUpdated()
{
    updatePixMap();
}
