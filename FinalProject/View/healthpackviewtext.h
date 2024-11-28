#ifndef HEALTHPACKVIEWTEXT_H
#define HEALTHPACKVIEWTEXT_H

#include "qfont.h"
#include "qgraphicsitem.h"
#include "world.h"
#include <QGraphicsSimpleTextItem>
#include <QObject>

class HealthPackViewText : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT

  public:
    HealthPackViewText(const std::unique_ptr<Tile> &healthPack, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent = nullptr);

  private:
    double tileWidth, tileHeight;
    QFont font;
    QTimer *animationTimer;
    int beatCount {};

  private slots:
    void updateAnimationFrame();
};

#endif // HEALTHPACKVIEWTEXT_H
