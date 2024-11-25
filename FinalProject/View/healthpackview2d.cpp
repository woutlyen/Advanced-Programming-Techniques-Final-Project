#include "healthpackview2d.h"

HealthPackView2D::HealthPackView2D(const std::unique_ptr<Tile>& healthPack, std::size_t gridSize, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent) {

    setPixmap(QPixmap(":/images/heart.png").scaled(gridSize,gridSize));
    setPos(gridSize*healthPack->getXPos(), gridSize*healthPack->getYPos());
}
