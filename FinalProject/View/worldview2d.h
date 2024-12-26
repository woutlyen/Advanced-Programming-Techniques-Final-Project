#ifndef WORLDVIEW2D_H
#define WORLDVIEW2D_H

#include "View/worldview.h"
#include <QObject>
#include <QPixmap>
#include <QColor>

class WorldView2D: public WorldView
{
public:
    QGraphicsScene* makeScene() const override;
    QGraphicsEllipseItem* addPoisonCircle(int x, int y, int radius, QGraphicsScene* scene, int value);
    void removePoisonCircle(QGraphicsEllipseItem* poisonCircle, QGraphicsScene* scene);

};

#endif // WORLDVIEW2D_H
