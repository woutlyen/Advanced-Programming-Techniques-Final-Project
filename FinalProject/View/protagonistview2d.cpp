#include "protagonistview2d.h"

ProtagonistView2D::ProtagonistView2D(const std::unique_ptr<Protagonist>& protagonist, std::size_t gridSize, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent) {

    setPixmap(QPixmap(":/images/mario.png").scaled(gridSize,gridSize));
    setPos(gridSize*protagonist->getXPos(), gridSize*protagonist->getYPos());
}
