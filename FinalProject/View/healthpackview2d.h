#ifndef HEALTHPACKVIEW2D_H
#define HEALTHPACKVIEW2D_H

#include <QGraphicsPixmapItem>

#include "world.h"

class HealthPackView2D : public QGraphicsPixmapItem
{
public:
    HealthPackView2D(const std::unique_ptr<Tile>& healthPack, std::size_t gridSize, QGraphicsItem* parent = nullptr);
};

#endif // HEALTHPACKVIEW2D_H
