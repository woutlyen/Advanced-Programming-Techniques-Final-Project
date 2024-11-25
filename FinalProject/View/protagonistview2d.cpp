#include "protagonistview2d.h"

ProtagonistView2D::ProtagonistView2D(const std::unique_ptr<Protagonist>& protagonist, std::size_t gridSize, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent) {

    setPixmap(QPixmap(":/images/mario.png").scaled(gridSize,gridSize));
    setPos(gridSize*protagonist->getXPos(), gridSize*protagonist->getYPos());

    connect(protagonist.get(), &Protagonist::posChanged, this, &ProtagonistView2D::onPositionChanged);
    //connect(protagonist.get(), &Protagonist::healthChanged, this, &ProtagonistView2D::onHealthChanged);
    connect(protagonist.get(), &Protagonist::energyChanged, this, &ProtagonistView2D::onEnergyChanged);

    this->gridSize = gridSize;
}

void ProtagonistView2D::onPositionChanged(int x, int y)
{
    setPos(gridSize*x, gridSize*y);
}

void ProtagonistView2D::onEnergyChanged(int energy)
{
    if(energy <= 0){
        setPixmap(QPixmap(":/images/dead.png").scaled(gridSize,gridSize));
    }
}
