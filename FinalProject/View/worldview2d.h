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
};

#endif // WORLDVIEW2D_H
