#ifndef PENEMYVIEWTEXT_H
#define PENEMYVIEWTEXT_H

#include "qfont.h"
#include "qgraphicsitem.h"
#include "qobject.h"
#include "qpen.h"
#include "world.h"
class PEnemyViewText : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT

  public:
    PEnemyViewText(const std::unique_ptr<Enemy> &enemy, double tileWidth, double tileHeight, QFont font, QGraphicsItem *parent = nullptr);

  private:
    double tileWidth, tileHeight;
    QFont font;
    QTimer *animationTimer;
    QPen pen;
    int currentFrameIndex;

  private slots:
    void updateAnimationFrame();
};


#endif // PENEMYVIEWTEXT_H
